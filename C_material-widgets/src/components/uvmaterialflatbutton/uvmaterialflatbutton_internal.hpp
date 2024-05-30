#pragma once

#include <QColor>
#include <QStateMachine>

class CUVMaterialFlatButton;
class QSequentialAnimationGroup;

class CUVMaterialFlatButtonStateMachine final : public QStateMachine {
	Q_OBJECT

	Q_PROPERTY(qreal overlayOpacity WRITE setOverlayOpacity READ overlayOpacity)
	Q_PROPERTY(qreal checkedOverlayProgress WRITE setCheckedOverlayProgress READ checkedOverlayProgress)
	Q_PROPERTY(qreal haloOpacity WRITE setHaloOpacity READ haloOpacity)
	Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
	Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
	explicit CUVMaterialFlatButtonStateMachine(CUVMaterialFlatButton* parent);
	~CUVMaterialFlatButtonStateMachine() override;

	void setOverlayOpacity(qreal opacity);
	[[nodiscard]] inline qreal overlayOpacity() const;

	void setCheckedOverlayProgress(qreal progress);
	[[nodiscard]] inline qreal checkedOverlayProgress() const;

	void setHaloOpacity(qreal opacity);
	[[nodiscard]] inline qreal haloOpacity() const;

	void setHaloSize(qreal size);
	[[nodiscard]] inline qreal haloSize() const;

	void setHaloScaleFactor(qreal factor);
	[[nodiscard]] inline qreal haloScaleFactor() const;

	void startAnimations();
	void setupProperties();
	void updateCheckedStatus();

signals:
	void buttonPressed();
	void buttonChecked();
	void buttonUnchecked();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Q_DISABLE_COPY(CUVMaterialFlatButtonStateMachine)

	void addTransition(QObject* object, QEvent::Type eventType, QState* fromState, QState* toState);
	void addTransition(QAbstractTransition* transition, QState* fromState, QState* toState);

	CUVMaterialFlatButton* const m_button;
	QState* const m_topLevelState;
	QState* const m_configState;
	QState* const m_checkableState;
	QState* const m_checkedState;
	QState* const m_uncheckedState;
	QState* const m_neutralState;
	QState* const m_neutralFocusedState;
	QState* const m_hoveredState;
	QState* const m_hoveredFocusedState;
	QState* const m_pressedState;
	QSequentialAnimationGroup
	* const m_haloAnimation;
	qreal m_overlayOpacity;
	qreal m_checkedOverlayProgress;
	qreal m_haloOpacity;
	qreal m_haloSize;
	qreal m_haloScaleFactor;
	bool m_wasChecked;
};

inline qreal CUVMaterialFlatButtonStateMachine::overlayOpacity() const {
	return m_overlayOpacity;
}

inline qreal CUVMaterialFlatButtonStateMachine::checkedOverlayProgress() const {
	return m_checkedOverlayProgress;
}

inline qreal CUVMaterialFlatButtonStateMachine::haloOpacity() const {
	return m_haloOpacity;
}

inline qreal CUVMaterialFlatButtonStateMachine::haloSize() const {
	return m_haloSize;
}

inline qreal CUVMaterialFlatButtonStateMachine::haloScaleFactor() const {
	return m_haloScaleFactor;
}
