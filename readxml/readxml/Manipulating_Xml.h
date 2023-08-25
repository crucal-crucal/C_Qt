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
	/*************************************************
	* @arg: 需要读取的 Xml 文件路径
	* @Fun: 读取Xml文件到 plainTextEdit 控件中
	* @return: 读取到的字符串 QString
	* **********************************************/
	static QString readXml(QString filePath); 
	/*************************************************
	* @arg: 需要修改的 Xml 文件路径
	* @Fun: 修改 Xml 文件的数据
	* @return: 修改成功 true，修改失败 false
	* **********************************************/
	static bool modifyXml(QString filePath);
	/*************************************************
	* @arg: 需要添加的 Xml 文件路径
	* @Fun: 添加数据到 Xml 文件中
	* @return: 添加成功 true，添加失败 false
	* **********************************************/
	static bool addXml(QString filePath);
	/*************************************************
	* @arg: 需要删除的 Xml 文件路径
	* @Fun: 删除 Xml 文件中的数据
	* @return: 删除成功 true，删除失败 false
	* **********************************************/
	static bool removeXml(QString filePath);
};