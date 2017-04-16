#include "gamemodel.hpp"

#include <QDebug>

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
        int currentCell = m_field[i][0];
        int count = 0;
        for(int j = 0; j != m_sideSize; ++j)
        {
            if(currentCell != m_field[i][j] || currentCell == 0)
                break;
            ++count;
        }

        if(count == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::verticalWin()
{
    for(int j = 0; j != m_sideSize; ++j)
    {
        int currentCell = m_field[0][j];
        int count = 0;
        for(int i = 0; i != m_sideSize; ++i)
        {
            if(currentCell != m_field[i][j] || currentCell == 0)
                break;
            ++count;
        }

        if(count == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::diagonalWin()
{
    int firstCount = 0, secondCount = 0;
    int currentFirstCell = m_field[0][0];
    int currentSecondCell = m_field[0][m_sideSize - 1];
    for(int i = 0; i != m_sideSize; ++i)
    {
        if(currentFirstCell == m_field[i][i] && currentFirstCell != 0)
            firstCount++;

        if(currentSecondCell == m_field[i][m_sideSize - 1 - i] && currentSecondCell != 0)
            secondCount++;
    }

    if(firstCount == m_winSequence)
        return true;
    else if(secondCount == m_winSequence)
        return true;

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
