#include "settingsmodel.hpp"

#include <QCoreApplication>
#include <QDebug>

SettingsModel::SettingsModel(QObject *parent) :
    QObject(parent),
    _settings(qApp->applicationDirPath() + "/settings.ini", QSettings::IniFormat)
{
    m_sideSize = _settings.value("SideSize", 3).toInt();
    m_winSequence = _settings.value("WinSequence", 3).toInt();
    m_gameMode = _settings.value("GameMode", 1).toInt();
    m_difficulty = _settings.value("Difficulty", 1).toInt();
}

void SettingsModel::saveSettings()
{
    _settings.setValue("SideSize", m_sideSize);
    _settings.setValue("WinSequence", m_winSequence);
    _settings.setValue("GameMode", m_gameMode);
    _settings.setValue("Difficulty", m_difficulty);

    emit settingsUpdated();
}

int SettingsModel::sideSize() const
{
    return m_sideSize;
}

void SettingsModel::setSideSize(int sideSize)
{
    m_sideSize = sideSize;
    emit sideSizeChanged();
}

int SettingsModel::winSequence() const
{
    return m_winSequence;
}

void SettingsModel::setWinSequence(int winSequence)
{
    m_winSequence = winSequence;
    emit winSequenceChanged();
}

int SettingsModel::gameMode() const
{
    return m_gameMode;
}

void SettingsModel::setGameMode(int gameMode)
{
    m_gameMode = gameMode;
    emit gameModeChanged();
}

int SettingsModel::difficulty() const
{
    return m_difficulty;
}

void SettingsModel::setDifficulty(int difficulty)
{
    m_difficulty = difficulty;
    emit difficultyChanged();
}