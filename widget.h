#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "common.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void initUI();        //初始化界面操作
    ~Widget();
};
#endif // WIDGET_H
