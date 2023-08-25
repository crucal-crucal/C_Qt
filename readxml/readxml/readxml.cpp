#include "readxml.h"

readxml::readxml(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	QString filePath = QApplication::applicationDirPath() + "/Config/testconfig.xml";
	QString str = Manipulating_Xml::readXml(filePath);
	ui.plainTextEdit->appendPlainText(str);

	filePath = QApplication::applicationDirPath() + "/Config/test.xml";
	qDebug() << (Manipulating_Xml::modifyXml(filePath) ? "修改成功" : "修改失败");
	qDebug() << (Manipulating_Xml::addXml(filePath) ? "添加成功" : "添加失败");
	qDebug() << (Manipulating_Xml::removeXml(filePath) ? "删除成功" : "删除失败");
}
