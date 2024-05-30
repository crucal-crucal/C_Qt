#include "uvmaterialsnackbar_internal.hpp"

#include <QDebug>
#include <QPropertyAnimation>

#include "uvmaterialsnackbar.hpp"
#include "lib/uvmaterialstatetransition.hpp"

CUVMaterialSnackbarStateMachine::CUVMaterialSnackbarStateMachine(CUVMaterialSnackbar* parent): QStateMachine(parent), m_snackbar(parent) {
	m_timer.setSingleShot(true);

	const auto hiddenState = new QState;
	const auto visibleState = new QState;
	const auto finalState = new QState;

	addState(hiddenState);
	addState(visibleState);
	addState(finalState);

	setInitialState(hiddenState);

	auto transition = new CUVMaterialStateTransition(SnackbarShowTransition);
	transition->setTargetState(visibleState);
	hiddenState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarHideTransition);
	transition->setTargetState(visibleState);
	hiddenState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarHideTransition);
	transition->setTargetState(finalState);
	visibleState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarWaitTransition);
	transition->setTargetState(hiddenState);
	finalState->addTransition(transition);

	transition = new CUVMaterialStateTransition(SnackbarNextTransition);
	transition->setTargetState(visibleState);
	finalState->addTransition(transition);

	connect(visibleState, &QState::propertiesAssigned, this, &CUVMaterialSnackbarStateMachine::snackbarShown);
	connect(finalState, &QState::propertiesAssigned, m_snackbar, &CUVMaterialSnackbar::dequeue);

	const auto animation = new QPropertyAnimation(this, "offset", this);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	animation->setDuration(300);
	addDefaultAnimation(animation);

	hiddenState->assignProperty(this, "offset", 0);
	visibleState->assignProperty(this, "offset", 1);
	finalState->assignProperty(this, "offset", 0);

	connect(&m_timer, &QTimer::timeout, this, &CUVMaterialSnackbarStateMachine::progress);

	m_snackbar->installEventFilter(this);
}

CUVMaterialSnackbarStateMachine::~CUVMaterialSnackbarStateMachine() = default;

bool CUVMaterialSnackbarStateMachine::eventFilter(QObject* watched, QEvent* event) {
	if (QEvent::MouseButtonPress == event->type() && m_snackbar->clickToDismissMode()) {
		progress();
	}
	return QStateMachine::eventFilter(watched, event);
}

void CUVMaterialSnackbarStateMachine::setOffset(const qreal offset) {
	m_offset = offset;
	m_snackbar->update();
}

void CUVMaterialSnackbarStateMachine::progress() {
	m_timer.stop();
	postEvent(new CUVMaterialStateTransitionEvent(SnackbarHideTransition));
	if (m_snackbar->clickToDismissMode()) {
		m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	}
}

void CUVMaterialSnackbarStateMachine::snackbarShown() {
	m_timer.start(m_snackbar->autoHideDuration());
	if (m_snackbar->clickToDismissMode()) {
		m_snackbar->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	}
}
