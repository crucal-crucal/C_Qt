#pragma once

#include <QMainWindow>

class MainWidget : public QMainWindow {
public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget() override;

private:
	void createCtrl();
	void layout();
	void initConnection();

private:
};
