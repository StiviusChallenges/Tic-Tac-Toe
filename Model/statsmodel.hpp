#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <QObject>
#include <QSettings>

class StatsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score1 READ score1)
    Q_PROPERTY(int score2 READ score2)
    Q_PROPERTY(int totalGames READ totalGames)

public:
    explicit StatsModel(QObject *parent = nullptr);

    Q_INVOKABLE void clearStats();
    Q_INVOKABLE static void updateStats(int winner);

    int score1() const;
    int score2() const;
    int totalGames() const;

private:
    QSettings _stats;
    int m_score1;
    int m_score2;
    int m_totalGames;

};

#endif // STATSMODEL_H
