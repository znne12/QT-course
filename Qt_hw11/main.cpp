#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "model.h"
#include <QDebug>
#include <QSqlError>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    qmlRegisterType<Model>("sqlModel", 1, 0, "Model");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
