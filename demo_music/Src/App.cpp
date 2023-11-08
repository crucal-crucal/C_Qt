#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

#include "HttpUtils.h"

int main(int argc, char* argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<HttpUtils>("MyUtils", 1, 0, "HttpUtils");

    app.setWindowIcon(QIcon(":/images/music.ico"));
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/QmlFile/App.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}