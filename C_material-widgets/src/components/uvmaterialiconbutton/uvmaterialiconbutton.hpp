#pragma once

#include <QtWidgets/QAbstractButton>

class CUVMaterialIconButtonPrivate;

#ifdef CUVMATERIALICONBUTTON_LIB
#define CUVMATERIALICONBUTTON_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALICONBUTTON_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALICONBUTTON_EXPORT CUVMaterialIconButton final : public QAbstractButton {
	Q_OBJECT

public:
	explicit CUVMaterialIconButton(const QIcon& icon, QWidget* parent = nullptr);
	~CUVMaterialIconButton() override;

	[[nodiscard]] QSize sizeHint() const Q_DECL_OVERRIDE;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setColor(const QColor& color);
	[[nodiscard]] QColor color() const;

	void setDisabledColor(const QColor& color);
	[[nodiscard]] QColor disabledColor() const;

protected:
	explicit CUVMaterialIconButton(CUVMaterialIconButtonPrivate& d, QWidget* parent = nullptr);

	bool event(QEvent* event) Q_DECL_OVERRIDE;
	bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

	const QScopedPointer<CUVMaterialIconButtonPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CUVMaterialIconButton)
	Q_DECLARE_PRIVATE(CUVMaterialIconButton)
};
