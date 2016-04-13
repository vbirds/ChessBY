#include "singlegame.h"
#include <QTimer>

SingleGame::SingleGame()
{
    this->_level = 5;
}

void SingleGame::click(int id, int row, int col)
{
    if( !(this->_bRedTurn) )
    {
        return;
    }

    Board::click(id, row, col);

    if( !(this->_bRedTurn) )
    {
        /*启动定时器0.1秒，在0.1秒后电脑再思考*/
        QTimer::singleShot(100, this, SLOT(computerMove()));
    }

}

void SingleGame::computerMove()
{
    Step* tmp;
    tmp = getBestMove();

    moveStone(tmp->_moveid, tmp->_killid, tmp->_rowTo, tmp->_colTo);

    delete tmp;
    update();
}



Step* SingleGame::getBestMove()
{
    /*
     * 1.试有哪些步骤可以走
     * 2.走着试一下
     * 3.评估走的结果
     * 4.取最好的作为参考
    */
    QVector<Step *> step;
    getAllPossibleMove(step);

    int maxScore = -100000;
    Step* ret = NULL;

    while(step.count())
    {
        Step* tmp = step.back();
        step.removeLast();

        fakeMove(tmp);
        int score = getMinScore(_level - 1, maxScore);
        unfakeMove(tmp);

        if(score > maxScore)
        {
            maxScore = score;
            if(ret)
            {
                delete ret;
            }
            ret = tmp;
        }
        else
        {
            delete tmp;
        }

    }

    return ret;
}

void SingleGame::judgedOver(int id, int &minRow, int &maxRow, int &minCol, int &maxCol)
{
    minRow = (minRow < 0) ? _s[id]._row : minRow;
    maxRow = (maxRow >9 ) ? _s[id]._row : maxRow;
    minCol = (minCol < 0) ? _s[id]._col : minCol;
    maxCol = (maxCol < 0) ? _s[id]._col : maxCol;
}

void SingleGame::getPossibleMove(int id, int &minRow, int &maxRow,
                                 int &minCol, int &maxCol)
{
    switch (_s[id]._type) {
    case Stone::BING:
        minRow = _s[id]._row -1;
        maxRow = _s[id]._row +1;
        minCol = _s[id]._col -1;
        maxCol = _s[id]._col +1;

        judgedOver(id, minRow, maxRow, minCol, maxCol);
        break;
    case Stone::MA:
        minRow = _s[id]._row -2;
        maxRow = _s[id]._row +2;
        minCol = _s[id]._col -2;
        maxCol = _s[id]._col +2;

        judgedOver(id, minRow, maxRow, minCol, maxCol);
        break;
    case Stone::PAO:
        minRow = 0;
        maxRow = 9;
        minCol = 0;
        maxCol = 8;
        break;
    case Stone::CHE:
        minRow = 0;
        maxRow = 9;
        minCol = 0;
        maxCol = 8;
        break;
    case Stone::XIANG:
        minRow = _s[id]._row -2;
        maxRow = _s[id]._row +2;
        minCol = _s[id]._col -2;
        maxCol = _s[id]._col +2;

        judgedOver(id, minRow, maxRow, minCol, maxCol);
        break;
    case Stone::SHI:
        if(isBottomSide(id))
        {
            minRow = 0;
            maxRow = 2;
        }
        else
        {
            minRow = 7;
            maxRow = 9;
        }
        minCol = 3;
        maxCol = 5;

        break;
    case Stone::JIANG:
        if(isBottomSide(id))
        {
            minRow = 0;
            maxRow = 2;
        }
        else
        {
            minRow = 7;
            maxRow = 9;
        }
        minCol = 3;
        maxCol = 5;

        break;
    }
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min = 16, max = 32;
    int minRow = 0, maxRow = 0;
    int minCol = 0, maxCol = 0;
    if(this->_bRedTurn)
    {
        min = 0, max = 16;
    }

    for(int i=min; i<max; ++i)
    {
        if(_s[i]._dead)
        {
            continue;
        }

        /*
         * title: 优化枚举走棋步骤算法。
         * name: jhz
         * time: 2015/04/09
         * scription:
         * 1.原来的算法把整个棋盘遍历，效率太低。
         * 2.根据棋子走棋规则的特点，优化遍历的边界，
         *   减少遍历的次数
        */
        getPossibleMove(i, minRow, maxRow, minCol, maxCol);

        for(int row=minRow; row < maxRow; ++row)
        {
            for(int col=minCol; col < maxCol; ++col)
            {
                int killid = getStoneId(row, col);
                if(sameColor(killid, i))
                {
                    continue;
                }
                if(canMove(i, killid, row, col))
                {
                    saveStep(i, killid, row, col, steps);
                }

            }
        }

#if 0
        /*原枚举走棋步骤算法*/
        /*
        for(int row=0; row<9; ++row)
        {
            for(int col=0; col<8; ++col)
            {
                int killid = getStoneId(row, col);
                if(sameColor(killid, i))
                {
                    continue;
                }
                if(canMove(i, killid, row, col))
                {
                    saveStep(i, killid, row, col, steps);
                }

            }
        }
        */
#endif
    }
}


void SingleGame::fakeMove(Step *step)
{
    killStone(step->_killid);
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

void SingleGame::unfakeMove(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);

}

/*评价局面分*/
int SingleGame::calScore()
{
    int redTotalScore = 0;
    int blackTotalScore = 0;
    //enum TYPE{JIANG, CHE, PAO, MA, BING, SHI, XIANG};
    static int chessScore[] = {1500, 100, 50, 50, 20, 10, 10};

    for(int i = 0; i < 16; ++i)
    {
        if(_s[i]._dead)
        {
            continue;
        }
        redTotalScore += chessScore[_s[i]._type];
    }
    for(int i = 16; i < 32; ++i)
    {
        if(_s[i]._dead)
        {
            continue;
        }
        blackTotalScore += chessScore[_s[i]._type];
    }

    return blackTotalScore - redTotalScore;
}

int SingleGame::getMinScore(int level, int curMaxScore)
{
    /*递归终局条件*/
    if(level == 0)
    {
        return calScore();
    }

    int minScore = 100000;
    QVector<Step*> steps;
    getAllPossibleMove(steps);

    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMaxScore(level-1, minScore);
        unfakeMove(step);
        delete step;

        if(score <= curMaxScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score < minScore)
        {
            minScore = score;
        }

    }

    return minScore;
}

int SingleGame::getMaxScore(int level, int curMinScore)
{
    /*递归终局条件*/
    if(level == 0)
    {
        return calScore();
    }

    int maxScore = -100000;
    QVector<Step*> steps;
    getAllPossibleMove(steps);

    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level-1, maxScore);
        unfakeMove(step);
        delete step;

        if(score >= curMinScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if(score > maxScore)
        {
            maxScore = score;
        }
    }

    return maxScore;
}
