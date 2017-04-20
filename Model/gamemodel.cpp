#include "gamemodel.hpp"

#include <QDebug>
#include <QCoreApplication>

const int EMPTY_CELL = 0;
const int DEFAULT_VALUE = 0;

GameModel::GameModel(QObject *parent) :
    QObject(parent),
    _stats(qApp->applicationDirPath() + "/stats.ini", QSettings::IniFormat)
{
    connect(this, &GameModel::startGame, this, [=](int sideSize){
        m_gameFinished = false;
        m_winner = NO_WINNER;
        m_currentCell = INVALID_CELL;
        resizeField(sideSize);
        clearField();
    });

    m_score1 = _stats.value("Score1", DEFAULT_VALUE).toInt();
    m_score2 = _stats.value("Score2", DEFAULT_VALUE).toInt();
    m_totalGames = _stats.value("TotalGames", DEFAULT_VALUE).toInt();
}

void GameModel::changeTurn()
{
    m_currentPlayer = (m_currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
}

void GameModel::clearStats()
{
    m_score1 = m_score2 = m_totalGames = 0;
    _stats.setValue("Score1", DEFAULT_VALUE);
    _stats.setValue("Score2", DEFAULT_VALUE);
    _stats.setValue("TotalGames", DEFAULT_VALUE);
}

bool GameModel::isEqualToNextCell(CheckingType type, int column, int row)
{
    switch(type)
    {
    case Horizontal:
        if(m_field[column][row] == m_field[column][row + 1] && m_field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case Vertical:
        if(m_field[row][column] == m_field[row + 1][column] && m_field[row][column] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case MainDiagonal:
        if(m_field[column][row] == m_field[column + 1][row + 1] && m_field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case SecondaryDiagonal:
        if(m_field[column][row] == m_field[column + 1][row - 1] && m_field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    }
    return false;
}

bool GameModel::horizontalOrVerticalWin()
{
    for(size_t column = 0; column != m_field.size(); ++column)
    {
        int horizontalMatch = 0, verticalMatch = 0;
        for(size_t row = 0; row != m_field.size() - 1; ++row)
        {
            horizontalMatch = isEqualToNextCell(Horizontal, column, row) ? horizontalMatch + 1 : 0;
            verticalMatch = isEqualToNextCell(Vertical, column, row) ? verticalMatch + 1 : 0;

            if(horizontalMatch + 1 == m_winSequence || verticalMatch + 1 == m_winSequence)
                return true;
        }
    }
    return false;
}

bool GameModel::diagonalWin()
{
    // We shouldn't check 1 and 2 cells in a row because such sequence is not allowed
    for(size_t index = 0; index != m_field.size() - 2; ++index)
    {
        if(mainDiagonalWin(index) || secondaryDiagonalWin(index))
        {
            return true;
        }
    }
    return false;
}

bool GameModel::mainDiagonalWin(int currentIndex)
{
    int belowMainDigonal = 0, aboveMainDiagonal = 0;
    for(size_t column = currentIndex, row = 0; column != m_field.size() - 1; ++row, ++column)
    {
        belowMainDigonal = isEqualToNextCell(MainDiagonal, column, row) ? belowMainDigonal + 1 : 0;
        aboveMainDiagonal = isEqualToNextCell(MainDiagonal, row, column) ? aboveMainDiagonal + 1 : 0;

        if(belowMainDigonal + 1 == m_winSequence || aboveMainDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::secondaryDiagonalWin(int currentIndex)
{
    int belowSecondDigonal = 0, aboveSecondDiagonal = 0;
    for(size_t column = currentIndex, row = m_field.size() - 1; column != m_field.size() - 1; --row, ++column)
    {
        belowSecondDigonal = isEqualToNextCell(SecondaryDiagonal, column, row) ? belowSecondDigonal + 1 : 0;
        aboveSecondDiagonal = isEqualToNextCell(SecondaryDiagonal, m_field.size() - 1 - row, m_field.size() - 1 - column) ? aboveSecondDiagonal + 1 : 0;

        if(belowSecondDigonal + 1 == m_winSequence || aboveSecondDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

void GameModel::clearField()
{
    std::fill(m_field.begin(), m_field.end(), std::vector<int>(m_field.size(), EMPTY_CELL));
}

void GameModel::finishGame(Result result)
{
    switch(result)
    {
    case Winner1st:
        setScore1(m_score1 + 1);
        setWinner(m_currentPlayer);
        break;
    case Winner2nd:
        setScore2(m_score2 + 1);
        setWinner(m_currentPlayer);
        break;
    default:
        setWinner(NO_WINNER);
        break;
    }

    setTotalGames(m_totalGames + 1);
    m_gameFinished = true;
}

int GameModel::winner() const
{
    return m_winner;
}

void GameModel::setWinner(int winner)
{  
    m_winner = winner;
    emit winnerChange();
}

int GameModel::winSequence() const
{
    return m_winSequence;
}

void GameModel::setWinSequence(int winSequence)
{
    m_winSequence = winSequence;
}

int GameModel::cell() const
{
    return m_currentCell;
}

void GameModel::setCell(int cell)
{
    m_currentCell = cell;
    m_field[m_currentCell / m_field.size()][m_currentCell % m_field.size()] = m_currentPlayer;
    if(horizontalOrVerticalWin() || diagonalWin())
    {
        Result result = static_cast<Result>(m_currentPlayer);
        finishGame(result);
    }
    else
    {
        for(const auto& row : m_field)
        {
            auto foundIt = std::find(row.begin(), row.end(), EMPTY_CELL);
            if(foundIt != row.end())
                return;
        }
        finishGame(Draw);
    }
}

int GameModel::score1() const
{
    return m_score1;
}

void GameModel::setScore1(int player1Score)
{
    m_score1 = player1Score;
    _stats.setValue("Score1", player1Score);
    emit score1Change();
}

int GameModel::score2() const
{
    return m_score2;
}

void GameModel::setScore2(int player2Score)
{
    m_score2 = player2Score;
    _stats.setValue("Score2", player2Score);
    emit score2Change();
}

int GameModel::totalGames() const
{
    return m_totalGames;
}

void GameModel::setTotalGames(int totalGames)
{
    m_totalGames = totalGames;
    _stats.setValue("TotalGames", totalGames);
    emit totalGamesChanged();
}

int GameModel::currentPlayer() const
{
    return m_currentPlayer;
}

bool GameModel::gameFinished() const
{
    return m_gameFinished;
}

void GameModel::resizeField(size_t sideSize)
{
    if(sideSize != m_field.size())
    {
        for(auto& row : m_field)
        {
            row.resize(sideSize);
        }
        m_field.resize(sideSize);
    }
}
