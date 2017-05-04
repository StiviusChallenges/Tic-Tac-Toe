#include "gamemodel.hpp"

#include <QDebug>
#include <QCoreApplication>
#include <algorithm>
#include <map>

#include "Model/statsmodel.hpp"

const int EMPTY_CELL = 0;
const int WIN_FIRST_SCORE = 10;
const int WIN_SECOND_SCORE = -10;
const int DRAW_SCORE = 0;

GameModel::GameModel(QObject* parent) :
    QObject(parent)
{
    connect(this, &GameModel::startGame, this, [=](int sideSize, int difficulty, int winSequence,
                                                   int gameMode, int computerTurn = -1){
        m_gameFinished = false;
        m_gameStarted = true;
        m_gameMode = gameMode;
        m_difficulty = difficulty;
        m_winSequence = winSequence;
        m_winner = NO_WINNER;
        m_currentPlayer = PLAYER_1;
        resizeField(sideSize);
        clearField();

        if(computerTurn != -1) {
            m_computerTurn = computerTurn;
            makeAMovement();
        }
    });
    srand(time(NULL));
}

void GameModel::changeTurn()
{
    m_currentPlayer = (m_currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
    makeAMovement();
}

void GameModel::makeAMovement()
{
    if(m_currentPlayer == m_computerTurn && m_gameMode == SettingsModel::Computer)
    {
        auto p = calculate(m_field, m_currentPlayer);
        qDebug() << "final decision: " << p.second << "; cell: " << p.first;
        if(p.first != INVALID_CELL)
        {
            setCellOccupied(p.first);
        }
    }
}

bool GameModel::isEqualToNextCell(const Matrix& field, CheckingType type, int column, int row)
{
    switch(type)
    {
    case Horizontal:
        if(field[column][row] == field[column][row + 1] && field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case Vertical:
        if(field[row][column] == field[row + 1][column] && field[row][column] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case MainDiagonal:
        if(field[column][row] == field[column + 1][row + 1] && field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    case SecondaryDiagonal:
        if(field[column][row] == field[column + 1][row - 1] && field[column][row] != EMPTY_CELL)
        {
            return true;
        }
        break;
    }
    return false;
}

bool GameModel::horizontalOrVerticalWin(const Matrix& field)
{
    for(size_t column = 0; column != field.size(); ++column)
    {
        int horizontalMatch = 0, verticalMatch = 0;
        for(size_t row = 0; row != field.size() - 1; ++row)
        {
            horizontalMatch = isEqualToNextCell(field, Horizontal, column, row) ? horizontalMatch + 1 : 0;
            verticalMatch = isEqualToNextCell(field, Vertical, column, row) ? verticalMatch + 1 : 0;

            if(horizontalMatch + 1 == m_winSequence || verticalMatch + 1 == m_winSequence)
                return true;
        }
    }
    return false;
}

bool GameModel::diagonalWin(const Matrix& field)
{
    // We shouldn't check 1 and 2 cells in a row because such sequence is not allowed
    for(size_t index = 0; index != field.size() - 2; ++index)
    {
        if(mainDiagonalWin(field, index) || secondaryDiagonalWin(field, index))
        {
            return true;
        }
    }
    return false;
}

bool GameModel::mainDiagonalWin(const Matrix& field, int currentIndex)
{
    int belowMainDigonal = 0, aboveMainDiagonal = 0;
    for(size_t column = currentIndex, row = 0; column != field.size() - 1; ++row, ++column)
    {
        belowMainDigonal = isEqualToNextCell(field, MainDiagonal, column, row) ? belowMainDigonal + 1 : 0;
        aboveMainDiagonal = isEqualToNextCell(field, MainDiagonal, row, column) ? aboveMainDiagonal + 1 : 0;

        if(belowMainDigonal + 1 == m_winSequence || aboveMainDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

bool GameModel::secondaryDiagonalWin(const Matrix& field, int currentIndex)
{
    int belowSecondDigonal = 0, aboveSecondDiagonal = 0;
    for(size_t column = currentIndex, row = field.size() - 1; column != field.size() - 1; --row, ++column)
    {
        belowSecondDigonal = isEqualToNextCell(field, SecondaryDiagonal, column, row) ? belowSecondDigonal + 1 : 0;
        aboveSecondDiagonal = isEqualToNextCell(field, SecondaryDiagonal, field.size() - 1 - row, field.size() - 1 - column) ? aboveSecondDiagonal + 1 : 0;

        if(belowSecondDigonal + 1 == m_winSequence || aboveSecondDiagonal + 1 == m_winSequence)
            return true;
    }
    return false;
}

void GameModel::clearField()
{
    std::fill(m_field.begin(), m_field.end(), std::vector<int>(m_field.size(), EMPTY_CELL));
}

void GameModel::finishGame(State result)
{
    switch(result)
    {
    case Winner1st:
        setWinner(m_currentPlayer);
        break;
    case Winner2nd:
        setWinner(m_currentPlayer);
        break;
    case Draw:
        setWinner(NO_WINNER);
        break;
    default:
        break;
    }
    m_gameFinished = true;
    m_gameStarted = false;
}

int GameModel::winner() const
{
    return m_winner;
}

void GameModel::setWinner(int winner)
{  
    m_winner = winner;
    StatsModel::updateStats(winner);
    emit winnerChange();
}

void GameModel::setCellOccupied(int cell)
{
    m_field[cell / m_field.size()][cell % m_field.size()] = m_currentPlayer;
    State currentState = checkGameState(m_field, m_currentPlayer);
    if(currentState != None)
        finishGame(currentState);
    emit cellOccupied(cell);
}


GameModel::State GameModel::checkGameState(const Matrix& field, int currentPlayer)
{
    if(horizontalOrVerticalWin(field) || diagonalWin(field))
    {
        return static_cast<State>(currentPlayer);
    }
    else
    {
        for(const auto& row : field)
        {
            auto foundIt = std::find(row.begin(), row.end(), EMPTY_CELL);
            if(foundIt != row.end())
                return None;
        }
        return Draw;
    }
}

int GameModel::currentPlayer() const
{
    return m_currentPlayer;
}

bool GameModel::gameFinished() const
{
    return m_gameFinished;
}

bool GameModel::gameStarted() const
{
    return m_gameStarted;
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

int GameModel::getScore(State state)
{
    switch(state)
    {
    case Winner1st:
        return WIN_FIRST_SCORE;
    case Winner2nd:
        return WIN_SECOND_SCORE;
    case Draw:
        return DRAW_SCORE;
    default:
        break;
    }
    return -1;
}

Decision GameModel::getRandomCorrectDecision(int decisionValue, std::map<int, int> scores)
{
    std::vector<Decision> correctDecisions;
    for(const auto& p : scores)
    {
        if(p.second == decisionValue)
            correctDecisions.push_back(p);
    }
    return correctDecisions[rand() % correctDecisions.size()];
}

Decision GameModel::minimax(std::map<int, int> scores, int currentPlayer)
{
    std::map<int, int>::iterator decision;
    if(currentPlayer == PLAYER_1)
    {
        decision = std::max_element(scores.begin(), scores.end(), [=](const auto& p1, const auto& p2){
           return p1.second < p2.second;
        });
    }
    else
    {
        decision = std::min_element(scores.begin(), scores.end(), [=](const auto& p1, const auto& p2){
           return p1.second < p2.second;
        });
    }
    auto randCorrectDecision = getRandomCorrectDecision(decision->second, scores);
    return std::make_pair(randCorrectDecision.first, randCorrectDecision.second);
}

Decision GameModel::calculate(Matrix field, int currentPlayer, int cell)
{
    if(cell != INVALID_CELL)
        field[cell / field.size()][cell % field.size()] = currentPlayer;

    auto state = checkGameState(field, currentPlayer);
    if(state != None)
        return std::make_pair(cell, getScore(state));

    if(cell != INVALID_CELL)
        currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
    int tempTurn = currentPlayer;

    std::map<int, int> scores;
    for(size_t i = 0; i != field.size() * field.size(); ++i)
    {
        if(field[i / field.size()][i % field.size()] == EMPTY_CELL)
        {
            int score = calculate(field, currentPlayer, i).second;
            scores[i] = score;
            currentPlayer = tempTurn;
        }
    }
    return minimax(scores, currentPlayer);
}
