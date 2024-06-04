#ifndef QTMATERIALDIALOG_H
#define QTMATERIALDIALOG_H

#include "lib/uvmaterialoverlaywidget.hpp"

class QLayout;
class CUVMaterialDialogPrivate;

class CUVMaterialDialog final : public CUVMaterialOverlayWidget {
	Q_OBJECT

public:
	explicit CUVMaterialDialog(QWidget* parent = nullptr);
	~CUVMaterialDialog() override;

	[[nodiscard]] QLayout* windowLayout() const;
	void setWindowLayout(QLayout* layout);

public slots:
	void showDialog();
	void hideDialog();

protected:
	void paintEvent(QPaintEvent* event) override;

	const QScopedPointer<CUVMaterialDialogPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CUVMaterialDialog)
	Q_DECLARE_PRIVATE(CUVMaterialDialog)
};

#endif // QTMATERIALDIALOG_H
