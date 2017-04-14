#include "gamemodel.hpp"

#include <QDebug>

const int SIDE_SIZE = 3;
const int EMPTY_CELL = 0;

GameModel::GameModel(QObject *parent) :
    QObject(parent), m_cells(SIDE_SIZE, std::vector<int>(SIDE_SIZE, EMPTY_CELL))
{
    connect(this, &GameModel::restartGame, this, [=](){
        m_gameFinished = false;
        clearCells();
    });
}

bool GameModel::horizontalWin()
{
    for(int i = 0; i != SIDE_SIZE; ++i)
    {
        int currentCell = m_cells[i][0];
        int count = 0;
        for(int j = 0; j != SIDE_SIZE; ++j)
        {
            if(currentCell != m_cells[i][j] || currentCell == 0)
                break;
            ++count;
        }

        if(count == SIDE_SIZE)
            return true;
    }
    return false;
}

bool GameModel::verticalWin()
{
    for(int j = 0; j != SIDE_SIZE; ++j)
    {
        int currentCell = m_cells[0][j];
        int count = 0;
        for(int i = 0; i != SIDE_SIZE; ++i)
        {
            if(currentCell != m_cells[i][j] || currentCell == 0)
                break;
            ++count;
        }

        if(count == SIDE_SIZE)
            return true;
    }
    return false;
}

bool GameModel::diagonalWin()
{
    int firstCount = 0, secondCount = 0;
    int currentFirstCell = m_cells[0][0];
    int currentSecondCell = m_cells[0][SIDE_SIZE - 1];
    for(int i = 0; i != SIDE_SIZE; ++i)
    {
        if(currentFirstCell == m_cells[i][i] && currentFirstCell != 0)
            firstCount++;

        if(currentSecondCell == m_cells[i][SIDE_SIZE - 1 - i] && currentSecondCell != 0)
            secondCount++;
    }

    if(firstCount == SIDE_SIZE)
        return true;
    else if(secondCount == SIDE_SIZE)
        return true;

    return false;
}

void GameModel::clearCells()
{
    std::fill(m_cells.begin(), m_cells.end(), std::vector<int>(SIDE_SIZE, EMPTY_CELL));
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

void GameModel::finishGame()
{
    if(m_currentPlayer == 1)
        setScore1(m_score1 + 1);
    else
        setScore2(m_score2 + 1);

    m_gameFinished = true;
    setWinner(m_currentPlayer);
}

int GameModel::cell() const
{
    return m_currentCell;
}

void GameModel::setCell(int cell)
{
    m_currentCell = cell;
    m_cells[m_currentCell / SIDE_SIZE][m_currentCell % SIDE_SIZE] = m_currentPlayer;
    if(horizontalWin() || verticalWin() || diagonalWin())
    {
        finishGame();
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
