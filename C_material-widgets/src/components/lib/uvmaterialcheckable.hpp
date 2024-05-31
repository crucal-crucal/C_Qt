﻿#pragma once

#include <QtWidgets/QAbstractButton>

class CUVMaterialCheckablePrivate;

#ifdef CUVMATERIAL_LIB
#define CUVMATERIAL_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIAL_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIAL_EXPORT CUVMaterialCheckable : public QAbstractButton {
	Q_OBJECT

public:
	enum LabelPosition {
		LabelPositionLeft,
		LabelPositionRight,
	};

	explicit CUVMaterialCheckable(QWidget* parent = nullptr);
	~CUVMaterialCheckable() override;

	void setLabelPosition(LabelPosition placement);
	[[nodiscard]] LabelPosition labelPosition() const;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setCheckedColor(const QColor& color);
	[[nodiscard]] QColor checkedColor() const;

	void setUncheckedColor(const QColor& color);
	[[nodiscard]] QColor uncheckedColor() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void setDisabledColor(const QColor& color);
	[[nodiscard]] QColor disabledColor() const;

	void setCheckedIcon(const QIcon& icon);
	[[nodiscard]] QIcon checkedIcon() const;

	void setUncheckedIcon(const QIcon& icon);
	[[nodiscard]] QIcon uncheckedIcon() const;

	[[nodiscard]] QSize sizeHint() const override;

protected:
	explicit CUVMaterialCheckable(CUVMaterialCheckablePrivate& d, QWidget* parent = nullptr);

	bool event(QEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

	void setupProperties();

	const QScopedPointer<CUVMaterialCheckablePrivate> d_ptr;

private:
	Q_DISABLE_COPY(CUVMaterialCheckable)
	Q_DECLARE_PRIVATE(CUVMaterialCheckable)
};
