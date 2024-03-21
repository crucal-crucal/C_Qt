//
// Created by crucal on 2024-03-17.
//
#pragma once

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "framelessdialog/framelessdialog.h"

class framelessdialog_p : public FramelessDialog {
  Q_OBJECT
  public:
	explicit framelessdialog_p(QWidget* parent = nullptr);

  private slots:
	void on_btnMin_clicked();
	void on_btnMax_clicked();
	void on_btnClose_clicked();

  private:
	void createCtrl();
	void layout();
	void initConnection();
	void initStyle();

  private:
	QLabel* m_pLbTitle{nullptr};

	QLabel* m_pLbTitleText{nullptr};
	QPushButton* m_pBtnMin{nullptr};
	QPushButton* m_pBtnMax{nullptr};
	QPushButton* m_pBtnClose{nullptr};

	QWidget* m_pCenterWidget{nullptr};

	QHBoxLayout* m_pHBoxLayTitle{nullptr};
	QVBoxLayout* m_pVBoxLayCenter{nullptr};
};

