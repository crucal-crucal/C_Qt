#pragma once

#include "lib/uvmaterialoverlaywidget.hpp"

class CUVMaterialBadgePrivate;

class CUVMaterialBadge : public CUVMaterialOverlayWidget {
	Q_OBJECT

	Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
	Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
	Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)

public:
	explicit CUVMaterialBadge(QWidget* parent = 0);
	explicit CUVMaterialBadge(const QIcon& icon, QWidget* parent = 0);
	explicit CUVMaterialBadge(const QString& text, QWidget* parent = 0);
	~CUVMaterialBadge();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setTextColor(const QColor& color);
	QColor textColor() const;

	void setBackgroundColor(const QColor& color);
	QColor backgroundColor() const;

	void setRelativePosition(const QPointF& pos);
	void setRelativePosition(qreal x, qreal y);
	QPointF relativePosition() const;

	void setRelativeXPosition(qreal x);
	qreal relativeXPosition() const;

	void setRelativeYPosition(qreal y);
	qreal relativeYPosition() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

	void setIcon(const QIcon& icon);
	QIcon icon() const;

	void setText(const QString& text);
	QString text() const;

protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

	int getDiameter() const;

	const QScopedPointer<CUVMaterialBadgePrivate> d_ptr;

private:
	Q_DISABLE_COPY(CUVMaterialBadge)
	Q_DECLARE_PRIVATE(CUVMaterialBadge)
};
