#include "choosedlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(_buttons[0] = new QPushButton("人机对战"));

    for(int i=0; i<1; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<1; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_selected = i;
            break;
        }
    }
    accept();
}

ChooseDlg::~ChooseDlg()
{

}

