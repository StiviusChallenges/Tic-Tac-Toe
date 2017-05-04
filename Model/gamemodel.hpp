#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QObject>
#include "Model/settingsmodel.hpp"

const int NO_WINNER = 0;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;
const int INVALID_CELL = -1;

using Matrix = std::vector<std::vector<int>>;
using Decision = std::pair<int, int>;

class GameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int winner READ winner WRITE setWinner NOTIFY winnerChange)
    Q_PROPERTY(int currentPlayer READ currentPlayer)
    Q_PROPERTY(bool gameFinished READ gameFinished)
    Q_PROPERTY(bool gameStarted READ gameStarted)

signals:
    void winnerChange();
    void startGame(int sideSize, int difficulty, int winSequence, int gameMode, int computerTurn = -1);
    void cellOccupied(int cell);

public:
    explicit GameModel(QObject* parent = nullptr);

    Q_INVOKABLE void setCellOccupied(int cel);
    Q_INVOKABLE void changeTurn();

    int winner() const;
    void setWinner(int winner);

    bool gameFinished() const;
    bool gameStarted() const;

    int currentPlayer() const;

private:
    enum State {
        Draw,
        Winner1st,
        Winner2nd,
        None
    };

    enum CheckingType {
        Horizontal,
        Vertical,
        MainDiagonal,
        SecondaryDiagonal
    };

    bool isEqualToNextCell(const Matrix& field, CheckingType type, int column, int row);
    bool horizontalOrVerticalWin(const Matrix& field);
    bool diagonalWin(const Matrix& field);
    bool mainDiagonalWin(const Matrix& field, int currentIndex);
    bool secondaryDiagonalWin(const Matrix& field, int currentIndex);

    void finishGame(State state);
    void clearField();
    void resizeField(size_t sideSize);
    void checkGameState();

    State checkGameState(const Matrix& field, int currentPlayer);
    Decision calculate(Matrix field, int turn, int cell = INVALID_CELL);
    int getScore(State result);
    Decision minimax(std::map<int, int> scores, int currentPlayer);
    void makeAMovement();

private:
    Matrix m_field;
    int m_winner = NO_WINNER;
    int m_currentPlayer = PLAYER_1;
    bool m_gameFinished = true;
    bool m_gameStarted = false;

    int m_winSequence = DEFAUT_WIN_SEQUENCE;
    int m_gameMode;
    int m_difficulty;
    int m_computerTurn = -1;

};


#endif // GAMEMODEL_HPP
