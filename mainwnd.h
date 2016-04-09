#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include "board.h"
#include "ctrlpanel.h"

class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(int gameType, QWidget *parent = 0);
    ~MainWnd();

    int _gameType;

signals:

public slots:

};

#endif // MAINWND_H
