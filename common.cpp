#include "common.h"

void setColor(QWidget* widget){
    QPalette pal(widget->palette());
    pal.setColor(QPalette::Background,Qt::red);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
}
