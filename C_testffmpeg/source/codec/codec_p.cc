#include "codec_p.h"

#include <utility>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavformat/avio.h"
#include "libavcodec/bsf.h"
#include "libavdevice/avdevice.h"
#include "libavutil/samplefmt.h"
#include "libavutil/imgutils.h"
#include "libavcodec/codec_par.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
#include "libavutil/pixfmt.h"
}

//CCalcPtsDur
inline CCalcPtsDur::CCalcPtsDur() {
	m_dTimeBase = 0.0;
	m_dFpsBen = 0.0;
	m_dFpsNum = 0.0;
	m_dFrameDur = 0.0;

	m_llAbsBaseTime = 0;
}

inline CCalcPtsDur::~CCalcPtsDur() = default;

inline void CCalcPtsDur::SetAbsBaseTime(const __int64& llAbsBaseTime) {
	m_llAbsBaseTime = llAbsBaseTime;
}

inline void CCalcPtsDur::SetTimeBase(const int iTimeBase, const int iFpsNum, const int iFpsBen) {
	m_dTimeBase = static_cast<double>(iTimeBase);
	m_dFpsBen = static_cast<double>(iFpsBen);
	m_dFpsNum = static_cast<double>(iFpsNum);

	m_dFrameDur = m_dTimeBase / (m_dFpsNum / m_dFpsBen);
}

inline __int64 CCalcPtsDur::GetVideoPts(__int64 lFrameIndex) const {
	auto lPts = static_cast<__int64>(m_dFrameDur) * lFrameIndex;
	lPts += m_llAbsBaseTime;

	return lPts;
}

inline __int64 CCalcPtsDur::GetVideoDur(__int64 lFrameIndex) const {
	__int64 lPts0 = static_cast<__int64>(m_dFrameDur) * lFrameIndex;
	__int64 lPts1 = static_cast<__int64>(m_dFrameDur) * (lFrameIndex + 1);
	return lPts1 - lPts0;
}

inline __int64 CCalcPtsDur::GetAudioPts(__int64 lPaketIndex, int iAudioSample) const {
	__int64 dAACSample = 1024.0;

	__int64 llPts = lPaketIndex * static_cast<__int64>(m_dTimeBase) * dAACSample / iAudioSample;
	llPts += m_llAbsBaseTime;
	return llPts;
}

__int64 CCalcPtsDur::GetAudioDur(__int64 lPaketIndex, int iAudioSample) const {
	__int64 lPts0 = GetAudioPts(lPaketIndex, iAudioSample);
	__int64 lPts1 = GetAudioPts(lPaketIndex + 1, iAudioSample);
	return lPts1 - lPts0;
}

// 根据给定的采样率和通道数，为 ADTS 格式的音频帧补充 ADTS 头部信息
void GetADTS(uint8_t* pBuf, __int64 nSampleRate, __int64 nChannels) {
	// 根据采样率确定 ADTS 头部中的 smap 值
	int iSmapIndex = 0;
	if (nSampleRate == 44100)
		iSmapIndex = 4;
	else if (nSampleRate == 48000)
		iSmapIndex = 3;
	else if (nSampleRate == 32000)
		iSmapIndex = 5;
	else if (nSampleRate == 64000)
		iSmapIndex = 2;

	// 构建 ADTS 头部中的 audio_specific_config 字段
	uint16_t audio_specific_config = 0;
	audio_specific_config |= ((2 << 11) & 0xF800);
	audio_specific_config |= ((iSmapIndex << 7) & 0x0780);
	audio_specific_config |= ((nChannels << 3) & 0x78);
	audio_specific_config |= 0 & 0x07;

	// 将 audio_specific_config 写入 ADTS 头部的前两个字节
	pBuf[0] = (audio_specific_config >> 8) & 0xFF;
	pBuf[1] = audio_specific_config & 0xFF;
	// 后续三个字节设置为常量值
	pBuf[2] = 0x56;
	pBuf[3] = 0xe5;
	pBuf[4] = 0x00;
}

// CCodecThread
FILE* CCodecThread::m_pLogFile = nullptr;
CCodecThread::CCodecThread(QString strFile, CPushStreamInfo stStreamInfo, QSize szPlay,
                           QPair<AVCodecParameters*, AVCodecParameters*> pairRecvCodecPara, OpenMode mode, bool bLoop, bool bPicture, QObject* parent)
: QThread(parent), m_eMode(mode), m_stPushStreamInfo(std::move(stStreamInfo)), m_strFile(std::move(strFile)), m_bLoop(bLoop),
  m_pairRecvCodecPara(pairRecvCodecPara), m_szPlay(szPlay), m_bPicture(bPicture) {
	// 设置日志级别为最详细的日志信息
	av_log_set_level(AV_LOG_TRACE);
	// 设置回调函数，写入日志信息
	av_log_set_callback(LogCallBack);
	// 线程结束后自动删除
	setAutoDelete(true);
}

CCodecThread::CCodecThread(QObject* parent)
: QThread(parent) {
	av_log_set_level(AV_LOG_TRACE);
	av_log_set_callback(LogCallBack);
	setAutoDelete(true);
}

CCodecThread::~CCodecThread() {
	stop();
	clearMemory();
}

void CCodecThread::open(QString strFile, QSize szPlay, CPushStreamInfo stStreamInfo, OpenMode mode, bool bLoop, bool bPicture) {
	stop();
	m_strFile = strFile;
	m_stPushStreamInfo = stStreamInfo;
	m_eMode = mode;
	m_bLoop = bLoop;
	m_szPlay = szPlay;
	m_bPicture = bPicture;
	resume();
	start();
}

void CCodecThread::seek(const quint64& nDuration) {
	if (m_pFormatCtx) {
		// 使用 QMutexLocker 确保线程安全地操作音频和视频相关资源
		QMutexLocker videoLocker(&m_videoMutex);
		QMutexLocker audioLocker(&m_audioMutex);
		// 处理视频定位
		if (m_pVideoThread) {
			// 定位视频流
			int nRet = avformat_seek_file(m_pFormatCtx, m_nVideoIndex, m_pFormatCtx->streams[m_nVideoIndex]->start_time,
			                              nDuration / av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->time_base),
			                              m_pFormatCtx->streams[m_nVideoIndex]->duration, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
			if (nRet >= 0) {
				// 设置视频线程当前的 PTS
				m_pVideoThread->setCurrentPts(nDuration / av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->time_base));
				// 清空视频队列中的数据
				while (!m_videoPacketQueue.isEmpty()) {
					AVPacket* pkt = m_videoPacketQueue.pop();
					av_packet_unref(pkt);
					av_packet_free(&pkt);
				}
				m_videoPacketQueue.clear();
				while (!m_videoPushPacketQueue.isEmpty()) {
					AVPacket* pkt = m_videoPushPacketQueue.pop();
					av_packet_unref(pkt);
					av_packet_free(&pkt);
				}
				m_videoPushPacketQueue.clear();
			} else {
				av_log(NULL, AV_LOG_WARNING, "seek video fail, avformat_seek_file return %d\n", nRet);
			}
		}
		// 处理音频定位
		if (m_pAudioThread) {
			if (m_nAudioIndex >= 0) {
				// 定位音频流
				int nRet = avformat_seek_file(m_pFormatCtx, m_nAudioIndex, m_pFormatCtx->streams[m_nAudioIndex]->start_time,
				                              nDuration / av_q2d(m_pFormatCtx->streams[m_nAudioIndex]->time_base),
				                              m_pFormatCtx->streams[m_nAudioIndex]->duration, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
				if (nRet >= 0) {
					m_pAudioThread->setCurrentPts(nDuration / av_q2d(m_pFormatCtx->streams[m_nAudioIndex]->time_base));
					while (!m_audioPacketQueue.isEmpty()) {
						AVPacket* pkt = m_audioPacketQueue.pop();
						av_packet_unref(pkt);
						av_packet_free(&pkt);
					}
					m_audioPacketQueue.clear();
					while (!m_audioPushPacketQueue.isEmpty()) {
						AVPacket* pkt = m_audioPushPacketQueue.pop();
						av_packet_unref(pkt);
						av_packet_free(&pkt);
					}
					m_audioPushPacketQueue.clear();
				} else {
					av_log(NULL, AV_LOG_WARNING, "seek audio fail, avformat_seek_file return %d\n", nRet);
				}
			} else if (m_pEncodeMuteThread) {
				//while (!m_audioPacketQueue.isEmpty())
				//{
				//    AVPacket* pkt = m_audioPacketQueue.pop();
				//    av_packet_unref(pkt);
				//    av_packet_free(&pkt);
				//}
				//m_audioPacketQueue.clear();
				//while (!m_audioPushPacketQueue.isEmpty())
				//{
				//    AVPacket* pkt = m_audioPushPacketQueue.pop();
				//    av_packet_unref(pkt);
				//    av_packet_free(&pkt);
				//}
				//m_audioPushPacketQueue.clear();
			}
		}
	}
}

void CCodecThread::pause() {
	m_bPause = true;
	if (m_pAudioThread) {
		m_pAudioThread->pause();
	}
	if (m_pVideoThread) {
		m_pVideoThread->pause();
	}
	if (m_pEncodeMuteThread) {
		m_pEncodeMuteThread->pause();
	}
}

void CCodecThread::resume() {
	// 线程继续执行
	m_bRunning = true;
	// 线程不再暂停
	m_bPause = false;
	// 唤醒音频线程和视频线程，使其从暂停状态中恢复
	m_audioWaitCondition.wakeOne();
	m_videoWaitCondition.wakeOne();
	// 如果线程存在，恢复线程的执行
	if (m_pAudioThread) {
		m_pAudioThread->resume();
	}
	if (m_pVideoThread) {
		m_pVideoThread->resume();
	}
	if (m_pEncodeMuteThread) {
		m_pEncodeMuteThread->resume();
	}
}

void CCodecThread::stop() {
	m_bLoop = false;
	m_bRunning = false;
	m_videoWaitCondition.wakeAll();
	m_audioWaitCondition.wakeAll();
	m_AVSyncWaitCondition.wakeAll();
	wait();
}

void CCodecThread::run() {
	int nRet = -1;
	char errBuf[4096];
	//查找视频流和音频流
	nRet = avformat_open_input(&m_pFormatCtx, m_strFile.toStdString().c_str(), NULL, NULL);
	if (nRet < 0) {
		av_strerror(nRet, errBuf, 4096);
		av_log(NULL, AV_LOG_ERROR, "Can't open input, %s\n", errBuf);
		return;
	}
	nRet = avformat_find_stream_info(m_pFormatCtx, NULL);
	if (nRet < 0) {
		av_strerror(nRet, errBuf, 4096);
		av_log(NULL, AV_LOG_ERROR, "Can't find stream info, %s\n", errBuf);
		avformat_close_input(&m_pFormatCtx);
		return;
	}
	av_dump_format(m_pFormatCtx, 0, m_strFile.toStdString().c_str(), 0);
	m_nVideoIndex = av_find_best_stream(m_pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	m_nAudioIndex = av_find_best_stream(m_pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (-1 == m_nVideoIndex && -1 == m_nAudioIndex) {
		av_log(NULL, AV_LOG_ERROR, "Can't find video and audio stream, %s\n");
		avformat_close_input(&m_pFormatCtx);
		return;
	}
	//push
	int nVideoEncodeIndex = -1;
	int nAudioEncodeIndex = -1;
	QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*, AVCodecContext*>> pairPushFormat;
	if (CCodecThread::OpenMode::OpenMode_Push & m_eMode) {
		// 解析推流地址的 scheme
		QUrl url(m_stPushStreamInfo.strAddress);
		AVFormatContext* pOutputFormatCtx = NULL;
		CCalcPtsDur calPts;
		QString strFileFormat = url.scheme();
		// 根据 scheme 设置输出格式
		int nTimeBase = 90000;
		if (0 == url.scheme().compare("udp", Qt::CaseInsensitive)) {
			strFileFormat = "mpegts";
		} else if (0 == url.scheme().compare("srt", Qt::CaseInsensitive)) {
			strFileFormat = "mpegts";
			if (url.query().contains("transtype=file", Qt::CaseInsensitive)) {
				nTimeBase = 1000;
			}
		} else if (0 == url.scheme().compare("rtmp", Qt::CaseInsensitive)) {
			strFileFormat = "flv";
			nTimeBase = 1000;
		}
		// 设置时间戳计算对象的时间基准和帧率
		calPts.SetTimeBase(nTimeBase, m_stPushStreamInfo.nFrameRateDen > 0 ? m_stPushStreamInfo.nFrameRateDen : 25,
		                   m_stPushStreamInfo.nFrameRateNum > 0 ? m_stPushStreamInfo.nFrameRateNum : 1);

		// 分配输出上下文并设置相关参数
		nRet = avformat_alloc_output_context2(&pOutputFormatCtx, nullptr, strFileFormat.toStdString().c_str(),
		                                      m_stPushStreamInfo.strAddress.toStdString().c_str());
		if (nRet < 0) {
			av_strerror(nRet, errBuf, 4096);
			av_log(NULL, AV_LOG_ERROR, "Can't alloc output ctx, %s\n", errBuf);
			avformat_close_input(&m_pFormatCtx);
			return;
		}

		//video
		AVCodecContext* pOutputVideoCodecCtx = NULL;
		if (CPushStreamInfo::Video & m_stPushStreamInfo.eStream) {
			// 查找H.264视频编码器
			const AVCodec* out_VideoCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
			//const AVCodec* out_VideoCodec = avcodec_find_encoder_by_name("h264_nvenc");

			// 分配和初始化输出视频编码器上下文
			pOutputVideoCodecCtx = avcodec_alloc_context3(NULL);
			if (m_pairRecvCodecPara.first && m_pairRecvCodecPara.first->width > 0 && m_pairRecvCodecPara.first->height > 0) {
				// 存在输入流参数，将其拷贝到输出视频编码器的上下文中
				avcodec_parameters_to_context(pOutputVideoCodecCtx, m_pairRecvCodecPara.first);
				avcodec_parameters_free(&m_pairRecvCodecPara.first);
				//av_opt_set_dict(pOutputVideoCodecCtx, &m_pRectFormatCtx->streams[nVideoIndex]->metadata);
			} else {
				pOutputVideoCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
				//编码视频宽度
				pOutputVideoCodecCtx->width = m_stPushStreamInfo.nWidth > 0 ? m_stPushStreamInfo.nWidth :
					                              m_pFormatCtx->streams[m_nVideoIndex]->codecpar->width;
				//编码视频高度
				pOutputVideoCodecCtx->height = m_stPushStreamInfo.nHeight > 0 ? m_stPushStreamInfo.nHeight :
					                               m_pFormatCtx->streams[m_nVideoIndex]->codecpar->height;
				//平均码率
				pOutputVideoCodecCtx->bit_rate = m_stPushStreamInfo.fVideoBitRate > 0 ? m_stPushStreamInfo.fVideoBitRate : 2000000; //变小码率画质不清晰
				//指定图像中每个像素的颜色数据的格式
				//I帧间隔  50帧一个I帧
				pOutputVideoCodecCtx->gop_size = 50;

				pOutputVideoCodecCtx->thread_count = 4;
				//两个非b帧之间b帧最大数
				pOutputVideoCodecCtx->max_b_frames = 0;
			}

			if (pOutputFormatCtx->oformat->flags & AVFMT_GLOBALHEADER) {
				pOutputVideoCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
			}
			//最小量化因子 建议值 10~30
			pOutputVideoCodecCtx->qmin = 10; //测试结果：当QMIN升高或qmax降低，对视音频质量和大小产生明显影响
			//最大量化因子
			pOutputVideoCodecCtx->qmax = 51; //测试结果：单纯减少qmax值增大体积，但并不能提高画质，还与其他因素有关
			//运动估计的最大搜索范围。跟运动补偿有关，值越大，补偿参考范围越广，越精确，编码效率下降。
			pOutputVideoCodecCtx->me_range = 16;
			//帧间最大量化因子
			pOutputVideoCodecCtx->max_qdiff = 4;
			//压缩变化的难易程度。值越大，越难压缩变换，压缩率越高，质量损失较大
			pOutputVideoCodecCtx->qcompress = 0.4;
			//编码视频帧率  25
			pOutputVideoCodecCtx->time_base.num = m_stPushStreamInfo.nFrameRateNum > 0 ?
				                                      m_stPushStreamInfo.nFrameRateNum : m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate.num;
			pOutputVideoCodecCtx->time_base.den = m_stPushStreamInfo.nFrameRateDen > 0 ?
				                                      m_stPushStreamInfo.nFrameRateDen : m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate.den;
			/*
			preset有ultrafast，superfast，veryfast，faster，fast，medium，slow，slower，veryslow，placebo这10个级别，每个级别的preset对应一组编码参数，不同级别的preset对应的编码参数集不一致。preset级别越高，编码速度越慢，解码后的质量也越高；级别越低，速度也越快，解码后的图像质量也就越差，从左到右，编码速度越来越慢，编码质量越来越好
			*/
			AVDictionary* param = 0;
			av_dict_set(&param, "preset", "superfast", 0);
			av_dict_set(&param, "tune", "zerolatency", 0);
			//av_dict_set(&param, "profile", "baseline", 0);
			int nRet = avcodec_open2(pOutputVideoCodecCtx, out_VideoCodec, &param);
			if (nRet < 0) {
				av_strerror(nRet, errBuf, 4096);
				av_log(NULL, AV_LOG_ERROR, "Can't open video encoder\n");
				avcodec_free_context(&pOutputVideoCodecCtx);
				avformat_free_context(pOutputFormatCtx);
				avformat_close_input(&m_pFormatCtx);
				return;
			}
			//unsigned char sps_pps[23] = { 0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x0a, 0xf8, 0x0f, 0x00, 0x44, 0xbe, 0x8,
			//    0x00, 0x00, 0x00, 0x01, 0x68, 0xce, 0x38, 0x80 };
			//pOutputVideoCodecCtx->extradata_size = 23;
			//pOutputVideoCodecCtx->extradata = (uint8_t*)av_malloc(23 + AV_INPUT_BUFFER_PADDING_SIZE);
			//if (pOutputVideoCodecCtx->extradata == NULL) {
			//    printf("could not av_malloc the video params extradata!\n");
			//    return;
			//}
			//memcpy(pOutputVideoCodecCtx->extradata, sps_pps, 23);

			// 创建输出流视频
			AVStream* out_VideoStream = avformat_new_stream(pOutputFormatCtx, NULL);
			if (!out_VideoStream) {
				av_log(NULL, AV_LOG_ERROR, "Can't create video streeam\n");
				avcodec_free_context(&pOutputVideoCodecCtx);
				avformat_free_context(pOutputFormatCtx);
				avformat_close_input(&m_pFormatCtx);
				return;
			}
			// 存储视频流的索引
			nVideoEncodeIndex = out_VideoStream->index;
			// 将视频编码器上下文的参数拷贝到输出视频流的编码参数中
			avcodec_parameters_from_context(out_VideoStream->codecpar, pOutputVideoCodecCtx);
			out_VideoStream->codecpar->codec_tag = 0;

			//out_VideoStream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
			//out_VideoStream->codecpar->codec_id = AV_CODEC_ID_H264;
			//out_VideoStream->codecpar->bit_rate = m_stPushStreamInfo.nAudioBitRate > 0 ? m_stPushStreamInfo.nAudioBitRate * 1024 : 1672320;
			//out_VideoStream->codecpar->bits_per_coded_sample = 24;
			//out_VideoStream->codecpar->bits_per_raw_sample = m_stPushStreamInfo.nColorDepth > 0 ? m_stPushStreamInfo.nColorDepth : 8;
			//out_VideoStream->codecpar->profile = 100;
			//out_VideoStream->codecpar->level = 41;
			//out_VideoStream->codecpar->width = m_stPushStreamInfo.nWidth > 0 ? m_stPushStreamInfo.nWidth : m_pFormatCtx->streams[m_nVideoIndex]->codecpar->width;
			//out_VideoStream->codecpar->height = m_stPushStreamInfo.nHeight > 0 ? m_stPushStreamInfo.nHeight : m_pFormatCtx->streams[m_nVideoIndex]->codecpar->height;
			//out_VideoStream->codecpar->field_order = AV_FIELD_PROGRESSIVE;
			//out_VideoStream->codecpar->chroma_location = AVCHROMA_LOC_LEFT;
			//out_VideoStream->codecpar->video_delay = 2;

			////avcodec_parameters_copy(out_VideoStream->codecpar, m_pFormatCtx->streams[m_nVideoIndex]->codecpar);
		}

		//audio
		AVCodecContext* pOutputAudioCodecCtx = NULL;
		if (CPushStreamInfo::Audio & m_stPushStreamInfo.eStream) {
			// 查找 AAC 音频编码器
			const AVCodec* out_AudioCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
			pOutputAudioCodecCtx = avcodec_alloc_context3(out_AudioCodec);
			if (m_pairRecvCodecPara.second && m_pairRecvCodecPara.second->sample_rate > 0 && m_pairRecvCodecPara.second->channels > 0) {
				avcodec_parameters_to_context(pOutputAudioCodecCtx, m_pairRecvCodecPara.second);
				avcodec_parameters_free(&m_pairRecvCodecPara.second);
				//av_opt_set_dict(pOutputVideoCodecCtx, &m_pRectFormatCtx->streams[nVideoIndex]->metadata);
			} else {
				//avcodec_parameters_to_context(pOutputAudioCodecCtx, m_pFormatCtx->streams[m_nAudioIndex]->codecpar);
				//av_opt_set_dict(pOutputAudioCodecCtx, &m_pFormatCtx->streams[m_nAudioIndex]->metadata);
				pOutputAudioCodecCtx->profile = (strFileFormat == "mpegts") ? FF_PROFILE_MPEG2_AAC_HE : FF_PROFILE_AAC_MAIN; // 编码协议
				pOutputAudioCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO; // 音频编码
				pOutputAudioCodecCtx->sample_fmt = AV_SAMPLE_FMT_FLTP; // 指定音频采样格式为浮点数
				pOutputAudioCodecCtx->channel_layout = AV_CH_LAYOUT_STEREO; // 设置音频通道布局为立体声
				pOutputAudioCodecCtx->channels = 2; // 双通道
				pOutputAudioCodecCtx->sample_rate = m_stPushStreamInfo.nAudioSampleRate > 0 ? m_stPushStreamInfo.nAudioSampleRate : 44100; // 设置采样频率
				pOutputAudioCodecCtx->bit_rate = m_stPushStreamInfo.nAudioBitRate > 0 ? m_stPushStreamInfo.nAudioBitRate * 1024 : 327680; // 设置采样比特率
				//             if (pOutputFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
				//             {
				//                 pOutputAudioCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
				//             }

				pOutputAudioCodecCtx->extradata_size = 5;                  // 设置音频编码器的额外数据大小为5个字节
				pOutputAudioCodecCtx->extradata = (uint8_t*)av_mallocz(5); // 分配5个字节额外空间
				// 生成 AAC 的 ADTS 头信息
				GetADTS(pOutputAudioCodecCtx->extradata, pOutputAudioCodecCtx->sample_rate, pOutputAudioCodecCtx->channels);
			}
			// 创建字典，存储音频编码器的配置参数
			AVDictionary* param = 0;
			// 设置音频编码器的预设值，预设值影响编码速度和质量之前的权衡
			av_dict_set(&param, "preset", "superfast", 0);
			// 设置音频编码器的调整参数，优化编码器以减小延迟
			av_dict_set(&param, "tune", "zerolatency", 0);
			// 打开音频编码器
			nRet = avcodec_open2(pOutputAudioCodecCtx, out_AudioCodec, &param);
			if (nRet < 0) {
				av_strerror(nRet, errBuf, 4096);
				av_log(NULL, AV_LOG_ERROR, "Can't open audio encoder\n");
				avcodec_free_context(&pOutputAudioCodecCtx);
				avformat_free_context(pOutputFormatCtx);
				avformat_close_input(&m_pFormatCtx);
				return;
			}
			// 创建音频流，并将其添加到输出格式上下文中
			AVStream* out_AudioStream = avformat_new_stream(pOutputFormatCtx, NULL);
			if (!out_AudioStream) {
				av_log(NULL, AV_LOG_ERROR, "Can't create audio stream\n");
				avcodec_free_context(&pOutputAudioCodecCtx);
				avformat_free_context(pOutputFormatCtx);
				avformat_close_input(&m_pFormatCtx);
				return;
			}
			// 存储音频流的索引
			nAudioEncodeIndex = out_AudioStream->index;
			// 将音频编码器的参数复制到音频流的参数中
			nRet = avcodec_parameters_from_context(out_AudioStream->codecpar, pOutputAudioCodecCtx);
			// 不使用标签
			out_AudioStream->codecpar->codec_tag = 0;

			//out_AudioStream->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
			//out_AudioStream->codecpar->codec_id = AV_CODEC_ID_AAC;
			//out_AudioStream->codecpar->bit_rate = m_stPushStreamInfo.nAudioBitRate > 0 ? m_stPushStreamInfo.nAudioBitRate * 1024 : 327680;
			//out_AudioStream->codecpar->bits_per_coded_sample = 16;
			////out_AudioStream->codecpar->bits_per_raw_sample = 24;
			//out_AudioStream->codecpar->profile = 1;
			//out_AudioStream->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
			//out_AudioStream->codecpar->channels = 2;
			//out_AudioStream->codecpar->sample_rate = m_stPushStreamInfo.nAudioSampleRate > 0 ? m_stPushStreamInfo.nAudioSampleRate : 44100;
			//avcodec_parameters_copy(out_AudioStream->codecpar, m_pFormatCtx->streams[m_nAudioIndex]->codecpar);
		}

		// 根据文件格式判断推流类型
		int nPushStreamType = 0;
		AVDictionary* avdic = nullptr;
		if (strFileFormat == "flv")
			nPushStreamType = 0;
		else if (strFileFormat == "mpegts")
			nPushStreamType = 1;
		if (nPushStreamType == 0) {
			//		av_dict_set(&avdic, "rtmp_live", "1", 0);
			//		av_dict_set(&avdic, "live", "1", 0);
		} else if (nPushStreamType == 1) {
			av_dict_set(&avdic, "pkt_size", "1316", 0);
			//av_dict_set(&avdic, "bitrate", pBitRate, 0);
			//			av_dict_set(&avdic, "burst_bits", pBurstBits, 0);
			//			av_dict_set(&avdic, "fifo_size", pFifoSize, 0);
		} else if (nPushStreamType == 2) {
			av_dict_set(&avdic, "mss", "1316", 0);
			//			av_dict_set(&avdic, "inputbw", ptmp, 0);
			av_dict_set(&avdic, "linger", "1", 0);
		}

		// 打开输出流的 I/O 上下文，传递之前设置好的音频编码器配置参数
		nRet = avio_open2(&pOutputFormatCtx->pb, m_stPushStreamInfo.strAddress.toStdString().c_str(), AVIO_FLAG_WRITE, nullptr, &avdic);
		if (nRet < 0) {
			av_strerror(nRet, errBuf, 4096);
			av_log(NULL, AV_LOG_ERROR, "Can't open io, %s\n", errBuf);
			if (pOutputVideoCodecCtx) {
				avcodec_free_context(&pOutputVideoCodecCtx);
			}
			if (pOutputAudioCodecCtx) {
				avcodec_free_context(&pOutputAudioCodecCtx);
			}
			avformat_free_context(pOutputFormatCtx);
			avformat_close_input(&m_pFormatCtx);
			return;
		}
		// 写入输出流的头部信息，初始化输出流并写入包含必要信息的头部
		nRet = avformat_write_header(pOutputFormatCtx, nullptr);
		if (nRet < 0) {
			avio_closep(&pOutputFormatCtx->pb);
			avformat_free_context(pOutputFormatCtx);
			avformat_close_input(&m_pFormatCtx);
			av_strerror(nRet, errBuf, 4096);
			av_log(NULL, AV_LOG_ERROR, "Can't write header, %s\n", errBuf);
			return;
		}
		// 将推流所需的格式上下文，时间基准，以及视频和音频编码器上下文保存
		pairPushFormat = qMakePair(pOutputFormatCtx, std::make_tuple(calPts, pOutputVideoCodecCtx, pOutputAudioCodecCtx));
		// 启动推流线程
		m_pPushThread = new CLXPushThread(pOutputFormatCtx, m_videoPushPacketQueue, m_audioPushPacketQueue,
		                                  m_pushVideoWaitCondition, m_pushVideoMutex, m_pushAudioWaitCondition, m_pushAudioMutex,
		                                  CPushStreamInfo::Video & m_stPushStreamInfo.eStream, CPushStreamInfo::Audio & m_stPushStreamInfo.eStream);
		m_pPushThread->start();
	}
	// 如果存在视频流
	if (m_nVideoIndex >= 0) {
		// 设置解码模式
		m_eDecodeMode = m_bPicture ? eLXDecodeMode::eLXDecodeMode_CPU : eLXDecodeMode::eLXDecodeMode_GPU;
		// 创建包含 AVFormatContext 和相关信息元组的pair对象
		QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairVideoFormat;
		pairVideoFormat = qMakePair(pairPushFormat.first, std::make_tuple(std::get<0>(pairPushFormat.second), std::get<1>(pairPushFormat.second)));
		// 创建视频线程
		m_pVideoThread = new CLXVideoThread(m_videoPacketQueue, m_videoPushPacketQueue, m_videoWaitCondition,
		                                    m_videoMutex, m_pushVideoWaitCondition, m_pushVideoMutex, m_pFormatCtx, m_nVideoIndex, nVideoEncodeIndex,
		                                    pairVideoFormat,
		                                    m_eMode, m_nAudioIndex < 0, CPushStreamInfo::Video & m_stPushStreamInfo.eStream, m_szPlay, m_eDecodeMode);
		// 连接信号
		connect(m_pVideoThread, &CLXVideoThread::notifyImage, this, &CCodecThread::notifyImage);
		connect(m_pVideoThread, &CLXVideoThread::notifyCountDown, this, &CCodecThread::notifyCountDown);
		// 开启线程
		m_pVideoThread->start();
	}
	// 如果存在音频流或者是推流模式并且音频流是开启的
	if (m_nAudioIndex >= 0 || (CCodecThread::OpenMode::OpenMode_Push & m_eMode && CPushStreamInfo::Audio & m_stPushStreamInfo.eStream)) {
		// 创建存储解码参数的 AVCodecParameters 对象
		AVCodecParameters decodePara;
		// 如果没有音频流，且是推流模式并且音频流是开启的
		if (m_nAudioIndex < 0 && CCodecThread::OpenMode::OpenMode_Push & m_eMode && CPushStreamInfo::Audio & m_stPushStreamInfo.eStream) {
			// 创建一个包含音频编码参数的元组
			std::tuple<CCalcPtsDur, AVCodecContext*> pairEncodeCtx = std::make_tuple(std::get<0>(pairPushFormat.second),
			                                                                         std::get<2>(pairPushFormat.second));
			// 创建静音音频编码线程
			m_pEncodeMuteThread = new CLXEncodeMuteAudioThread(m_audioPacketQueue, m_audioWaitCondition, m_audioMutex, m_AVSyncWaitCondition,
			                                                   m_AVSyncMutex, nAudioEncodeIndex, pairEncodeCtx);
			m_pEncodeMuteThread->start();
			// 从推送格式的音频上下文中获取解码参数，并设置AAC的profile
			avcodec_parameters_from_context(&decodePara, std::get<2>(pairPushFormat.second));
			decodePara.profile = FF_PROFILE_AAC_LOW;
			memset(decodePara.extradata, 0, decodePara.extradata_size);
			decodePara.extradata_size = 0;
		}
		QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairAudioFormat;
		pairAudioFormat = qMakePair(pairPushFormat.first, std::make_tuple(std::get<0>(pairPushFormat.second), std::get<2>(pairPushFormat.second)));
		// 创建音频线程
		m_pAudioThread = new CLXAudioThread(m_audioPacketQueue, m_audioPushPacketQueue, m_audioWaitCondition,
		                                    m_audioMutex, m_pushAudioWaitCondition, m_pushAudioMutex, m_pFormatCtx, m_nAudioIndex, nAudioEncodeIndex,
		                                    pairAudioFormat,
		                                    m_eMode, CPushStreamInfo::Audio & m_stPushStreamInfo.eStream, decodePara);
		connect(m_pAudioThread, &CLXAudioThread::notifyAudio, this, &CCodecThread::notifyAudio);
		connect(m_pAudioThread, &CLXAudioThread::notifyCountDown, this, &CCodecThread::notifyCountDown);
		connect(m_pAudioThread, &CLXAudioThread::notifyAudioPara, this, &CCodecThread::notifyAudioPara);
		// 启动音频线程
		m_pAudioThread->start();
	}
	// 如果媒体文件的时长大于等于0，通过信号传递垫片的时长，单位：秒，否则传递0
	if (m_pFormatCtx->duration >= 0) {
		emit notifyClipInfo(m_pFormatCtx->duration / AV_TIME_BASE);
	} else {
		emit notifyClipInfo(0);
	}
	//视频准备读取
	AVPacket* packet = av_packet_alloc();
	av_init_packet(packet);

	//读取数据包
Loop:
	while (m_bRunning && av_read_frame(m_pFormatCtx, packet) >= 0) {
		// 如果处于暂停状态，等待编码线程唤醒
		if (m_bPause) {
			if (m_nVideoIndex >= 0) {
				QMutexLocker videoLocker(&m_videoMutex);
				m_videoWaitCondition.wait(&m_videoMutex);
			} else if (m_nAudioIndex >= 0) {
				QMutexLocker audioLocker(&m_audioMutex);
				m_audioWaitCondition.wait(&m_audioMutex);
			}
			av_packet_unref(packet);
			continue;
		}
		// 当前数据包属于视频流
		if (m_nVideoIndex == packet->stream_index) {
			// 如果是图像模式，循环将克隆的数据包推送到视频队列中，并唤醒相关线程
			if (m_bPicture) {
				while (m_bRunning) {
					AVPacket* pkt = av_packet_clone(packet);
					QMutexLocker locker(&m_videoMutex);
					if (m_videoPacketQueue.isFull()) {
						m_videoWaitCondition.wait(&m_videoMutex);
					}
					m_videoPacketQueue.push(pkt);
					m_videoWaitCondition.wakeOne();
					m_AVSyncWaitCondition.wakeOne();
				}
			}
			// 否则将克隆的数据包推送到视频队列，并唤醒相关线程
			else {
				AVPacket* pkt = av_packet_clone(packet);
				QMutexLocker locker(&m_videoMutex);
				if (m_videoPacketQueue.isFull()) {
					m_videoWaitCondition.wait(&m_videoMutex);
				}
				m_videoPacketQueue.push(pkt);
				m_AVSyncWaitCondition.wakeOne();
				m_videoWaitCondition.wakeOne();
			}
		}
		// 当前数据包属于音频流
		else if (m_nAudioIndex == packet->stream_index) {
			// 将克隆的数据包推送到音频队列，并唤醒相关线程
			AVPacket* pkt = av_packet_clone(packet);
			QMutexLocker locker(&m_audioMutex);
			if (m_audioPacketQueue.isFull()) {
				m_audioWaitCondition.wait(&m_audioMutex);
			}
			m_audioPacketQueue.push(pkt);
			m_audioWaitCondition.wakeOne();
		}
		// 释放当前数据包
		av_packet_unref(packet);
	}
	// 如果处于运行状态并且启用了循环播放
	if (m_bRunning && m_bLoop) {
		// 暂停，定位到起始时间，恢复播放
		pause();
		seek(m_pFormatCtx->start_time);
		resume();
		goto Loop;
	}
	// 清理内存
	clearMemory();
	// 如果存在推送格式的上下文，写入尾部，关闭IO，释放视频和音频编码上下文
	if (pairPushFormat.first) {
		av_write_trailer(pairPushFormat.first);
		avio_close(pairPushFormat.first->pb);
		if (std::get<1>(pairPushFormat.second)) {
			avcodec_close(std::get<1>(pairPushFormat.second));
			avcodec_free_context(&std::get<1>(pairPushFormat.second));
		}
		if (std::get<2>(pairPushFormat.second)) {
			avcodec_close(std::get<2>(pairPushFormat.second));
			avcodec_free_context(&std::get<2>(pairPushFormat.second));
		}
		avformat_free_context(pairPushFormat.first);
	}
	// 释放数据包和媒体格式上下文
	av_packet_free(&packet);
	avformat_close_input(&m_pFormatCtx);
}

void CCodecThread::LogCallBack(void* avcl, int level, const char* fmt, va_list vl) {
	QString strLogPath = qApp->applicationDirPath() + "/log/ffmpeg.log";
	if (m_pLogFile == nullptr) {
		m_pLogFile = fopen(strLogPath.toStdString().c_str(), "w+");
	}
	if (m_pLogFile) {
		// 构建时间戳格式
		char timeFmt[1024];
		sprintf(timeFmt, "%s     %s", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.z").toStdString().c_str(), fmt);
		// 将格式化后的日志信息写入文件
		vfprintf(m_pLogFile, timeFmt, vl);
		// 刷新缓冲区
		fflush(m_pLogFile);
	}
}

void CCodecThread::clearMemory() {
	if (m_pPushThread) {
		m_pushVideoWaitCondition.wakeAll();
		m_pushAudioWaitCondition.wakeAll();
		m_pPushThread->stop();
		SAFE_DELETE(m_pPushThread);
	}
	if (m_pVideoThread) {
		m_videoWaitCondition.wakeAll();
		m_pVideoThread->stop();
		SAFE_DELETE(m_pVideoThread);
	}
	if (m_pAudioThread) {
		m_audioWaitCondition.wakeAll();
		m_pAudioThread->stop();
		SAFE_DELETE(m_pAudioThread);
	}
	if (m_pEncodeMuteThread) {
		m_AVSyncWaitCondition.wakeAll();
		m_pEncodeMuteThread->stop();
		SAFE_DELETE(m_pEncodeMuteThread);
	}
	while (!m_videoPacketQueue.isEmpty()) {
		AVPacket* pkt = m_videoPacketQueue.pop();
		av_packet_unref(pkt);
		av_packet_free(&pkt);
	}
	m_videoPacketQueue.clear();
	while (!m_audioPacketQueue.isEmpty()) {
		AVPacket* pkt = m_audioPacketQueue.pop();
		av_packet_unref(pkt);
		av_packet_free(&pkt);
	}
	m_audioPacketQueue.clear();
	while (!m_videoPushPacketQueue.isEmpty()) {
		AVPacket* pkt = m_videoPushPacketQueue.pop();
		av_packet_unref(pkt);
		av_packet_free(&pkt);
	}
	m_videoPushPacketQueue.clear();
	while (!m_audioPushPacketQueue.isEmpty()) {
		AVPacket* pkt = m_audioPushPacketQueue.pop();
		av_packet_unref(pkt);
		av_packet_free(&pkt);
	}
	m_audioPushPacketQueue.clear();
}
