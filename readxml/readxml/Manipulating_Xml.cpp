#include "Manipulating_Xml.h"

Manipulating_Xml::Manipulating_Xml() {}

QString Manipulating_Xml::readXml() {
	QFile file;
	QString nodename;
	QString Output;

	file.setFileName(QApplication::applicationDirPath() + "/Config/testconfig.xml");
	qDebug() << QApplication::applicationDirPath();
	if (!file.exists()) {
		qDebug() << "testconfig.xml 文件不存在";
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "打开文件失败";
	}
	else {
		QXmlStreamReader xmlreader(&file);
		qDebug() << "xml文件存在，打开成功!";
		while (!xmlreader.atEnd() || !xmlreader.hasError()) {
			xmlreader.readNextStartElement();
			nodename = xmlreader.name().toString();
			if (nodename == "Data" && xmlreader.isStartElement()) {
				xmlreader.attributes().value("id").toString();
				Output.append(QString("ID:%1").arg(xmlreader.attributes().value("id").toString()));
				Output.push_back("\n");
				while (!(nodename == "Data" && xmlreader.isEndElement())) {
					xmlreader.readNextStartElement();
					nodename = xmlreader.name().toString();
					if (nodename == "Number" && xmlreader.isStartElement()) {
						while (!(nodename == "Number" && xmlreader.isEndElement())) {
							Output.append(QString("Number:%1").arg(xmlreader.readElementText()));
							Output.push_back("\n");
						}
					}
					else if (nodename == "Name" && xmlreader.isStartElement()) {
						while (!(nodename == "Name" && xmlreader.isEndElement())) {
							Output.append(QString("Name:%1").arg(xmlreader.readElementText()));
							Output.push_back("\n");
						}
					}
					else if (nodename == "email" && xmlreader.isStartElement()) {
						while (!(nodename == "email" && xmlreader.isEndElement())) {
							Output.append(QString("email:%1").arg(xmlreader.readElementText()));
							Output.push_back("\n");
						}
					}
					else if (nodename == "website" && xmlreader.isStartElement()) {
						while (!(nodename == "website" && xmlreader.isEndElement())) {
							Output.append(QString("website:%1").arg(xmlreader.readElementText()));
							Output.push_back("\n");
							Output.append("------------------\n");
						}
					}
				}
			}
		}
	}
	file.close();
	return Output;
}

bool Manipulating_Xml::modifyXml()
{
	QFile file;
	QString filePath = QApplication::applicationDirPath() + "/Config/test.xml";
	file.setFileName(filePath);
	if (!file.open(QFile::ReadOnly))
		return false;

	//更新一个标签项,如果知道xml的结构，直接定位到那个标签上定点更新
	//或者用遍历的方法去匹配tagname或者attribut，value来更新
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return false;
	}
	file.close();

	QDomElement root = doc.documentElement();
	QDomNodeList list = root.elementsByTagName("book");
	QDomNode node = list.at(list.size() - 1).firstChild(); //定位到第三个一级子节点的子元素
	QDomNode oldnode = node.firstChild(); //标签之间的内容作为节点的子节点出现,当前是Pride and Projudice
	node.firstChild().setNodeValue("Crucal");
	QDomNode newnode = node.firstChild();
	node.replaceChild(newnode, oldnode);

	if (!file.open(QFile::WriteOnly | QFile::Truncate))
		return false;
	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格

	file.close();
	return true;
}

bool Manipulating_Xml::addXml()
{
	QFile file;
	QString filePath = QApplication::applicationDirPath() + "/Config/test.xml";
	file.setFileName(filePath);
	if (!file.open(QFile::ReadOnly))
		return false;

	//增加一个一级子节点以及元素
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return false;
	}
	file.close();

	QDomElement root = doc.documentElement();
	QDomElement book = doc.createElement("book");
	book.setAttribute("id", 3);
	book.setAttribute("time", "1813/1/27");
	QDomElement title = doc.createElement("title");
	QDomText text;
	text = doc.createTextNode("Pride and Prejudice");
	title.appendChild(text);
	book.appendChild(title);
	QDomElement author = doc.createElement("author");
	text = doc.createTextNode("Jane Austen");
	author.appendChild(text);
	book.appendChild(author);
	root.appendChild(book);

	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //先读进来，再重写，如果不用truncate就是在后面追加内容，就无效了
		return false;
	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格
	file.close();
	return true;
}

bool Manipulating_Xml::removeXml()
{    
	QFile file;
	QString filePath = QApplication::applicationDirPath() + "/Config/test.xml";
	file.setFileName(filePath);
	if (!file.open(QFile::ReadOnly))
		return false;

	//删除一个一级子节点及其元素，外层节点删除内层节点于此相同
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return false;
	}
	file.close();  //一定要记得关掉啊，不然无法完成操作

	QDomElement root = doc.documentElement();
	QDomNodeList list = doc.elementsByTagName("book"); //由标签名定位
	for (int i = 0; i<list.count(); i++)
	{
		QDomElement e = list.at(i).toElement();
		if (e.attribute("time") == "1813/1/27")  //以属性名定位，类似于hash的方式，warning：这里仅仅删除一个节点，其实可以加个break
			root.removeChild(list.at(i));
	}

	if (!file.open(QFile::WriteOnly | QFile::Truncate))
		return false;
	//输出到文件
	QTextStream out_stream(&file);
	doc.save(out_stream, 4); //缩进4格
	file.close();
	return true;
}
