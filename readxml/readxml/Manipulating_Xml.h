#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif
#pragma once
#include <QXmlStreamReader>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

/*
 对于 Xml 文件的增删查改操作
*/
class Manipulating_Xml
{
public:
	Manipulating_Xml();

public:
	QString readXml(); // 读取Xml 文件
	bool modifyXml(); // 修改Xml 文件
	void addXml(); // 增加Xml 文件
	void removeXml(); // 删除xml 文件
};