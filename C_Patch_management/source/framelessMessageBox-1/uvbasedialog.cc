#include "uvbasedialog.h"

#include <utility>

#define NATIVE_DETECT_WIDTH 10

CUVBaseDialog::CUVBaseDialog(QWidget* parent) : QDialog(parent) {
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog);
	setAttribute(Qt::WA_TranslucentBackground);
	m_pDialogBtnBox = new QDialogButtonBox(this);
	connect(m_pDialogBtnBox, &QDialogButtonBox::accepted, this, &CUVBaseDialog::accept);
	connect(m_pDialogBtnBox, &QDialogButtonBox::rejected, this, &CUVBaseDialog::reject);
	m_pDialogBtnBox->setContentsMargins(0, 6, 6, 6);
	m_pDialogBtnBox->hide();

	m_plyVTotal = new QVBoxLayout(this);
	m_plyHTitle = new QHBoxLayout;
	m_plyHContent = new QHBoxLayout;

	auto* spacerItem = new QSpacerItem(0, TITLE_HEIGHT, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_plyHTitle->addSpacerItem(spacerItem);
	m_plyHTitle->setContentsMargins(0, 0, 6, 0);
	m_plyHTitle->setSpacing(6);
	m_plyHContent->setContentsMargins(1, 0, 1, 1);

	m_plyVTotal->setContentsMargins(BORDER_SHADOW_WIDTH, BORDER_SHADOW_WIDTH, BORDER_SHADOW_WIDTH, BORDER_SHADOW_WIDTH);

	m_plyVTotal->addLayout(m_plyHTitle);
	m_plyVTotal->addLayout(m_plyHContent);
	m_plyVTotal->addWidget(m_pDialogBtnBox);
	m_plyVTotal->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_plyVTotal->setSpacing(0);
	setLayout(m_plyVTotal);
}

CUVBaseDialog::~CUVBaseDialog() = default;

void CUVBaseDialog::setTitle(QString strTitle) {
	m_strTitle = std::move(strTitle);
}

QRect CUVBaseDialog::getTilteRect() const {
	return m_rtTitle;
}

QList<QAbstractButton*> CUVBaseDialog::getTitleButton() const {
	return m_hashTitleButtons.values();
}

void CUVBaseDialog::setIcon(const QString& strPath, bool bScale, QSize scaleSize) {
	m_strIconPath = strPath;
	m_bIconScaled = bScale;
	m_icon.load(strPath);
	if (!m_icon.isNull() && m_bIconScaled) {
		m_icon = m_icon.scaled(scaleSize, Qt::KeepAspectRatio);
	}
}

void CUVBaseDialog::setResizeable(bool bResizeable) {
	m_bResizeable = bResizeable;
}

void CUVBaseDialog::setEscEnable(bool bEnable) {
	m_bEscEnable = bEnable;
}

void CUVBaseDialog::setMoveEnable(bool bEnable) {
	m_bMoveEnable = bEnable;
}

void CUVBaseDialog::setTitleVisible(bool bVisible) {
	m_bTitleVisible = bVisible;
	for (auto i : m_hashTitleButtons) {
		i->setVisible(m_bTitleVisible);
	}
}

void CUVBaseDialog::setEnterEnable(bool bEnable) {
	m_bEnterEnable = bEnable;
}

void CUVBaseDialog::setShadowVisible(bool bVisible) {
	m_bShadowVisible = bVisible;
	if (!m_bShadowVisible) {
		setAttribute(Qt::WA_TranslucentBackground, false);
		m_plyHContent->setContentsMargins(1, 0, 0, 1);
		m_plyVTotal->setContentsMargins(0, 0, 0, 0);
	}
}

void CUVBaseDialog::setTitleBtnRole(TitleButtonRoles emTitleButtonRoles) {
	if (emTitleButtonRoles == NoButtonRole) {
		qDeleteAll(m_hashTitleButtons.values());
		m_hashTitleButtons.clear();
		return;
	}
	if (emTitleButtonRoles & MinRole) {
		QPushButton* pBtn = addTitleButton(MinRole);
		connect(pBtn, &QPushButton::clicked, this, &CUVBaseDialog::showMinimized);
	}
	if (emTitleButtonRoles & MaxRole) {
		QPushButton* pBtn = addTitleButton(MaxRole);
		pBtn->setCheckable(true);
		connect(pBtn, &QPushButton::clicked, this, &CUVBaseDialog::switchSize);
	}
	if (emTitleButtonRoles & CloseRole) {
		QPushButton* pBtn = addTitleButton(CloseRole);
		connect(pBtn, &QPushButton::clicked, this, &CUVBaseDialog::closeDialog);
	}
}

void CUVBaseDialog::setDialogBtnRole(QDialogButtonBox::StandardButtons emBtns) {
	if (QDialogButtonBox::NoButton == emBtns) {
		m_pDialogBtnBox->hide();
	} else {
		m_pDialogBtnBox->setStandardButtons(emBtns);
		if (emBtns & QDialogButtonBox::Ok) {
			m_pDialogBtnBox->button(QDialogButtonBox::Ok)->setText(QObject::tr("IDS_OK"));
		}
		if (emBtns & QDialogButtonBox::Cancel) {
			m_pDialogBtnBox->button(QDialogButtonBox::Cancel)->setText(QObject::tr("IDS_CANCEL"));
		}
		if (emBtns & QDialogButtonBox::Apply) {
			m_pDialogBtnBox->button(QDialogButtonBox::Apply)->setText(QObject::tr("IDS_APPLY"));
			connect(m_pDialogBtnBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &CUVBaseDialog::apply);
		}
		m_pDialogBtnBox->show();
	}
}

void CUVBaseDialog::setContent(QWidget* pContentWidget) {
	if (pContentWidget) {
		if (!m_plyHContent->isEmpty()) {
			m_plyHContent->removeItem(m_plyHContent->itemAt(0));
		}
		m_plyHContent->addWidget(pContentWidget);
	}
}

void CUVBaseDialog::setContent(QLayout* pLayout) {
	if (pLayout) {
		if (!m_plyHContent->isEmpty()) {
			m_plyHContent->removeItem(m_plyHContent->itemAt(0));
		}
		m_plyHContent->addLayout(pLayout);
	}
}

QPushButton* CUVBaseDialog::button(QDialogButtonBox::StandardButton emBtn) {
	return m_pDialogBtnBox->button(emBtn);
}

void CUVBaseDialog::paintEvent(QPaintEvent* event) {
	if (m_bTitleVisible) {
		QPainter painter(this);
		QStyleOption opt;
		opt.init(this);
		if (m_bShadowVisible) {
			opt.rect.adjust(BORDER_SHADOW_WIDTH, BORDER_SHADOW_WIDTH, -BORDER_SHADOW_WIDTH, -BORDER_SHADOW_WIDTH);
		} else {
			opt.rect.adjust(0, 0, -1, 0);
		}
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

		painter.setPen(Qt::NoPen);

		painter.fillRect(m_rtTitle, QColor("#464545"));

		if (m_bShadowVisible) {
			painter.setBrush(Qt::NoBrush);
			for (int i = BORDER_SHADOW_WIDTH - 1; i >= 0; --i) {
				int nRGB = 80 - i * 10;
				painter.setPen(QColor(nRGB, nRGB, nRGB, i * 40));
				painter.drawRoundedRect(rect().adjusted(i, i, -i - 1, -i - 1), 3, 3, Qt::AbsoluteSize);
			}
		}
		QFont font;
		font.setPixelSize(16);
		painter.setFont(font);
		painter.setRenderHint(QPainter::TextAntialiasing);

		QRect rtUseable = m_rtTitle;
		if (!m_plyHTitle->isEmpty()) {
			int nLeftSide = m_plyHTitle->geometry().right();
			for (int i = 0; i < m_plyHTitle->count(); ++i) {
				QLayoutItem* item = m_plyHTitle->itemAt(i);
				if (item->widget()) {
					nLeftSide = qMin(item->widget()->geometry().left(), nLeftSide);
				}
			}
			rtUseable.setWidth(nLeftSide);
		}
		QRect rtIcon = rtUseable;
		if (!m_icon.isNull()) {
			if (m_bIconScaled) {
				rtIcon.setLeft(rtUseable.left() + 10);
				rtIcon.setTop(rtUseable.top() + (rtUseable.height() - m_icon.height()) / 2);
				rtIcon.setBottom(rtIcon.top() + m_icon.height());
				rtIcon.setRight(rtIcon.left() + m_icon.width());
				painter.drawPixmap(rtIcon, m_icon);
			} else {
				rtIcon.setLeft(rtUseable.left() + 2);
				rtIcon.setTop(rtUseable.top() + 2);
				rtIcon.setBottom(rtUseable.bottom() - 1);
				rtIcon.setRight(rtIcon.left() + m_icon.width());
				painter.drawPixmap(rtIcon, m_icon);
			}
		}
		if (!m_strTitle.isEmpty()) {
			painter.setPen(QColor(255, 255, 255));
			QRect rtItem = rtUseable;
			rtItem.setLeft(23);
			QFontMetrics fontMetrics(painter.font());
			if (!m_icon.isNull()) {
				rtItem.setLeft(rtIcon.right() + 23);
			}
			QString strTitle = m_strTitle;
			if (fontMetrics.horizontalAdvance(m_strTitle) > rtItem.width()) {
				strTitle = fontMetrics.elidedText(m_strTitle, Qt::ElideRight, rtItem.width());
			}
			painter.drawText(rtItem, strTitle, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
		}
	}
}

bool CUVBaseDialog::nativeEvent(const QByteArray& eventType, void* message, long* result) {
#ifdef Q_OS_WIN
	if (!m_bResizeable) {
		return false;
	}
	MSG* msg = (MSG*)message;
	switch (msg->message) {
		case WM_NCHITTEST: {
			if (!isMaximized()) {
				double dpr = this->devicePixelRatioF();
				long xPos = GET_X_LPARAM(msg->lParam) / dpr;
				long yPos = GET_Y_LPARAM(msg->lParam) / dpr;
				QPoint pos = mapFromGlobal(QPoint(xPos/* / dpr*/, yPos/* / dpr*/));
				xPos = pos.x();
				yPos = pos.y();
				if (xPos < NATIVE_DETECT_WIDTH && yPos < NATIVE_DETECT_WIDTH)                    // 左上角
					*result = HTTOPLEFT;
				else if (xPos >= width() - NATIVE_DETECT_WIDTH && yPos < NATIVE_DETECT_WIDTH)    // 右上角
					*result = HTTOPRIGHT;
				else if (xPos < NATIVE_DETECT_WIDTH && yPos >= height() - NATIVE_DETECT_WIDTH)   // 左下角
					*result = HTBOTTOMLEFT;
				else if (xPos >= width() - NATIVE_DETECT_WIDTH && yPos >= height() - NATIVE_DETECT_WIDTH)// 右下角
					*result = HTBOTTOMRIGHT;
				else if (xPos < NATIVE_DETECT_WIDTH)                                     //左边
					*result = HTLEFT;
				else if (xPos >= width() - NATIVE_DETECT_WIDTH)                              //右边
					*result = HTRIGHT;
				else if (yPos < NATIVE_DETECT_WIDTH)                                       //上边
					*result = HTTOP;
				else if (yPos >= height() - NATIVE_DETECT_WIDTH)                             //下边
					*result = HTBOTTOM;
				else              //其他部分不做处理，返回false，留给其他事件处理器处理
					return false;
				return true;
			}
		}
			break;
		case WM_GETMINMAXINFO: {
			if (::IsZoomed(msg->hwnd)) {
				RECT frame = {0, 0, 0, 0};
				AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);

				//record frame area data
				double dpr = this->devicePixelRatioF();

				QMargins frames;
				QMargins margins(0, 0, 0, 0);
				frames.setLeft(abs(frame.left) / dpr + 0.5);
				frames.setTop(abs(frame.bottom) / dpr + 0.5);
				frames.setRight(abs(frame.right) / dpr + 0.5);
				frames.setBottom(abs(frame.bottom) / dpr + 0.5);

				setContentsMargins(frames.left() + margins.left(), \
                frames.top() + margins.top(), \
                frames.right() + margins.right(), \
                frames.bottom() + margins.bottom());

				if (m_hashTitleButtons[MaxRole]) {
					if (!m_hashTitleButtons[MaxRole]->isChecked()) {
						m_hashTitleButtons[MaxRole]->setChecked(true);
					}
				}
			} else {
				setContentsMargins(QMargins());
				if (m_hashTitleButtons[MaxRole]) {
					if (m_hashTitleButtons[MaxRole]->isChecked()) {
						m_hashTitleButtons[MaxRole]->setChecked(false);
					}
				}
			}
			return false;
		}
		default: break;
	}

#endif
	return false;
}

void CUVBaseDialog::mousePressEvent(QMouseEvent* event) {
	if (m_bMoveEnable && event->button() == Qt::LeftButton && m_rtTitle.contains(event->pos())) {
		m_PressTitlePoint = event->pos();
		m_bPressTitle = true;
	}
	QDialog::mousePressEvent(event);
}

void CUVBaseDialog::mouseReleaseEvent(QMouseEvent* event) {
	if (m_bPressTitle) {
		m_bPressTitle = false;
	}
	QDialog::mouseReleaseEvent(event);
}

void CUVBaseDialog::mouseMoveEvent(QMouseEvent* event) {
	if (m_bPressTitle) {
		move(event->globalPos() - m_PressTitlePoint);
	}
	QDialog::mouseMoveEvent(event);
}

void CUVBaseDialog::keyPressEvent(QKeyEvent* event) {
	if (!m_bEscEnable && Qt::Key_Escape == event->key()) {
		return;
	} else if (!m_bEnterEnable && (Qt::Key_Return == event->key() || Qt::Key_Enter == event->key())) {
		auto key = Qt::Key(event->key());
		return;
	} else {
		QDialog::keyPressEvent(event);
	}
}

void CUVBaseDialog::resizeEvent(QResizeEvent* event) {
	if (m_bShadowVisible) {
		m_rtTitle = rect().adjusted(BORDER_SHADOW_WIDTH + 1, BORDER_SHADOW_WIDTH + 1, -BORDER_SHADOW_WIDTH - 1, 0);
	} else {
		if (m_hashTitleButtons[MaxRole] && m_hashTitleButtons[MaxRole]->isChecked()) {
			m_rtTitle = rect().adjusted(1, 10, -2, 0);
		} else {
			m_rtTitle = rect().adjusted(1, 2, -2, 0);
		}
	}
	m_rtTitle.setBottom(m_rtTitle.top() + TITLE_HEIGHT);
	if (auto* spacerItem = dynamic_cast<QSpacerItem*>(m_plyHTitle->itemAt(0)))
		spacerItem->changeSize(0, m_rtTitle.height() + 2, QSizePolicy::Expanding, QSizePolicy::Fixed);

	QDialog::resizeEvent(event);
}

void CUVBaseDialog::apply() {

}

void CUVBaseDialog::closeDialog() {
	reject();
}

void CUVBaseDialog::addTitleButton(QAbstractButton* pButton, TitleButtonRole emButtonRole) {
	insertTitleButton(pButton, m_plyHTitle->count(), emButtonRole);
}

QPushButton* CUVBaseDialog::addTitleButton(TitleButtonRole emButtonRole) {
	return insertTitleButton(m_plyHTitle->count(), emButtonRole);
}

QPushButton* CUVBaseDialog::insertTitleButton(int nIndex, TitleButtonRole emButtonRole) {
	QStyle::StandardPixmap icon = QStyle::SP_CustomBase;
	QString strObjectName;
	QString strToolTip;
	switch (emButtonRole) {
		case CUVBaseDialog::HelpRole:icon = QStyle::SP_TitleBarContextHelpButton;
			strObjectName = "CUVBaseDialog_Dialog_Btn_Help";
			strToolTip = tr("CUVBaseDialog_HELP");
			break;
		case CUVBaseDialog::MinRole:icon = QStyle::SP_TitleBarMinButton;
			strObjectName = "CUVBaseDialog_Dialog_Btn_Min";
			strToolTip = tr("CUVBaseDialog_MIN");
			break;
		case CUVBaseDialog::MaxRole:icon = QStyle::SP_TitleBarMaxButton;
			strObjectName = "CUVBaseDialog_Dialog_Btn_Max";
			strToolTip = tr("CUVBaseDialog_MAX");
			break;
		case CUVBaseDialog::CloseRole:icon = QStyle::SP_TitleBarCloseButton;
			strObjectName = "CUVBaseDialog_Dialog_Btn_Close";
			strToolTip = tr("CUVBaseDialog_CLOSE");
			break;
		default:break;
	}
	auto* pBtn = new QPushButton(this);
	pBtn->setObjectName(strObjectName);
	pBtn->setToolTip(strToolTip);
	if (!pBtn->testAttribute(Qt::WA_StyleSheet)) {
		QStyle* style = pBtn->style();
		pBtn->setIcon(style->standardIcon(icon));
	}
	insertTitleButton(pBtn, nIndex, emButtonRole);
	return pBtn;
}

void CUVBaseDialog::insertTitleButton(QAbstractButton* pButton, int nIndex, TitleButtonRole emButtonRole) {
	m_hashTitleButtons.insert(emButtonRole, pButton);
	m_plyHTitle->insertWidget(nIndex + 1, pButton);
}

void CUVBaseDialog::switchSize() {
	if (isMaximized()) {
		showNormal();
	} else {
		showMaximized();
	}
}
