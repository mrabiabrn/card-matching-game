#include "cardtable.h"
#include "QLabel"
#include "QTime"
#include "QCoreApplication"
#include "cardbutton.h"



CardTable::CardTable(Timer *timer): QGridLayout()
{
    this->timer = timer;
    this->score = 0;
    this->score_lbl = new QLabel("Score: 0");

    //message box with two buttons
    this->message = new QMessageBox();
    //standart close button
    this->message->setStandardButtons(QMessageBox::Close);
    //play again button is added
    pa = new QPushButton("Play Again!");
    message->addButton(pa, QMessageBox::AcceptRole);

    this->message->setStyleSheet("QLabel{min-width: 300px;}");
    this->message->setText("You won!");


    this->i = 0;
}


void CardTable::delay()
{

    QTime delayTime = QTime::currentTime().addMSecs(800);
    while (QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void CardTable::is_finished() {
    if(this->timer->cnt == 180 || this->score == 15) {
        for (int i = 0; i < this->count(); i++)
            {
              CardButton *b = qobject_cast<CardButton*>(this->itemAt(i)->widget());
              b->setEnabled(false);
           }

    }
}

void CardTable::check_click(){


    this->i++;
    if(this->i == 1) { //one click, add card to array
        cur_cards[0] = qobject_cast<CardButton *>(sender());
    }
    else if(this->i == 2) { //two click, control if matches

        cur_cards[1] = qobject_cast<CardButton *>(sender());

        //clicking same button twice, still one card is visible
        if(cur_cards[0]->num == cur_cards[1]->num)
            this->i--;

        //2 different button click
        else {

            //disable all card buttons except the clicked ones
            for (int i = 0; i < this->count(); i++)
                {
                  CardButton *b = qobject_cast<CardButton*>(this->itemAt(i)->widget());
                  if(b->num != cur_cards[0]->num && b->num != cur_cards[1]->num)
                     b->setEnabled(false);
               }

            // put a delay in order to see the second card's text
            this->delay();

            //matching cards
            if(cur_cards[0]->text() == cur_cards[1]->text()){
                this->score++;
                this->score_lbl->setText("Score: " + QString::number(this->score));

                //control if player wins
                if(this->score == 15) {

                    this->timer->timer->stop();

                    cur_cards[0]->setText(""); cur_cards[0]->setEnabled(false);
                    cur_cards[1]->setText(""); cur_cards[1]->setEnabled(false);

                    this->message->exec(); //execute message box

                }

            //disable matching cards
            cur_cards[0]->setText(""); cur_cards[0]->setEnabled(false);
            cur_cards[1]->setText(""); cur_cards[1]->setEnabled(false);

            }

            //two cards do not match
            else {
                cur_cards[0]->setText("?");
                cur_cards[1]->setText("?");

            }

        //clean clicked button's info to store new clicks
        cur_cards[0] =nullptr; cur_cards[1] =nullptr;
        this->i = 0;



        //enable all buttons except matched ones
        for (int i = 0; i < this->count(); ++i)
            {
              CardButton *b = qobject_cast<CardButton*>(this->itemAt(i)->widget());
              if(b->text() != "")
                  b->setEnabled(true);
           }

        this->is_finished();

    }

}

}
