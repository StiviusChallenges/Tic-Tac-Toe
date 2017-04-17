#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Model/gamemodel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<GameModel>("org.game.engine", 1, 0, "GameModel"); // QML and C++ integration
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
