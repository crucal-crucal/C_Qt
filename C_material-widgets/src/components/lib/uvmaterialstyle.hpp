#pragma once

#include <QtWidgets/QCommonStyle>

#include "uvmaterialstyle_p.hpp"

#define MATERIAL_DISABLE_THEME_COLORS \
    if (d->useThemeColors == true) { d->useThemeColors = false; }

class CUVMaterialTheme;

#ifdef CUVMATERIAL_LIB
#define CUVMATERIAL_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIAL_EXPORT Q_DECL_IMPORT
#endif

class CUVMATERIAL_EXPORT CUVMaterialStyle final : public QCommonStyle {
	Q_OBJECT

public:
	inline static CUVMaterialStyle& instance();

	void setTheme(CUVMaterialTheme* theme);
	[[nodiscard]] QColor themeColor(const QString& key) const;

protected:
	const QScopedPointer<CUVMaterialStylePrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(CUVMaterialStyle)

	CUVMaterialStyle();
};

inline CUVMaterialStyle& CUVMaterialStyle::instance() {
	static CUVMaterialStyle instance;
	return instance;
}
