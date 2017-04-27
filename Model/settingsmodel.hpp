#ifndef SETTINGSMODEL_HPP
#define SETTINGSMODEL_HPP

#include <QObject>
#include <QSettings>

const int DEFAULT_SIDE_SIZE = 3;
const int DEFAUT_WIN_SEQUENCE = 3;

class SettingsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sideSize READ sideSize WRITE setSideSize NOTIFY sideSizeChanged)
    Q_PROPERTY(int winSequence READ winSequence WRITE setWinSequence NOTIFY winSequenceChanged)
    Q_PROPERTY(GameMode gameMode READ gameMode WRITE setGameMode NOTIFY gameModeChanged)
    Q_PROPERTY(Difficulty difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)

signals:
    void settingsUpdated();
    void sideSizeChanged();
    void winSequenceChanged();
    void gameModeChanged();
    void difficultyChanged();

public:
    enum GameMode {
        Computer = 1,
        TwoPlayers
    };
    Q_ENUM(GameMode)

    enum Difficulty {
        Easy = 1,
        Medium,
        Hard
    };
    Q_ENUM(Difficulty)

    explicit SettingsModel(QObject *parent = nullptr);

    Q_INVOKABLE void saveSettings();

    int sideSize() const;
    void setSideSize(int sideSize);

    int winSequence() const;
    void setWinSequence(int winSequence);

    GameMode gameMode() const;
    void setGameMode(GameMode gameMode);

    Difficulty difficulty() const;
    void setDifficulty(Difficulty difficulty);

private:
    int m_sideSize;
    int m_winSequence;
    GameMode m_gameMode;
    Difficulty m_difficulty;
    QSettings _settings;

};

#endif // SETTINGSMODEL_HPP
