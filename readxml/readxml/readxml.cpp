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
		QMessageBox::warning(NULL, "¾¯¸æ", "ÐÞ¸ÄÊ§°Ü!");
	}
	config.addXml();
	config.removeXml();
}
