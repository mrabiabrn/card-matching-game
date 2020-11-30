#include "timer.h"
#include <QPushButton>

Timer::Timer(): QObject()
  {
    this->timer = new QTimer();
    this->label = new QLabel("Time(secs): 0");

    this->mb = new QMessageBox();
    mb->setStandardButtons(QMessageBox::Close);
    pa = new QPushButton("Play Again!");
    mb->addButton(pa, QMessageBox::AcceptRole); //default button


    mb->setText("You lost!");
    mb->setStyleSheet("QLabel{min-width: 300px;}");

    this->cnt = 0;
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(inc_timer()));

    this->timer->start(1000);
}

//Increments count per second
void Timer::inc_timer() {

    this->cnt++;
    if(this->cnt > 180) {
        this->timer->stop();
        mb->exec();
       }
    this->label->setText("Time(secs): " + QString::number(this->cnt));



}



