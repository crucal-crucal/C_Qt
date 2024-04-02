#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QGraphicsBlurEffect>

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
	void btn1_clicked();
	void btn2_clicked();
	void initForm();

  private:
	QWidget* m_pCenterWidget{nullptr};
	QPushButton* m_pBtn1{nullptr};
	QPushButton* m_pBtn2{nullptr};

	QHBoxLayout* m_pBtnHLayout{nullptr};
	QVBoxLayout* m_pCenterVLayout{nullptr};
	QDialog* d1{nullptr};
	QDialog* d2{nullptr};
};
