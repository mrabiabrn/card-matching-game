#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include <QPushButton>
#include <QLabel>


class CardButton: public QPushButton
{
    Q_OBJECT

public:
    CardButton(const QString& value, int num, QWidget* parent = 0);
    QString value;
    int num;         //unique number belongs to this card button


    public slots:
    void change_value();
};



#endif // CARDBUTTON_H
