//
// Created by crucal on 2024-03-17.
//
#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "framelessdialog_p.h"
#include "framelessmainwindow_p.h"
#include "framelesswidget_p.h"
#include "framelessMessageBox-1/uvmessagebox.h"
#include "framelessMessageBox-2/uvmessagebox.h"

class Q_DECL_EXPORT test : public QMainWindow {
  Q_OBJECT
  public:
	explicit test(QWidget* parent = nullptr);
	~test() override;

  private:
	void createCtrl();
	void layout();
	void initConnection();

  private:
	QPushButton* m_pBtnDialog{nullptr};
	QPushButton* m_pBtnWidget{nullptr};
	QPushButton* m_pBtnMainWindow{nullptr};
	QPushButton* m_pBtnMessageBox_1{nullptr};
	QPushButton* m_pBtnMessageBox_2{nullptr};

	QWidget* m_pCenterWidget{nullptr};

	QHBoxLayout* m_pHLayout{nullptr};
	QVBoxLayout* m_pCenterVLayout{nullptr};

	framelessdialog_p* m_pFramelsssDialog{nullptr};
	framelesswidget_p* m_pFramelsssWidget{nullptr};
	framelessmainwindow_p* m_pFramelsssMainwindow{nullptr};
};
