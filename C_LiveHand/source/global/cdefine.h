#pragma once

#include <iostream>
#include <charconv>
#include <QDir>
#include <QFile>

#ifdef Q_OS_WIN
#include <Windows.h>
#include <tlhelp32.h>
#endif // Q_OS_WIN

#define  SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }

// 进程状态
enum eProcessState {
	eProcessState_Unknown = -1, // 未知
	eProcessState_Online,       // 在线
	eProcessState_Online_Push,  // 在线推送
	eProcessState_Offline,      // 离线
};

// 推送流信息
struct CPushStreamInfo {
	// 推送流类型
	enum PushStream {
		Video = 0x1,
		Audio = 0x2
	};

	QString strAddress{ "" };                        // 推送地址
	float fVideoBitRate{ 0.0 };                      // 视频比特率
	PushStream eStream{ PushStream(Video | Audio) }; // 推流类型
	int nWidth{ 0 };                                 // 视频宽度
	int nHeight{ 0 };                                // 视频高度
	int nFrameRateNum{ 1 };                          // 视频帧率分子
	int nFrameRateDen{ 25 };                         // 视频帧率分母
	int nColorDepth{ 24 };                           // 视频颜色深度
	int nAudioBitRate{ 0 };                          // 音频比特率
	int nAudioSampleRate{ 0 };                       // 音频采样率
};

constexpr int ERRBUFSIZE = 4096; // 错误信息大小
// 循环队列
template<typename T>
struct CircularQueue {
public:
	// 创建指定大小的循环队列
	explicit CircularQueue(int size);
	~CircularQueue();
	// 判断循环队列是否已满
	bool isFull() const;
	// 判断循环队列是否为空
	bool isEmpty() const;
	// 将元素推入循环队列末尾
	bool push(T);
	// 弹出队首
	T pop();
	// 获取队首
	T first();
	// 清空队列
	void clear();
	int size() const;

private:
	// 循环队列总大小
	std::atomic_int m_nSize{ 0 };
	// 循环队列头部索引
	std::atomic_int m_nFront{ 0 };
	// 循环队列尾部索引
	std::atomic_int m_nRear{ 0 };
	// 存储循环队列元素的数组
	T* m_pData{ nullptr };
};

template<typename T>
inline CircularQueue<T>::CircularQueue(const int size)
: m_nSize(size) {
	m_pData = new T[size];
}

template<typename T>
inline CircularQueue<T>::~CircularQueue() {
	delete[]m_pData;
}

template<typename T>
inline bool CircularQueue<T>::isFull() const {
	return m_nFront == (m_nRear + 1) % m_nSize;
}

template<typename T>
inline bool CircularQueue<T>::isEmpty() const {
	return m_nFront == m_nRear;
}

template<typename T>
inline bool CircularQueue<T>::push(T data) {
	if (isFull()) {
		return false;
	}
	m_pData[m_nRear] = data;
	m_nRear = (m_nRear + 1) % m_nSize;
	return true;
}

template<typename T>
inline T CircularQueue<T>::pop() {
	if (isEmpty()) {
		return nullptr;
	}
	T data = m_pData[m_nFront];
	m_nFront = (m_nFront + 1) % m_nSize;
	return data;
}

template<typename T>
inline T CircularQueue<T>::first() {
	if (isEmpty()) {
		return nullptr;
	}
	T data = m_pData[m_nFront];
	return data;
}

template<typename T>
inline void CircularQueue<T>::clear() {
	m_nFront = 0;
	m_nRear = 0;
}

template<typename T>
inline int CircularQueue<T>::size() const {
	return (m_nRear - m_nFront + m_nSize) % m_nSize;
}
