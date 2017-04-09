#include "gamemodel.hpp"

const int FIELD_SIZE = 9;

GameModel::GameModel(QObject *parent) : QObject(parent), m_cells(FIELD_SIZE)
{
    std::fill(m_cells.begin(), m_cells.end(), 0);
    m_currentPlayer = 1;
    m_score1 = m_score2 = m_winner = 0;
}

void GameModel::checkField() // check if one of the player wins
{
    for(int i = 0; i != FIELD_SIZE; i += 3)
    {
        if(m_cells[i] == m_cells[i+1] && m_cells[i+1] == m_cells[i+2] && m_cells[i] == m_cells[i+2]) // vertical
        {
            if(m_cells[i] != 0)
            {
                m_winner = m_cells[i];
                std::fill(m_cells.begin(), m_cells.end(), 0);
                return;
            }
        }
    }
    for(int i = 0; i != 3; i++)
    {
        if(m_cells[i] == m_cells[i+3] && m_cells[i+3] == m_cells[i+6] && m_cells[i] == m_cells[i+6]) // horizontal
        {
            if(m_cells[i] != 0)
            {
                m_winner = m_cells[i];
                std::fill(m_cells.begin(), m_cells.end(), 0);
                return;
            }
        }
    }
    if(m_cells[0] == m_cells[4] && m_cells[4] == m_cells[8] && m_cells[0] == m_cells[8]) // 1st diagonal
    {
        if(m_cells[0] != 0)
        {
            m_winner = m_cells[0];
            std::fill(m_cells.begin(), m_cells.end(), 0);
            return;
        }

    }
    else if(m_cells[2] == m_cells[4] && m_cells[4] == m_cells[6] && m_cells[2] == m_cells[6]) // 2nd diagonal
    {
        if(m_cells[2] != 0)
        {
            m_winner = m_cells[2];
            std::fill(m_cells.begin(), m_cells.end(), 0);
            return;
        }
    }
}

int GameModel::winner() const
{
    return m_winner;
}

void GameModel::setWinner(int wnr)
{
    m_winner = wnr;
    emit winnerChange();
}

int GameModel::cell() const
{
    return m_currentCell;
}

void GameModel::setCell(int cell)
{
    m_currentCell = cell;
    m_cells[m_currentCell] = m_currentPlayer;
    checkField();
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
