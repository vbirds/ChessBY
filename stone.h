#ifndef STONE_H
#define STONE_H

#include <QString>

class Stone
{
public:
    Stone();
    ~Stone();

    void init(int id);

    enum TYPE{JIANG, CHE, PAO, MA, BING, SHI, XIANG};

    int     _row;   //行
    int     _col;   //列
    int     _id;    //id
    bool    _dead;  //是否死
    bool    _red;   //是否红方
    TYPE    _type;  //类型

    QString getText();

    void rotate();

};

#endif // STONE_H
