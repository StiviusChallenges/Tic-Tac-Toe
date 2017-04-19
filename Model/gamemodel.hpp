#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QObject>
#include "Model/settingsmodel.hpp"

const int NO_WINNER = 0;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;
const int INVALID_CELL = -1;

class GameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score1 READ score1 WRITE setScore1 NOTIFY score1Change)
    Q_PROPERTY(int score2 READ score2 WRITE setScore2 NOTIFY score2Change)
    Q_PROPERTY(int totalGames READ totalGames WRITE setTotalGames NOTIFY totalGamesChanged)
    Q_PROPERTY(int winner READ winner WRITE setWinner NOTIFY winnerChange)
    Q_PROPERTY(int currentCell READ cell WRITE setCell)
    Q_PROPERTY(int currentPlayer READ currentPlayer)
    Q_PROPERTY(int winSequence READ winSequence WRITE setWinSequence)
    Q_PROPERTY(bool gameFinished READ gameFinished)

signals:
    void score1Change();
    void score2Change();
    void totalGamesChanged();
    void winnerChange();
    void startGame(int sideSize);

public:
    explicit GameModel(QObject* parent = nullptr);

    Q_INVOKABLE void changeTurn();

    int score1() const;
    void setScore1(int);

    int score2() const;
    void setScore2(int);

    int totalGames() const;
    void setTotalGames(int totalGames);

    int cell() const;
    void setCell(int);

    int winner() const;
    void setWinner(int);

    int winSequence() const;
    void setWinSequence(int winSequence);

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

private:
    int m_winSequence = DEFAUT_WIN_SEQUENCE;
    std::vector<std::vector<int>> m_field;
    QSettings _stats;
    int m_winner = NO_WINNER;
    int m_currentCell = INVALID_CELL;
    int m_score1;
    int m_score2;
    int m_totalGames;
    int m_currentPlayer = PLAYER_1;
    bool m_gameFinished = false;

};


#endif // GAMEMODEL_HPP
