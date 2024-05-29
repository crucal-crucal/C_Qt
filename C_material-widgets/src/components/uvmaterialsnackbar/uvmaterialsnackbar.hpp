#pragma once

#include "lib/uvmaterialoverlaywidget.hpp"

class CUVMaterialSnackbarPrivate;

#ifdef CUVMATERIALSNACKBAR_LIB
#define CUVMATERIALSNACKBAR_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIALSNACKBAR_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIALSNACKBAR_EXPORT CUVMaterialSnackbar final : public CUVMaterialOverlayWidget {
	Q_OBJECT

public:
	explicit CUVMaterialSnackbar(QWidget* parent = nullptr);
	~CUVMaterialSnackbar() override;

	void setAutoHideDuration(int duration);
	[[nodiscard]] int autoHideDuration() const;

	void setUseThemeColors(bool value);
	[[nodiscard]] bool useThemeColors() const;

	void setBackgroundColor(const QColor& color);
	[[nodiscard]] QColor backgroundColor() const;

	void setBackgroundOpacity(qreal opacity);
	[[nodiscard]] qreal backgroundOpacity() const;

	void setTextColor(const QColor& color);
	[[nodiscard]] QColor textColor() const;

	void setFontSize(qreal size);
	[[nodiscard]] qreal fontSize() const;

	void setBoxWidth(int width);
	[[nodiscard]] int boxWidth() const;

	void setClickToDismissMode(bool value);
	[[nodiscard]] bool clickToDismissMode() const;

public slots:
	void addMessage(const QString& message);
	void addInstantMessage(const QString& message);
	void dequeue();

protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

	const QScopedPointer<CUVMaterialSnackbarPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CUVMaterialSnackbar)
	Q_DECLARE_PRIVATE(CUVMaterialSnackbar)
};
