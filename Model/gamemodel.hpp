#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QObject>
#include "Model/settingsmodel.hpp"

const int NO_WINNER = 0;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;

class GameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int winner READ winner WRITE setWinner NOTIFY winnerChange)
    Q_PROPERTY(int currentPlayer READ currentPlayer)
    Q_PROPERTY(bool gameFinished READ gameFinished)

signals:
    void winnerChange();
    void startGame(int sideSize, int gameMode, int difficulty, int winSequence);
    void cellOccupied(int cell);

public:
    explicit GameModel(QObject* parent = nullptr);

    Q_INVOKABLE void setCellOccupied(int cel);
    Q_INVOKABLE void changeTurn();

    int winner() const;
    void setWinner(int winner);

    bool gameFinished() const;
    int currentPlayer() const;

private:
    enum Result {
        Draw,
        Winner1st,
        Winner2nd
    };

    enum CheckingType {
        Horizontal,
        Vertical,
        MainDiagonal,
        SecondaryDiagonal
    };

    bool isEqualToNextCell(CheckingType type, int column, int row);
    bool horizontalOrVerticalWin();
    bool diagonalWin();
    bool mainDiagonalWin(int currentIndex);
    bool secondaryDiagonalWin(int currentIndex);

    void finishGame(Result result);
    void clearField();
    void resizeField(size_t sideSize);
    void checkGameState();

private:
    std::vector<std::vector<int>> m_field;
    int m_winner = NO_WINNER;
    int m_currentPlayer = PLAYER_1;
    bool m_gameFinished = false;

    int m_winSequence = DEFAUT_WIN_SEQUENCE;
    int m_gameMode;
    int m_difficulty;

};


#endif // GAMEMODEL_HPP
