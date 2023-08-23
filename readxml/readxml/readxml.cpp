#include "readxml.h"

readxml::readxml(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	Manipulating_Xml config;
	QString str = config.readXml();
	ui.plainTextEdit->appendPlainText(str);

	bool err = config.modifyXml();
	if (!err) {
		QMessageBox::warning(NULL, "¾¯¸æ", "ÐÞ¸ÄÊ§°Ü!");
	}
	config.addXml();
	config.removeXml();
}
