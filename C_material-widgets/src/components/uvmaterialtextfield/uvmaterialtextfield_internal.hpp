﻿#pragma once

#include <QStateMachine>

#include "uvmaterialtextfield.hpp"

class QPropertyAnimation;
class CUVMaterialTextFieldLabel;

class CUVMaterialTextFieldStateMachine final : public QStateMachine {
	Q_OBJECT

	Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
	explicit CUVMaterialTextFieldStateMachine(CUVMaterialTextField* parent);
	~CUVMaterialTextFieldStateMachine() override;

	void setLabel(CUVMaterialTextFieldLabel* label);

	inline void setProgress(qreal progress);
	[[nodiscard]] inline qreal progress() const;

public slots:
	void setupProperties(const QString& text = "") const;

private:
	Q_DISABLE_COPY(CUVMaterialTextFieldStateMachine)

	CUVMaterialTextField* const m_textField;
	QState* const m_normalState;
	QState* const m_focusedState;
	std::unique_ptr<CUVMaterialTextFieldLabel> m_label;
	QPropertyAnimation* m_offsetAnimation;
	QPropertyAnimation* m_colorAnimation;
	qreal m_progress;
};

inline void CUVMaterialTextFieldStateMachine::setProgress(const qreal progress) {
	m_progress = progress;
	m_textField->update();
}

inline qreal CUVMaterialTextFieldStateMachine::progress() const {
	return m_progress;
}

class CUVMaterialTextFieldLabel final : public QWidget {
	Q_OBJECT

	Q_PROPERTY(qreal scale WRITE setScale READ scale)
	Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
	Q_PROPERTY(QColor color WRITE setColor READ color)

public:
	explicit CUVMaterialTextFieldLabel(CUVMaterialTextField* parent);
	~CUVMaterialTextFieldLabel() override;

	inline void setScale(qreal scale);
	[[nodiscard]] inline qreal scale() const;

	inline void setOffset(const QPointF& pos);
	[[nodiscard]] inline QPointF offset() const;

	inline void setColor(const QColor& color);
	[[nodiscard]] inline QColor color() const;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Q_DISABLE_COPY(CUVMaterialTextFieldLabel)

	CUVMaterialTextField* const m_textField;
	qreal m_scale;
	qreal m_posX;
	qreal m_posY;
	QColor m_color;
};

inline void CUVMaterialTextFieldLabel::setScale(const qreal scale) {
	m_scale = scale;
	update();
}

inline qreal CUVMaterialTextFieldLabel::scale() const {
	return m_scale;
}

inline void CUVMaterialTextFieldLabel::setOffset(const QPointF& pos) {
	m_posX = pos.x();
	m_posY = pos.y();
	update();
}

inline QPointF CUVMaterialTextFieldLabel::offset() const {
	return { m_posX, m_posY };
}

inline void CUVMaterialTextFieldLabel::setColor(const QColor& color) {
	m_color = color;
	update();
}

inline QColor CUVMaterialTextFieldLabel::color() const {
	return m_color;
}