#include "mainwidget.hpp"

MainWidget::MainWidget(QWidget* parent): QMainWindow(parent) {
	setAttribute(Qt::WA_DeleteOnClose);
	createCtrl();
	layout();
	initConnection();
	resize(800, 600);
}

MainWidget::~MainWidget() = default;

void MainWidget::createCtrl() {
}

void MainWidget::layout() {
}

void MainWidget::initConnection() {
}
