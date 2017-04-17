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
    Q_PROPERTY(int sideSize READ sideSize WRITE setSideSize NOTIFY sideSizeChanged)
    Q_PROPERTY(int totalGames READ totalGames WRITE setTotalGames NOTIFY totalGamesChanged)
    Q_PROPERTY(int winSequence READ winSequence WRITE setWinSequence)
    Q_PROPERTY(bool gameFinished READ gameFinished)

signals:
    void score1Change();
    void score2Change();
    void winnerChange();
    void restartGame();
    void sideSizeChanged();
    void totalGamesChanged();

public:
    explicit GameModel(QObject* parent = nullptr);

    Q_INVOKABLE void changeTurn();

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

    int sideSize() const;
    void setSideSize(int sideSize);

    int totalGames() const;
    void setTotalGames(int totalGames);

    int winSequence() const;
    void setWinSequence(int winSequence);

private:
    enum ResultEnum {
        Draw,
        Winner1st,
        Winner2nd
    };

    void finishGame(ResultEnum result);
    bool horizontalWin();
    bool verticalWin();
    bool diagonalWin();
    void clearField();

private:
    std::vector<std::vector<int>> m_field;
    int m_winner = 0;
    int m_currentCell = -1;
    int m_score1 = 0;
    int m_score2 = 0;
    int m_currentPlayer = 1;
    int m_sideSize = 3;
    int m_totalGames = 0;
    bool m_gameFinished = false;
    int m_winSequence = 3;
};


#endif // GAMEMODEL_HPP
