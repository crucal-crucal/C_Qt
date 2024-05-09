//
// Created by crucal on 2024-03-17.
//
#pragma once

#include <QMainWindow>

#include "framelessdialog_p.hpp"
#include "framelessmainwindow_p.hpp"
#include "framelesswidget_p.hpp"
#include "framelessMessageBox-1/uvmessagebox.hpp"
#include "framelessMessageBox-2/uvmessagebox.hpp"
#include "uvframelesshelper/framelesshelper.hpp"

class Q_DECL_EXPORT test final : public QMainWindow {
	Q_OBJECT

public:
	explicit test(QWidget* parent = nullptr);
	~test() override;

private:
	void createCtrl();
	void layoutcustom() const;
	void initConnection();

	QPushButton* m_pBtnDialog{ nullptr };
	QPushButton* m_pBtnWidget{ nullptr };
	QPushButton* m_pBtnMainWindow{ nullptr };
	QPushButton* m_pBtnMessageBox_1{ nullptr };
	QPushButton* m_pBtnMessageBox_2{ nullptr };
	QPushButton* m_pBtnFramelesshelper{ nullptr };

	QWidget* m_pCenterWidget{ nullptr };

	QHBoxLayout* m_pHLayout{ nullptr };
	QVBoxLayout* m_pCenterVLayout{ nullptr };

	framelessdialog_p* m_pFramelessDialog{ nullptr };
	framelesswidget_p* m_pFramelessWidget{ nullptr };
	framelessmainwindow_p* m_pFramelessMainwindow{ nullptr };

	QxFrameless::FramelessHelper* m_pFramelsssHelper{ nullptr };
	QWidget* m_pFramelessHelperWidget{ nullptr };
};
