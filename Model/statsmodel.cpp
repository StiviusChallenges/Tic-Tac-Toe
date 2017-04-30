#include "statsmodel.hpp"

#include <QCoreApplication>
#include <QDebug>

const int DEFAULT_VALUE = 0;
const int NO_WINNER = 0;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

StatsModel::StatsModel(QObject *parent) :
    QObject(parent)
{
    QSettings stats(qApp->applicationDirPath() + "/stats.ini", QSettings::IniFormat);
    m_score1 = stats.value("Score1", DEFAULT_VALUE).toInt();
    m_score2 = stats.value("Score2", DEFAULT_VALUE).toInt();
    m_totalGames = stats.value("TotalGames", DEFAULT_VALUE).toInt();
}

void StatsModel::clearStats()
{
    QSettings stats(qApp->applicationDirPath() + "/stats.ini", QSettings::IniFormat);
    m_score1 = m_score2 = m_totalGames = 0;
    stats.setValue("Score1", DEFAULT_VALUE);
    stats.setValue("Score2", DEFAULT_VALUE);
    stats.setValue("TotalGames", DEFAULT_VALUE);
}

void StatsModel::updateStats(int winner)
{
    QSettings stats(qApp->applicationDirPath() + "/stats.ini", QSettings::IniFormat);
    int score1 = stats.value("Score1", DEFAULT_VALUE).toInt();
    int score2 = stats.value("Score2", DEFAULT_VALUE).toInt();
    int totalGames = stats.value("TotalGames", DEFAULT_VALUE).toInt();

    switch(winner)
    {
    case PLAYER_1:
        stats.setValue("Score1", score1 + 1);
        break;
    case PLAYER_2:
        stats.setValue("Score2", score2 + 1);
        break;
    default:
        break;
    }
    stats.setValue("TotalGames", totalGames + 1);
}

int StatsModel::score1() const
{
    return m_score1;
}

int StatsModel::score2() const
{
    return m_score2;
}

int StatsModel::totalGames() const
{
    return m_totalGames;
}
