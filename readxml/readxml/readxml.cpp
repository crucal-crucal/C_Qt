#include "readxml.h"

readxml::readxml(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	Config config;
	QString str = config.readConfig();
	ui.plainTextEdit->appendPlainText(str);

	bool err = config.modifyXml();
	if (!err) {
		QMessageBox::warning(NULL, "警告", "修改失败!");
	}
	else {
		QMessageBox::information(NULL, "提示", "修改成功!");
	}
}
