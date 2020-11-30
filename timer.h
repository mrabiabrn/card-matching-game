#ifndef TIMER_H
#define TIMER_H
#include <QLabel>
#include <QTimer>
#include <QMessageBox>


class Timer: public QObject
{
     Q_OBJECT

public:
    Timer();
    QLabel *label;
    QTimer *timer;
    QMessageBox *mb;
    QPushButton *pa;  // extra play again button for message box
    int cnt;          // counts seconds

public slots:
    void inc_timer();

};

#endif // TIMER_H
