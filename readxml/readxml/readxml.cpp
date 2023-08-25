#include "readxml.h"

readxml::readxml(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	Manipulating_Xml config;
	QString str = config.readXml();
	ui.plainTextEdit->appendPlainText(str);
	qDebug() << (config.modifyXml() ? "修改成功" : "修改失败");
	qDebug() << (config.addXml() ? "添加成功" : "添加失败");
	qDebug() << (config.removeXml() ? "删除成功" : "删除失败");
}
