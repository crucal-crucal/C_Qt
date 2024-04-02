#ifndef ZH_TO_PY_H
#define ZH_TO_PY_H

//#define NDEBUG

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QMutex>
#include <QApplication>
#include <iostream>
#include <cctype>

class ZH_TO_PY : public QObject
{
    Q_OBJECT
public:
    static ZH_TO_PY *Instance();
    explicit ZH_TO_PY(QObject *parent = nullptr);

private:
    // 管理动态分配内存，确保在对象生命周期结束时自动释放资源，从而避免出现内存泄露
    static QScopedPointer<ZH_TO_PY> self;
    QStringList listPY; // 拼音全写
    QStringList listJP; // 拼音简写

public:
    // 载入拼音文件
    void LoadPY(const QString &filename = "zhtopy.txt");
    // 汉字转拼音
    QString zhToPY(const QString &chinese);
    // 汉字转字母简写
    QString zhToJP(const QString &chinese);
    // 汉字转首字母
    QString zhToZM(const QString &chinese);
};

#endif // ZH_TO_PY_H
