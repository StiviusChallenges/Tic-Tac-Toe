#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Model/gamemodel.hpp"
#include "Model/settingsmodel.hpp"
#include "Model/statsmodel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<GameModel>("org.game.engine", 1, 0, "GameModel");
    qmlRegisterType<SettingsModel>("org.settings.model", 1, 0, "SettingsModel");
    qmlRegisterType<StatsModel>("org.stats.model", 1, 0, "StatsModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
