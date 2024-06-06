#include "uvmaterialcircularprogress_internal.hpp"

/*!
 *  \class CUVMaterialCircularProgressDelegate
 *  \internal
 */
CUVMaterialCircularProgressDelegate::CUVMaterialCircularProgressDelegate(CUVMaterialCircularProgress* parent)
: QObject(parent), m_progress(parent), m_dashOffset(0), m_dashLength(89), m_angle(0) {
	Q_ASSERT(parent);
}

CUVMaterialCircularProgressDelegate::~CUVMaterialCircularProgressDelegate() = default;
