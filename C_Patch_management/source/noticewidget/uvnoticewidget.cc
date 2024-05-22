#include "uvnoticewidget.hpp"

#include <QFontMetrics>
#include <QTime>

CUVNoticeWidget::CUVNoticeWidget(QWidget* parent) : QLabel(parent) {
	m_TimerCount = m_notice_def_delay_cnt;
	setAlignment(Qt::AlignCenter);

	m_Timer = new QTimer(this);
	connect(m_Timer, &QTimer::timeout, this, &CUVNoticeWidget::OnTimerTimeout, Qt::UniqueConnection);
}

CUVNoticeWidget::~CUVNoticeWidget() {
	if (m_Timer->isActive()) {
		m_Timer->stop();
	}

	delete m_Timer;
	deleteLater();
}

void CUVNoticeWidget::notice(QWidget* parent, const QString& msg, const int delay_ms, const bool bsuccess) {
	if (m_Timer->isActive()) {
		m_Timer->stop();
		setVisible(false);
	}

	if (msg.isEmpty() || delay_ms <= 0) {
		return;
	}

	setParent(parent);
	setMessage(msg, delay_ms, bsuccess);
	m_Timer->start(m_timer_interval_ms);
}

void CUVNoticeWidget::setMessage(const QString& msg, const int delay_ms, const bool bsuccess) {
	QStringList string_list = msg.split("\n");
	const QFontMetrics font_metrics(font());
	m_ListLinesLen.clear();

	int maxLinelen = 1; // 最长的那一行
	for (const auto& s : string_list) {
		int tmpW = font_metrics.horizontalAdvance(s);
		m_ListLinesLen.append(tmpW);
		if (maxLinelen < tmpW) {
			maxLinelen = tmpW;
		}
	}

	m_Parent = parentWidget();
	m_BaseWidth = font_metrics.horizontalAdvance(msg);
	m_BaseHeight = font_metrics.lineSpacing() + m_patch_height;
	m_MinHeight = (m_BaseWidth * m_BaseHeight) / maxLinelen + 1; // 面积除以最长的宽就是最小的高

	changeSize();
	setWordWrap(true); // 换行
	setText(msg);
	// 居中
	if (m_Parent) {
		move((m_Parent->width() - width()) >> 1, (m_Parent->height() - height()) >> 1);
	}

	setVisible(true);
	m_fontcolor = bsuccess ? "green" : "red";
	setStyleSheet(QString(STYLE_SHEET).arg(m_fontcolor).arg(m_transparent_max_val)); // 不透明
	m_TimerCount = delay_ms / m_timer_interval_ms + 1;                               // 延时计数计算
	m_TransparentVal = m_transparent_max_val;
}

void CUVNoticeWidget::changeSize() {
	if (m_Parent) {
		const double wd = m_Parent->width() * m_size_scale;
		// 提示内容多少决定提示框面积，长方形面积 s = m_BaseHeight * m_BaseWidth
		// 面积 s 固定，当 m_BaseWidth 跟随窗体宽度变大而增大，那么 m_BaseHeight 应当变小，才维持 s 固定
		int newH = static_cast<int>((m_BaseHeight * m_BaseWidth) / wd) + m_patch_height;
		if (newH < (m_MinHeight + m_BaseHeight)) { // 设定最小高度
			newH = m_MinHeight + m_BaseHeight;
		} else {
			foreach(const int lineLen, m_ListLinesLen) {
				if (lineLen > wd) { // 某一行长度大于当前宽度就会发生折行，高度需要增加
					newH += m_BaseHeight;
				}
			}
		}

		setFixedSize(static_cast<int>(wd), newH);
	}
}

void CUVNoticeWidget::OnTimerTimeout() {
	--m_TimerCount;
	if (m_TimerCount) {
		if (m_Parent) {
			if (const QPoint pt((m_Parent->width() - width()) >> 1, (m_Parent->height() - height()) >> 1); pos() != pt) { // 父窗口位置变化
				changeSize();
				move(pt);
			}
		}
		// 最后1s开始渐变消失
		if (m_TimerCount <= m_notice_def_delay_cnt && 0 < m_TransparentVal) {
			m_TransparentVal -= m_transparent_cut_val;
			if (0 > m_TransparentVal) {
				m_TransparentVal = 0;
			}
			// 控制透明度
			setStyleSheet(QString(STYLE_SHEET).arg(m_fontcolor).arg(m_TransparentVal));
		}
	} else {
		m_Timer->stop();
		setVisible(false);
	}
}
