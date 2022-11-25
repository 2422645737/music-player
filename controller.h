#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QProgressBar>
#include "common.h"

class Controller : public QWidget
{
    Q_OBJECT
private:
    void init();        //初始化
    void initUI();       //初始化界面
public:
    explicit Controller(QWidget* parent = nullptr);

signals:

};

#endif // CONTROLLER_H
