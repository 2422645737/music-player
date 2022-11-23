#include "common.h"

void setColor(QWidget* widget){
    QPalette pal(widget->palette());
    pal.setColor(QPalette::Background,Qt::red);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
}



void print_music(Music music)
{
    qDebug() << "音乐名称：" << music.name;
    qDebug() << "音乐路径：" << music.path;
    qDebug() << "音乐后缀：" << music.suffix;
    qDebug() << "音乐时长：" << music.duration;
}
