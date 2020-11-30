#ifndef CARDTABLE_H
#define CARDTABLE_H
#include <QGridLayout>
#include <QMessageBox>
#include "timer.h"

#include "cardbutton.h"



class CardTable: public QGridLayout
{
    Q_OBJECT

public:
    CardTable(Timer *timer);
    Timer *timer;
    QLabel *score_lbl;    //label for score
    QMessageBox *message;
    QPushButton *pa;      //extra play again button for message box
    int score;            //keeps score
    int i;                //keeps track of number of clicks
    CardButton *cur_cards[2] = {nullptr, nullptr};    //stores currently clicked buttons

    void delay();

public slots:
    void is_finished();
    void check_click();   //click operations: controls, compares
};

#endif // CARDTABLE_H
