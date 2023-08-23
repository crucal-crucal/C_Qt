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

class Config
{
public:
	Config();

	QString readConfig(); // ¶ÁÈ¡Xml ÎÄ¼þ
	bool modifyXml();
};