#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class person : public QObject
{
    Q_OBJECT

    //QT中类的属性是给脚本和元对象系统使用的，比如QtScript,QML,或者QObject::property/setProperty等，主要是用来进行属性封装在具体的脚本库
    //qml开发中必须使用
    //宏（定义宏之只能用空格隔开，不能用逗号
    //定义一个属性age，类型是int，读age的方式是readAge(), 写age的方式是setAge()
    //NOTIFY后面跟的是当前类已经定义的一个信号函数，只要该属性（age 发生更改，就会发出该信号，这个信号函数必须采用0个或1个参数，并且参数的属性必须和属性的类型相同
    //当age属性发生变化时，会发射ageChanged信号，需要在类相关定义添加emit进行信号发送
    Q_PROPERTY(int age READ readAge WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name)
public:
    //构造函数，防止隐式转换
    explicit person(QString name, int age, QObject *parent = nullptr)
    {
        m_name = name;
        m_age = age;
    }

    int readAge()
    {
        return m_age;
    }
    void setAge(int value)
    {
        m_age = value;
        emit ageChanged(value);
    }
signals:
    void ageChanged(int v);

private:
    QString m_name;
    int m_age;
};

#endif // PERSON_H
