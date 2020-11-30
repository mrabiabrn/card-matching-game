#include "restart.h"
#include <QProcess>
#include <QApplication>

Restart::Restart(): QObject()
{

}

void Restart::restarter() {
    //global pointer referring to app terminates it
    qApp->quit();
    //start app again
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
