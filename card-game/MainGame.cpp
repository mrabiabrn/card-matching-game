#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
//#include<ctime>

#include "restart.h"
#include "timer.h"
#include "cardbutton.h"
#include "cardtable.h"

using namespace std;

void set_button_clr(QPushButton *b);

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    //main window widget
    QWidget *mw = new QWidget();
    mw->resize(900,250);
    mw->setWindowTitle("Card Match Game");

    //game restarter
    Restart *r = new Restart();

    //timer
    Timer *tm = new Timer();
    //time out message box connections-> close(exit game), play again(starts a new game)
    QObject::connect(tm->mb->button(QMessageBox::Close), SIGNAL(clicked()),&app,SLOT(quit()));
    QObject::connect(tm->pa, SIGNAL(clicked()),r,SLOT(restarter()));

    //new game button
    QPushButton *newgame = new QPushButton("New Game");
    set_button_clr(newgame);
    QObject::connect(newgame, SIGNAL(clicked()), r, SLOT(restarter())); //new game -> restarts the game

    //quit button
    QPushButton *quitb = new QPushButton("Quit");
    set_button_clr(quitb);
    QObject::connect(quitb, SIGNAL(clicked()), &app, SLOT(quit())); //quit -> quits the game


    //grid of cards
    CardTable *table = new CardTable(tm);
    QObject::connect(table->message->button(QMessageBox::Close), SIGNAL(clicked()),&app,SLOT(quit()));
    QObject::connect(table->pa, SIGNAL(clicked()),r,SLOT(restarter()));

    QObject::connect(tm->timer,SIGNAL(timeout()), table, SLOT(is_finished()));

    // array of card texts
    string cardValues[30] = {"Camus","Camus","London","London","Tolstoy","Tolstoy",
                             "Márquez","Márquez","Kundera","Kundera","Flaubert","Flaubert",
                             "Zweig","Zweig","Hugo","Hugo","Hesse","Hesse",
                             "Saramago","Saramago","Kafka","Kafka","Hawking","Hawking",
                             "Dostoyevski","Dostoyevski","Foucault","Foucault","Atılgan","Atılgan"};


    srand(time(0));
    for(int r = 1; r <= 5; r++) {
        for(int c = 1; c <= 6; c++) {

            // randomly choose an index
            int indx;
            do {
                indx = rand()%30;
            }
            while(cardValues[indx] == "");

            // create and assign the value in array at chosen index to this cardbutton
            CardButton *b = new CardButton(QString::fromStdString(cardValues[indx]), 6*(r-1)+c,nullptr);
            set_button_clr(b);

            QObject::connect(b, SIGNAL(clicked()),table, SLOT(check_click()));
            table->addWidget(b,r,c,1,1);    //add the card button to card table grid

            cardValues[indx] = "";
        }
    }

    //horizontal layout : timer, score, spacer, newgame, quit
    QHBoxLayout *hl = new QHBoxLayout();
    QSpacerItem *hsi = new QSpacerItem(100, 0);
    hl->addWidget(tm->label);
    hl->addWidget(table->score_lbl);
    hl->addSpacerItem(hsi);
    hl->addWidget(newgame);
    hl->addWidget(quitb);

    //vertical layout : horizontal layout, spacer, grid
    QVBoxLayout *vl = new QVBoxLayout();
    QSpacerItem *vsi = new QSpacerItem(0, 50);
    vl->addLayout(hl);
    vl->addSpacerItem(vsi);
    vl->addLayout(table);

    //main window widget : vertical layout
    mw->setLayout(vl);
    mw->show();

    return app.exec();

}


//thickens edges of passed button parameter

void set_button_clr(QPushButton *b) {

    QPalette pal = b->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    b->setAutoFillBackground(true);
    b->setPalette(pal);
    b->update();

}
