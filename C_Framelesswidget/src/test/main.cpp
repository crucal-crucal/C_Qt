//
// Created by crucal on 2024-03-17.
//
#include <QApplication>
#include <iostream>
#include "framelessdialog_p.h"
#include "test.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	framelessdialog_p w;
	w.show();
	return QApplication::exec();
}