<<<<<<< HEAD
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFileInfo>
#include <QDir>
#include <QQmlContext>
#include <QMetaObject>
#include <QApplication>

#include "mainwindow.h"

//#define NDEBUG

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    MainWindow w;
    w.show();
//    QFileInfo fileInfo(__FILE__);
//    QString directoryName = fileInfo.dir().dirName();
//#ifdef NDEBUG
//    qDebug() << directoryName;
//#endif
//    QQmlApplicationEngine engine;

//    //    qmlRegisterType<CppObject>("MyCppObject",1,0,"CppObject");
////    const QUrl url("qrc:/" + directoryName + "/main.qml");
//    const QUrl url("qrc:/mian.qml");
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//        &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);

//    engine.load(url);

    //    My_Test t1;
    //    auto context = engine.rootContext();
    //    context->setContextProperty("My_Test", &t1);
    //    //    My_Test m_datas;
    //    //    QQmlContext *qmlctx = engine.rootContext();
    //    //    // 使用QQmlContex的setContextProperty()成员函数向QML运行上下文注册C++类型
    //    //    // 注册m_dadas
    //    //    qmlctx->setContextProperty("My_Test", &m_datas);

    //    // C++调用qml
    //    auto root = engine.rootObjects(); // 拿到所有对象列表

    //    // 找出列表中的第一个
    //    auto pushButton = root.first()->findChild<QObject *>("Btn");

    //    QObject::connect(pushButton,SIGNAL(signalInfo(int)), &t1, SLOT(slotInfo(int)));

    //    //    QVariant ret;
    //    //    // 调用上述实例化的名字，main.qml中对应的函数名，将返回到上述定义的ret中
    //    ////    QMetaObject::invokeMethod(labelqml, "getText", Q_RETURN_ARG(QVariant, ret));
    //    //    // 如果有参数要传入调用宏Q_ARG(QVariant, "参数")
    //    //    QMetaObject::invokeMethod(labelqml, "getText",Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, " jie"));

    //    //    qDebug() << ret.toString();
    return app.exec();
}
=======
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
