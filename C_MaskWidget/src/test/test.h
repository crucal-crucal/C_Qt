#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

#include "MaskWidget/MaskWidget.h"

class test : public QMainWindow {
  Q_OBJECT
  public:
	explicit test(QWidget* parent = nullptr);
	~test() override;

  private:
	void createCtrl();
	void layout();
	void initConnection();

  private slots:
	void btn_clicked();
	void initForm();

  private:
	QWidget* m_pCenterWidget{nullptr};
	QPushButton* m_pBtn{nullptr};

	QHBoxLayout* m_pBtnHLayout{nullptr};
	QVBoxLayout* m_pCenterVLayout{nullptr};
	QDialog* d{nullptr};
};
