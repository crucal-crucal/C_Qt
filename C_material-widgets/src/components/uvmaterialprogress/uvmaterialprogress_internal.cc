#include "uvmaterialprogress_internal.hpp"

/*!
 *  \class CUVMaterialProgressDelegate
 *  \internal
 */

CUVMaterialProgressDelegate::CUVMaterialProgressDelegate(CUVMaterialProgress* parent)
: QObject(parent), m_progress(parent), m_offset(0) {
	Q_ASSERT(parent);
}

CUVMaterialProgressDelegate::~CUVMaterialProgressDelegate() = default;
