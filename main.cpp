#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Model/gamemodel.hpp"
#include "Model/settingsmodel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<GameModel>("org.game.engine", 1, 0, "GameModel");
    qmlRegisterType<SettingsModel>("org.settings.model", 1, 0, "SettingsModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
