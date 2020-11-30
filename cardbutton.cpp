#include "cardbutton.h"
using namespace std;
CardButton::CardButton(const QString& value, int num, QWidget* parent):QPushButton(value,parent)
{

    this->value = value;
    this->setText("?");  //initially, text of the button is "?"
    this->num = num;

    QObject::connect(this, SIGNAL(clicked()),this, SLOT(change_value()));

}


// changes button's text to its value when it is clicked
void CardButton::change_value(){

    this->setText(this->value);

}
