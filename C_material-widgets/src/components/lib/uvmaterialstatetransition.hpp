#pragma once

#include <QAbstractTransition>

#include "uvmaterialstatetransitionevent.hpp"

#ifdef CUVMATERIAL_LIB
#define CUVMATERIAL_EXPORT Q_DECL_EXPORT
#else
#define CUVMATERIAL_EXPORT Q_DECL_IMPORT
#endif

/*
 * @brief ×´Ì¬»ú×´Ì¬×ª»»Àà
 */
class CUVMATERIAL_EXPORT CUVMaterialStateTransition final : public QAbstractTransition {
	Q_OBJECT

public:
	explicit CUVMaterialStateTransition(ECUVMaterialStateTransitionType type);

protected:
	bool eventTest(QEvent* event) override;
	void onTransition(QEvent*) override;

private:
	ECUVMaterialStateTransitionType m_type;
};
