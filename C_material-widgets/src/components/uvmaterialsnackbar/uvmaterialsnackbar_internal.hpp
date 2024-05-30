#pragma once

#include <QStateMachine>
#include <QTimer>

class CUVMaterialSnackbar;

class CUVMaterialSnackbarStateMachine final : public QStateMachine {
	Q_OBJECT

	Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	explicit CUVMaterialSnackbarStateMachine(CUVMaterialSnackbar* parent);
	~CUVMaterialSnackbarStateMachine() override;

	void setOffset(qreal offset);
	[[nodiscard]] inline qreal offset() const;

public slots:
	void progress();

protected slots:
	void snackbarShown();

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Q_DISABLE_COPY(CUVMaterialSnackbarStateMachine)

	CUVMaterialSnackbar* const m_snackbar{ nullptr };
	QTimer m_timer{};
	qreal m_offset{};
};

inline qreal CUVMaterialSnackbarStateMachine::offset() const {
	return m_offset;
}
