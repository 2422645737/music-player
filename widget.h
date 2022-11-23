#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "common.h"
#include "controller.h"
#include "musiclist.h"
#include "musicinfo.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    QMediaPlayer* player;
    musicInfo* music_info_widget;
    MusicList* music_list_widget;
    Controller* controller;
    void init();      //初始化操作
    void initUI();        //初始化界面操作
    void initConnect();    //初始化connect

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void music_changed(QString path);
};
#endif // WIDGET_H
