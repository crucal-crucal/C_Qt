#pragma once

#include <QObject>

#include "uvmaterialcircularprogress.hpp"

class CUVMaterialCircularProgressDelegate final : public QObject {
	Q_OBJECT

	Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
	Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
	Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
	explicit CUVMaterialCircularProgressDelegate(CUVMaterialCircularProgress* parent);
	~CUVMaterialCircularProgressDelegate() override;

	inline void setDashOffset(qreal offset);
	[[nodiscard]] inline qreal dashOffset() const;

	inline void setDashLength(qreal length);
	[[nodiscard]] inline qreal dashLength() const;

	inline void setAngle(int angle);
	[[nodiscard]] inline int angle() const;

private:
	Q_DISABLE_COPY(CUVMaterialCircularProgressDelegate)

	CUVMaterialCircularProgress* const m_progress;
	qreal m_dashOffset;
	qreal m_dashLength;
	int m_angle;
};

inline void CUVMaterialCircularProgressDelegate::setDashOffset(const qreal offset) {
	m_dashOffset = offset;
	m_progress->update();
}

inline qreal CUVMaterialCircularProgressDelegate::dashOffset() const {
	return m_dashOffset;
}

inline void CUVMaterialCircularProgressDelegate::setDashLength(const qreal length) {
	m_dashLength = length;
	m_progress->update();
}

inline qreal CUVMaterialCircularProgressDelegate::dashLength() const {
	return m_dashLength;
}

inline void CUVMaterialCircularProgressDelegate::setAngle(const int angle) {
	m_angle = angle;
	m_progress->update();
}

inline int CUVMaterialCircularProgressDelegate::angle() const {
	return m_angle;
}
