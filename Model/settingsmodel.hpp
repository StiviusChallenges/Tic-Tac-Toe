#ifndef SETTINGSMODEL_HPP
#define SETTINGSMODEL_HPP

#include <QObject>
#include <QSettings>

class SettingsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sideSize READ sideSize WRITE setSideSize NOTIFY sideSizeChanged)
    Q_PROPERTY(int winSequence READ winSequence WRITE setWinSequence NOTIFY winSequenceChanged)
    Q_PROPERTY(int gameMode READ gameMode WRITE setGameMode NOTIFY gameModeChanged)
    Q_PROPERTY(int difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)

signals:
    void settingsUpdated();
    void sideSizeChanged();
    void winSequenceChanged();
    void gameModeChanged();
    void difficultyChanged();

public:
    explicit SettingsModel(QObject *parent = nullptr);

    Q_INVOKABLE void saveSettings();

    int sideSize() const;
    void setSideSize(int sideSize);

    int winSequence() const;
    void setWinSequence(int winSequence);

    int gameMode() const;
    void setGameMode(int gameMode);

    int difficulty() const;
    void setDifficulty(int difficulty);

private:
    int m_sideSize;
    int m_winSequence;
    int m_gameMode;
    int m_difficulty;
    QSettings _settings;

};

#endif // SETTINGSMODEL_HPP
