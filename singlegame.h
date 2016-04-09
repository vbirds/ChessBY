#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"

class SingleGame : public Board
{
    Q_OBJECT
public:
    SingleGame();
    virtual void click(int id, int row, int col);

    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);

    void fakeMove(Step* step);
    void unfakeMove(Step* step);

    int  calScore();
    int getMinScore(int level, int curMaxScore);
    int getMaxScore(int level, int curMinScore);

    int _level;


signals:
    void sigBack();

public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
