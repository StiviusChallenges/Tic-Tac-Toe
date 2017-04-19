#include "gamemodel.hpp"

#include <iostream>

const int EMPTY_CELL = 0;

GameModel::GameModel(QObject *parent) :
    QObject(parent), m_field(m_sideSize, std::vector<int>(m_sideSize, EMPTY_CELL))
{
    connect(this, &GameModel::restartGame, this, [=](){
        m_gameFinished = false;
        m_winner = 0;
        m_currentCell = -1;
        clearField();
    });
}

void GameModel::changeTurn()
{
    m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
}

bool GameModel::horizontalWin()
{
    for(int i = 0; i != m_sideSize; ++i)
    {
        int equations = 0;
        for(int j = 0; j != m_sideSize - 1; ++j)
        {
            if(m_field[i][j] == m_field[i][j + 1] && m_field[i][j] != 0)
            {
                ++equations;
                if(equations + 1 == m_winSequence)
                    return true;
            }
            else
            {
                equations = 0;
            }
        }
    }
    return false;
}

bool GameModel::verticalWin()
{
    for(int i = 0; i != m_sideSize; ++i)
    {
        int equations = 0;
        for(int j = 0; j != m_sideSize - 1; ++j)
        {
            if(m_field[j][i] == m_field[j + 1][i] && m_field[j][i] != 0)
            {
                ++equations;
                if(equations + 1 == m_winSequence)
                    return true;
            }
            else
            {
                equations = 0;
            }
        }
    }
    return false;
}

bool GameModel::isEqualToNextCell(Diagonal diagonal, int column, int row)
{
    if(diagonal == Main)
    {
        if(m_field[column][row] == m_field[column + 1][row + 1]
                && m_field[column][row] != 0)
        {
            return true;
        }
    }
    else
    {
        if(m_field[column][row] == m_field[column + 1][row - 1]
                && m_field[column][row] != 0)
        {
            return true;
        }
    }
    return false;
}

bool GameModel::mainDiagonalWin(int currentIndex)
{
    int belowMainDigonal = 0, aboveMainDiagonal = 0;
    for(int column = currentIndex, row = 0; column != m_sideSize - 1; ++row, ++column)
    {
        belowMainDigonal = isEqualToNextCell(Main, column, row) ? belowMainDigonal + 1 : 0;
        aboveMainDiagonal = isEqualToNextCell(Main, row, column) ? aboveMainDiagonal + 1 : 0;

        if(belowMainDigonal + 1 == m_winSequence || aboveMainDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::secondaryDiagonalWin(int currentIndex)
{
    int belowSecondDigonal = 0, aboveSecondDiagonal = 0;
    for(int column = currentIndex, row = m_sideSize - 1; column != m_sideSize - 1; --row, ++column)
    {
        belowSecondDigonal = isEqualToNextCell(Secondary, column, row) ? belowSecondDigonal + 1 : 0;
        aboveSecondDiagonal = isEqualToNextCell(Secondary, m_sideSize - 1 - row, m_sideSize - 1 - column) ? aboveSecondDiagonal + 1 : 0;

        if(belowSecondDigonal + 1 == m_winSequence || aboveSecondDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::diagonalWin()
{
    // We shouldn't check 1 and 2 cells in a row because such sequence is not allowed
    for(int index = 0; index != m_sideSize - 2; ++index)
    {
        if(mainDiagonalWin(index) || secondaryDiagonalWin(index))
        {
            return true;
        }
    }
    return false;
}

void GameModel::clearField()
{
    std::fill(m_field.begin(), m_field.end(), std::vector<int>(m_sideSize, EMPTY_CELL));
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

bool GameModel::gameFinished() const
{
    return m_gameFinished;
}

int GameModel::sideSize() const
{
    return m_sideSize;
}

void GameModel::setSideSize(int sideSize)
{
    m_sideSize = sideSize;
    emit sideSizeChanged();

    for(auto& row : m_field)
    {
        row.resize(m_sideSize);
    }
    m_field.resize(m_sideSize);
    emit restartGame();
}

int GameModel::totalGames() const
{
    return m_totalGames;
}

void GameModel::setTotalGames(int totalGames)
{
    m_totalGames = totalGames;
    emit totalGamesChanged();
}

int GameModel::winSequence() const
{
    return m_winSequence;
}

void GameModel::setWinSequence(int winSequence)
{
    m_winSequence = winSequence;
}

void GameModel::finishGame(ResultEnum result)
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
        setWinner(0);
        break;
    }

    setTotalGames(m_totalGames + 1);
    m_gameFinished = true;
}

int GameModel::cell() const
{
    return m_currentCell;
}

void GameModel::setCell(int cell)
{
    m_currentCell = cell;
    m_field[m_currentCell / m_sideSize][m_currentCell % m_sideSize] = m_currentPlayer;
    if(horizontalWin() || verticalWin() || diagonalWin())
    {
        ResultEnum result = static_cast<ResultEnum>(m_currentPlayer);
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

int GameModel::currentPlayer() const
{
    return m_currentPlayer;
}

void GameModel::setCurrentPlayer(int currentPlayer)
{
    m_currentPlayer = currentPlayer;
}

int GameModel::score1() const
{
    return m_score1;
}

void GameModel::setScore1(int player1Score)
{
    m_score1 = player1Score;
    emit score1Change();
}

int GameModel::score2() const
{
    return m_score2;
}

void GameModel::setScore2(int player2Score)
{
    m_score2 = player2Score;
    emit score2Change();
}
