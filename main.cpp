#include <QApplication>
#include "choosedlg.h"
#include "mainwnd.h"
#include <QTime>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTime t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    ChooseDlg dlg;
    if(dlg.exec() != QDialog::Accepted)
        return 0;

    MainWnd wnd(dlg._selected);
    wnd.show();


    return app.exec();
}
