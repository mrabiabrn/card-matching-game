#ifndef RESTART_H
#define RESTART_H
#include <QObject>


class Restart: public QObject
{
    Q_OBJECT

public:
    Restart();

public slots:
    void restarter();

};

#endif // RESTART_H
