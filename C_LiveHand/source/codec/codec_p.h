#pragma once

#include <QThread>
#include <QRunnable>
#include <QWaitCondition>
#include <QPixmap>
#include <QUrl>
#include <QMutex>
#include <QDebug>
#include <QApplication>

#include "global/cdefine.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavcodec/codec_par.h"
#include "libavutil/pixfmt.h"
}

class CCodecThread;
class CVideoThread;
class CAudioThread;
class CVideoPlayThread;
class CAudioPlayThread;
class CEncodeVideoThread;
class CEncodeAudioThread;
class CEncodeMuteAudioThread;
class CPushThread;
struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;
struct SwsContext;
struct AVPacket;
struct AVRational;
struct AVCodecParameters;

#ifdef CODEC_P_LIB
#define CODEC_P_EXPORT Q_DECL_EXPORT
#else
#define CODEC_P_EXPORT Q_DECL_IMPORT
#endif

class CODEC_P_EXPORT CCalcPtsDur {
public:
	CCalcPtsDur();
	~CCalcPtsDur();

	// 设置时间基准和帧率，并计算帧的持续时间
	void SetTimeBase(int iTimeBase, int iFpsNum, int iTimeBen);
	// 设置绝对基准时间
	void SetAbsBaseTime(const __int64& llAbsBaseTime);
	// 根据帧索引计算视频帧的时间戳
	[[nodiscard]] __int64 GetVideoPts(__int64 lFrameIndex) const;
	// 根据帧索引计算视频帧的持续时间
	[[nodiscard]] __int64 GetVideoDur(__int64 lFrameIndex) const;
	// 根据包索引和音频样本数计算音频帧的时间戳
	[[nodiscard]] __int64 GetAudioPts(__int64 lPaketIndex, int iAudioSample) const;
	// 根据包索引和音频样本数计算音频帧的持续时间
	[[nodiscard]] __int64 GetAudioDur(__int64 lPaketIndex, int iAudioSample) const;
	// 时间基准
	double m_dTimeBase;
	// 帧率分子
	double m_dFpsBen;
	// 帧率分母
	double m_dFpsNum;
	// 帧的持续时间
	double m_dFrameDur;

private:
	// 绝对基准时间
	__int64 m_llAbsBaseTime;
};

class CODEC_P_EXPORT CCodecThread final : public QThread, public QRunnable {
	Q_OBJECT

public:
	enum OpenMode {
		OpenMode_Play = 0x1,
		OpenMode_Push = 0x2
	};
	enum eDecodeMode {
		eDecodeMode_CPU = 0, // cpu解码
		eDecodeMode_GPU      // gpu解码
	};
	explicit CCodecThread(QString strFile, CPushStreamInfo stStreamInfo, QSize szPlay,
	                      QPair<AVCodecParameters*, AVCodecParameters*> pairRecvCodecPara,
	                      OpenMode mode = OpenMode::OpenMode_Push, bool bLoop = false,
	                      bool bPicture = false, QObject* parent = nullptr);
	explicit CCodecThread(QObject* parent = nullptr);
	~CCodecThread() override;

public:
	void open(const QString& strFile, const QSize& szPlay, const CPushStreamInfo& stStreamInfo = CPushStreamInfo(),
	          OpenMode mode = OpenMode_Play, bool bLoop = false, bool bPicture = false);
	void seek(const quint64& nDuration);
	void pause();
	void resume();
	void stop();

signals:
	void notifyClipInfo(const quint64&);
	void notifyCountDown(const quint64&);
	void notifyImage(const QPixmap&);
	void notifyAudio(const QByteArray&);
	void notifyAudioPara(const quint64&, const quint64&);

protected:
	void run() override;

private:
	static void LogCallBack(void*, int, const char*, va_list);
	void clearMemory();

private:
	QPair<AVCodecParameters*, AVCodecParameters*> m_pairRecvCodecPara;
	AVFormatContext* m_pFormatCtx{ nullptr };

private:
	QString m_strFile;                  // 要处理的文件路径
	QSize m_szPlay;                     // 播放窗口大小
	CPushStreamInfo m_stPushStreamInfo; // 推送流信息
	bool m_bRunning{ true };
	bool m_bPause{ false };
	int m_nVideoIndex{ -1 };
	int m_nAudioIndex{ -1 };
	CircularQueue<AVPacket*> m_videoPacketQueue{ 1000 };      // 存储视频数据的 AVPacket 指针队列
	CircularQueue<AVPacket*> m_audioPacketQueue{ 10000 };     // 存储音频数据的 AVPacket 指针
	CircularQueue<AVPacket*> m_videoPushPacketQueue{ 1000 };  // 存储推送视频数据的 AVPacket 指针
	CircularQueue<AVPacket*> m_audioPushPacketQueue{ 10000 }; // 存储推送音频数据的 AVPacket 指针
	QWaitCondition m_videoWaitCondition;
	QMutex m_videoMutex; // 视频线程的等待条件和互斥锁
	QWaitCondition m_audioWaitCondition;
	QMutex m_audioMutex; // 音频线程的等待条件和互斥锁
	QWaitCondition m_pushVideoWaitCondition;
	QMutex m_pushVideoMutex; // 推送视频数据线程的等待条件和互斥锁
	QWaitCondition m_pushAudioWaitCondition;
	QMutex m_pushAudioMutex; // 推送音频数据线程的等待条件和互斥锁
	QWaitCondition m_AVSyncWaitCondition;
	QMutex m_AVSyncMutex; // 音视频同步线程的的等待条件和互斥锁

	CVideoThread* m_pVideoThread{ nullptr }; // 视频线程
	CAudioThread* m_pAudioThread{ nullptr }; // 音频线程
	CEncodeMuteAudioThread* m_pEncodeMuteThread{ nullptr };
	CPushThread* m_pPushThread{ nullptr };
	CCodecThread::OpenMode m_eMode{ CCodecThread::OpenMode::OpenMode_Play };
	bool m_bLoop{ false };
	bool m_bPicture{ false };
	eDecodeMode m_eDecodeMode{ eDecodeMode::eDecodeMode_CPU };
	static FILE* m_pLogFile;
};

class CODEC_P_EXPORT CVideoThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	packetQueue 存储解码前的数据包队列
	pushPacketQueue 存储解码后的数据包队列
	waitCondition 线程同步条件
	mutex 互斥锁
	videoWaitCondition 视频同步条件
	videoMutex 视频互斥锁
	pFormatCtx 输入视频格式上下文
	nStreamIndex 输入视频流索引
	nEncodeStreamIndex 编码后视频流索引
	mapOutputCtx 输出格式上下文和编解码相关信息
	eMode 打开格式
	bSendCountDown 是否发送倒计时信号
	bPush 是否推流
	szPlay 视频播放的尺寸
	eDecodeMode 解码模式
	*/
	explicit CVideoThread(CircularQueue<AVPacket*>& packetQueue, CircularQueue<AVPacket*>& pushPacketQueue, QWaitCondition& waitCondition,
	                      QMutex& mutex, QWaitCondition& videoWaitCondition, QMutex& videoMutex, AVFormatContext* pFormatCtx,
	                      int nStreamIndex, int nEncodeStreamIndex, QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairOutputCtx,
	                      CCodecThread::OpenMode eMode, bool bSendCountDown, bool bPush, QSize szPlay, CCodecThread::eDecodeMode eDecodeMode,
	                      QObject* parent = nullptr);
	~CVideoThread() override;

public:
	void pause();
	void resume();
	void stop();

public:
	// 设置当前的时间戳
	void setCurrentPts(int64_t nPts);

	static enum AVPixelFormat hw_pix_fmt;
	static enum AVPixelFormat get_hw_format(AVCodecContext* ctx, const enum AVPixelFormat* pix_fmts);
signals:
	// 通知倒计时
	void notifyCountDown(const quint64&);
	// 通知图像
	void notifyImage(const QPixmap&);

private:
	static void clearQueue(CircularQueue<AVFrame*>& queue);

protected:
	void run() override;

private:
	AVFormatContext* m_pFormatCtx{ nullptr };                                          // 输入视频流的上下文
	AVCodecContext* m_pCodecCtx{ nullptr };                                            // 视频编解码器的上下文
	QSize m_szPlay;                                                                    // 视频播放尺寸
	QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> m_pairOutputCtx; // 输出格式上下文和编解码相关信息
	int m_nStreamIndex{ -1 };                                                          // 输入视频流索引
	int m_nEncodeStreamIndex{ -1 };                                                    // 编码后视频流索引
	bool m_bRunning{ true };                                                           // 是否在运行
	bool m_bPause{ false };                                                            // 是否暂停
	bool m_bSendCountDown{ false };                                                    // 是否发送倒计时信号
	bool m_bPush{ false };                                                             // 是否推流
	bool m_decodeType{ false };                                                        // 解码类型

	CEncodeVideoThread* m_pEncodeThread{ nullptr };    // 视频编码线程
	CVideoPlayThread* m_pPlayThread{ nullptr };        // 视频播放线程
	CircularQueue<AVPacket*>& m_packetQueue;           // 存储解码前的数据包循环队列
	CircularQueue<AVPacket*>& m_pushPacketQueue;       // 存储解码后的数据包循环队列
	CircularQueue<AVFrame*> m_decodeFrameQueue{ 100 }; // 存储解码后视频帧的循环队列
	CircularQueue<AVFrame*> m_playFrameQueue{ 100 };   // 存储播放的视频帧的循环队列
	QWaitCondition& m_decodeWaitCondition;             // 解码线程条件变量和互斥锁
	QMutex& m_decodeMutex;
	QWaitCondition m_encodeWaitCondition; // 编码线程条件变量和互斥锁
	QMutex m_encodeMutex;
	QWaitCondition m_playWaitCondition; // 播放线程条件变量和互斥锁
	QMutex m_playMutex;
	QWaitCondition& m_pushWaitCondition; // 推流线程条件变量和互斥锁
	QMutex& m_pushMutex;
	CCodecThread::OpenMode m_eMode{ CCodecThread::OpenMode::OpenMode_Play }; // 打开模式，是播放还是推流
	const CCodecThread::eDecodeMode& m_eDecodeMode;                          // 解码模式
};

class CODEC_P_EXPORT CAudioThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	packetQueue 存储解码前的数据包队列
	pushPacketQueue 存储解码后的数据包队列
	waitCondition 线程同步条件
	mutex 互斥锁
	audioWaitCondition 音频同步条件
	audioMutex 音频互斥锁
	pFormatCtx 输入音频格式上下文
	nStreamIndex 输入音频流索引
	nEncodeStreamIndex 编码后音频流索引
	pairOutputCtx 输出格式上下文和编解码相关信息
	eMode 打开格式
	bPush 是否推流
	decodePara 解码参数
	*/
	explicit CAudioThread(CircularQueue<AVPacket*>& packetQueue, CircularQueue<AVPacket*>& pushPacketQueue, QWaitCondition& waitCondition,
	                      QMutex& mutex, QWaitCondition& audioWaitCondition, QMutex& audioMutex, AVFormatContext* pFormatCtx,
	                      int nStreamIndex, int nEncodeStreamIndex, QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairOutputCtx,
	                      CCodecThread::OpenMode eMode, bool bPush, const AVCodecParameters& decodePara, QObject* parent = nullptr);
	~CAudioThread() override;

public:
	void pause();
	void resume();
	void stop();

public:
	void setCurrentPts(int64_t nPts);

private:
	static void clearQueue(CircularQueue<AVFrame*>& queue);

signals:
	// 通知倒计时信息
	void notifyCountDown(const quint64&);
	// 通知音频数据
	void notifyAudio(const QByteArray&);
	// 通知音频参数
	void notifyAudioPara(const quint64&, const quint64&);

protected:
	void run() override;

private:
	CEncodeAudioThread* m_pEncodeThread{ nullptr };                                    // 编码音频线程
	CAudioPlayThread* m_pPlayThread{ nullptr };                                        // 播放音频线程
	AVFormatContext* m_pFormatCtx{ nullptr };                                          // 输入音频流的格式上下文
	AVCodecContext* m_pCodecCtx{ nullptr };                                            // 音频解码器上下文
	const AVCodecParameters& m_decodePara;                                             // 解码参数
	QPair<AVFormatContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> m_pairOutputCtx; // 输出音频流的相关上下文
	int m_nStreamIndex{ -1 };                                                          // 输入音频流索引
	int m_nEncodeStreamIndex{ -1 };                                                    // 编码音频流索引
	bool m_bRunning{ true };                                                           // 线程是否运行
	bool m_bPause{ false };                                                            // 线程是否暂停
	bool m_bPush{ false };                                                             // 线程是否推流

	CircularQueue<AVPacket*>& m_packetQueue;            // 音频包队列
	CircularQueue<AVPacket*>& m_pushPacketQueue;        // 音频推送包队列
	CircularQueue<AVFrame*> m_decodeFrameQueue{ 1000 }; // 解码帧队列
	CircularQueue<AVFrame*> m_playFrameQueue{ 1000 };   // 播放帧队列
	QWaitCondition& m_decodeWaitCondition;              // 解码等待条件以及解码互斥锁
	QMutex& m_decodeMutex;
	QWaitCondition m_encodeWaitCondition; // 编码等待条件以及编码互斥锁
	QMutex m_encodeMutex;
	QWaitCondition m_playWaitCondition; // 播放等待条件以及播放互斥锁
	QMutex m_playMutex;
	QWaitCondition& m_pushWaitCondition; // 推流等待条件以及推流互斥锁
	QMutex& m_pushMutex;
	CCodecThread::OpenMode m_eMode{ CCodecThread::OpenMode::OpenMode_Play }; // 音频处理方式
};

class CODEC_P_EXPORT CVideoPlayThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	decodeFrameQueue 等待播放视频帧队列
	waitCondition 线程同步条件
	mutex 互斥锁
	pCodecCtx 对应的视频解码器
	timeBase 视频帧时间基数
	bSendCountDown 是否发送倒计时
	videoThread 音频线程
	szPlay 播放窗口大小
	eDecodeMode 视频解码模式
	*/
	explicit CVideoPlayThread(CircularQueue<AVFrame*>& decodeFrameQueue, QWaitCondition& waitCondition, QMutex& mutex,
	                          AVCodecContext* pCodecCtx, const AVRational& timeBase, bool bSendCountDown, CVideoThread* videoThread, QSize szPlay,
	                          CCodecThread::eDecodeMode eDecodeMode, QObject* parent = nullptr);
	~CVideoPlayThread() override;

public:
	void pause();
	void resume();
	void stop();

public:
	void setCurrentPts(int64_t nPts);

protected:
	void run() override;

private:
	AVCodecContext* m_pCodecCtx{ nullptr };    // 视频解码器
	bool m_bRunning{ true };                   // 线程是否运行
	bool m_bPause{ false };                    // 是否暂停
	int64_t m_nLastTime{ -1 };                 // 上一次播放时间
	int64_t m_nLastPts{ -1 };                  // 上一次播放时间戳
	bool m_bSendCountDown{ false };            // 是否发送倒计时通知
	const AVRational& m_timeBase;              // 视频帧时间基数
	CVideoThread* m_videoThread{ nullptr };    // 视频线程
	CircularQueue<AVFrame*>& m_playFrameQueue; // 视频播放帧队列
	QWaitCondition& m_playWaitCondition;       // 视频播放等待条件以及互斥锁
	QMutex& m_playMutex;
	QSize m_szPlay;                                 // 播放窗口尺寸
	const CCodecThread::eDecodeMode& m_eDecodeMode; // 视频解码模式
};

class CODEC_P_EXPORT CAudioPlayThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	decodeFrameQueue 等待播放音频帧队列
	waitCondition 线程同步条件
	mutex 互斥锁
	pCodecCtx 对应的音频解码器
	timeBase 音频帧时间基数
	audioThread 音频线程
	*/
	explicit CAudioPlayThread(CircularQueue<AVFrame*>& decodeFrameQueue, QWaitCondition& waitCondition, QMutex& mutex,
	                          AVCodecContext* pCodecCtx, const AVRational& timeBase, CAudioThread* audioThread, QObject* parent = nullptr);
	~CAudioPlayThread() override;

public:
	void pause();
	void resume();
	void stop();

public:
	void setCurrentPts(int64_t nPts);

protected:
	void run() override;

private:
	AVCodecContext* m_pCodecCtx{ nullptr };    // 音频解码器
	bool m_bRunning{ true };                   // 是否运行
	bool m_bPause{ false };                    // 是否暂停
	int64_t m_nLastTime{ -1 };                 // 上一次播放时间
	int64_t m_nLastPts{ -1 };                  // 上一次播放时间戳
	const AVRational& m_timeBase;              // 音频时间基数
	CAudioThread* m_audioThread{ nullptr };    // 音频线程
	CircularQueue<AVFrame*>& m_playFrameQueue; // 待播放音频帧队列
	QWaitCondition& m_playWaitCondition;       // 音频播放等待条件以及互斥锁
	QMutex& m_playMutex;
};

class CODEC_P_EXPORT CEncodeVideoThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	encodeFrameQueue 等待编码的视频帧队列
	pushPacketQueue 等待推送的视频包队列
	encodeWaitCondition 编码线程同步条件
	encodeMutex 编码互斥锁
	pushWaitCondition 推送线程同步条件
	pushMutex 推送互斥锁
	nEncodeStreamIndex 视频流索引
	pairEncodeCtx 编码器上下文和相关信息的组合
	eDecodeMode 编码模式
	*/
	explicit CEncodeVideoThread(CircularQueue<AVFrame*>& encodeFrameQueue, CircularQueue<AVPacket*>& pushPacketQueue,
	                            QWaitCondition& encodeWaitCondition,
	                            QMutex& encodeMutex, QWaitCondition& pushWaitCondition, QMutex& pushMutex, int nEncodeStreamIndex,
	                            QPair<AVCodecContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairEncodeCtx,
	                            CCodecThread::eDecodeMode eDecodeMode, QObject* parent = nullptr);
	~CEncodeVideoThread() override;

public:
	void pause();
	void resume();
	void stop();

protected:
	void run() override;

private:
	CircularQueue<AVFrame*>& m_encodeFrameQueue;                                      // 等待编码的视频帧队列
	CircularQueue<AVPacket*>& m_pushPacketQueue;                                      // 等待推流的视频包队列
	int m_nEncodeStreamIndex{ -1 };                                                   // 视频流索引
	QWaitCondition& m_encodeWaitCondition;                                            // 编码线程同步条件
	QMutex& m_encodeMutex;                                                            // 编码互斥锁
	QWaitCondition& m_pushWaitCondition;                                              // 推流线程互斥条件
	QMutex& m_pushMutex;                                                              // 推流互斥锁
	QPair<AVCodecContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> m_pairEncodeCtx; // 编码器以及相关的信息
	bool m_bRunning{ true };                                                          // 是否运行
	bool m_bPause{ false };                                                           // 是否暂停
	const CCodecThread::eDecodeMode& m_eEncodeMode;                                   // 编码模式
};

class CODEC_P_EXPORT CEncodeAudioThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	encodeFrameQueue 等待编码的音频帧队列
	pushPacketQueue 等待推送的音频包队列
	encodeWaitCondition 编码线程同步条件
	encodeMutex 编码互斥锁
	pushWaitCondition 推送线程同步条件
	pushMutex 推送互斥锁
	nEncodeStreamIndex 音频流索引
	pairEncodeCtx 编码器上下文和相关信息的组合
	*/
	explicit CEncodeAudioThread(CircularQueue<AVFrame*>& encodeFrameQueue, CircularQueue<AVPacket*>& pushPacketQueue,
	                            QWaitCondition& encodeWaitCondition, QMutex& encodeMutex, QWaitCondition& pushWaitCondition, QMutex& pushMutex,
	                            int nEncodeStreamIndex, QPair<AVCodecContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> pairEncodeCtx,
	                            QObject* parent = nullptr);
	~CEncodeAudioThread() override;

public:
	void pause();
	void resume();
	void stop();

protected:
	void run() override;

private:
	CircularQueue<AVFrame*>& m_encodeFrameQueue;                                      // 等待编码的音频帧队列
	CircularQueue<AVPacket*>& m_pushPacketQueue;                                      // 等待推送的音频包队列
	int m_nEncodeStreamIndex{ -1 };                                                   // 音频流索引
	QWaitCondition& m_encodeWaitCondition;                                            // 编码线程同步条件
	QMutex& m_encodeMutex;                                                            // 编码线程互斥锁
	QWaitCondition& m_pushWaitCondition;                                              // 推流线程同步条件
	QMutex& m_pushMutex;                                                              // 推流线程互斥锁
	QPair<AVCodecContext*, std::tuple<CCalcPtsDur, AVCodecContext*>> m_pairEncodeCtx; // 编码器及其相关信息
	bool m_bRunning{ true };                                                          // 是否运行
	bool m_bPause{ false };                                                           // 是否暂停
};

class CODEC_P_EXPORT CEncodeMuteAudioThread final : public QThread {
	Q_OBJECT

public:
	/* @Parameter
	pushPacketQueue 等待推送的音频包队列引用
	encodeWaitCondition 编码线程同步条件引用
	encodeMutex 编码互斥锁引用
	syncWaitCondition 推送线程同步条件引用
	syncMutex 推送互斥锁引用
	nEncodeStreamIndex 音频流索引
	pairEncodeCtx 编码器上下文和相关信息的组合
	*/
	explicit CEncodeMuteAudioThread(CircularQueue<AVPacket*>& pushPacketQueue, QWaitCondition& encodeWaitCondition,
	                                QMutex& encodeMutex, QWaitCondition& syncWaitCondition, QMutex& syncMutex, int nEncodeStreamIndex,
	                                std::tuple<CCalcPtsDur, AVCodecContext*> pairEncodeCtx, QObject* parent = nullptr);
	~CEncodeMuteAudioThread() override;

public:
	void pause();
	void resume();
	void stop();

protected:
	void run() override;

private:
	CircularQueue<AVPacket*>& m_encodePacketQueue;            // 等待推送的音频包队列引用
	int m_nEncodeStreamIndex{ -1 };                           // 音频流索引
	QWaitCondition& m_encodeWaitCondition;                    // 编码线程同步条件引用
	QMutex& m_encodeMutex;                                    // 编码互斥锁引用
	QWaitCondition& m_syncWaitCondition;                      // 推送线程同步条件引用
	QMutex& m_syncMutex;                                      // 推送互斥锁引用
	std::tuple<CCalcPtsDur, AVCodecContext*> m_pairEncodeCtx; // 编码器上下文和相关信息
	bool m_bRunning{ true };                                  // 是否运行
	bool m_bPause{ false };                                   // 是否暂停
};

class CODEC_P_EXPORT CPushThread final : public QThread {
	Q_OBJECT

public:
	explicit CPushThread(AVFormatContext* pOutputFormatCtx, CircularQueue<AVPacket*>& videoPacketQueue,
	                     CircularQueue<AVPacket*>& audioPacketQueue, QWaitCondition& videoWaitCondition, QMutex& videoMutex,
	                     QWaitCondition& audioWaitCondition, QMutex& audioMutex, bool bPushVideo, bool bPushAudio, QObject* parent = nullptr);
	~CPushThread() override;

public:
	// 暂停推送
	void pause();
	// 恢复推送
	void resume();
	// 停止推送
	void stop();

protected:
	void run() override;

private:
	CircularQueue<AVPacket*>& m_videoPacketQueue;   // 视频数据队列
	CircularQueue<AVPacket*>& m_audioPacketQueue;   // 音频数据队列
	bool m_bRunning{ true };                        // 线程是否在执行
	bool m_bPause{ false };                         // 线程是否暂停
	bool m_bPushVideo{ true };                      // 是否推送视频
	bool m_bPushAudio{ false };                     // 是否推送音频
	QWaitCondition& m_videoWaitCondition;           // 视频等待条件
	QMutex& m_videoMutex;                           // 视频互斥锁
	QWaitCondition& m_audioWaitCondition;           // 音频等待条件
	QMutex& m_audioMutex;                           // 音频互斥锁
	AVFormatContext* m_pOutputFormatCtx{ nullptr }; // 输出格式上下文
};

class CODEC_P_EXPORT CRecvThread final : public QThread, public QRunnable {
	Q_OBJECT

public:
	explicit CRecvThread(QString strPath, QObject* parent = nullptr);
	~CRecvThread() override;

public:
	void stop();
	[[nodiscard]] QString path() const;
	[[nodiscard]] QPair<AVCodecParameters*, AVCodecParameters*> getContext() const;

protected:
	void run() override;

private:
	AVFormatContext* m_pFormatCtx{ nullptr };
	QString m_strPath{ "" };
	bool m_bRunning{ false };
	int64_t m_nVideoPts{ -1 };
	int64_t m_nAudioPts{ -1 };
	AVCodecParameters* m_pVideoCodecPara{ nullptr };
	AVCodecParameters* m_pAudioCodecPara{ nullptr };
};
