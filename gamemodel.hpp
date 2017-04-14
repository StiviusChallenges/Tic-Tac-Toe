#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include <QObject>
#include <QVector>

class GameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentPlayer READ currentPlayer WRITE setCurrentPlayer)
    Q_PROPERTY(int score1 READ score1 WRITE setScore1 NOTIFY score1Change)
    Q_PROPERTY(int score2 READ score2 WRITE setScore2 NOTIFY score2Change)
    Q_PROPERTY(int currentCell READ cell WRITE setCell)
    Q_PROPERTY(int winner READ winner WRITE setWinner NOTIFY winnerChange)
    Q_PROPERTY(bool gameFinished READ gameFinished)

signals:
    void score1Change();
    void score2Change();
    void winnerChange();
    void restartGame();

public:
    explicit GameModel(QObject* parent = nullptr);

    int currentPlayer() const;
    void setCurrentPlayer(int);

    int score1() const;
    void setScore1(int);

    int score2() const;
    void setScore2(int);

    int cell() const;
    void setCell(int);

    int winner() const;
    void setWinner(int);

    bool gameFinished() const;

private:
    void finishGame();
    bool horizontalWin();
    bool verticalWin();
    bool diagonalWin();
    void clearCells();

private:
    std::vector<std::vector<int>> m_cells;
    int m_winner = 0;
    int m_currentCell = -1;
    int m_score1 = 0;
    int m_score2 = 0;
    int m_currentPlayer = 1;
    bool m_gameFinished = false;

};


#endif // GAMEMODEL_HPP
