#pragma once

#include "uvmaterialprogress.hpp"

class CUVMaterialProgressDelegate final : public QObject {
	Q_OBJECT

	Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialProgressDelegate(CUVMaterialProgress* parent);
	~CUVMaterialProgressDelegate() override;

	inline void setOffset(qreal offset);
	[[nodiscard]] inline qreal offset() const;

private:
	Q_DISABLE_COPY(CUVMaterialProgressDelegate)

	CUVMaterialProgress* const m_progress;
	qreal m_offset;
};

inline void CUVMaterialProgressDelegate::setOffset(const qreal offset) {
	m_offset = offset;
	m_progress->update();
}

inline qreal CUVMaterialProgressDelegate::offset() const {
	return m_offset;
}
