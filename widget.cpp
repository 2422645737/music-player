#include "widget.h"
#include "controller.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void Widget::initUI()         //初始化界面功能
{
    //设置初始大小
    this->resize(1100,650);

    //设置整体布局
    QGridLayout* mainLayout = new QGridLayout;
    this->setLayout(mainLayout);

    //设置底部控制栏
    Controller* controller = new Controller;
    controller->setMinimumHeight(80);
    mainLayout->addWidget(controller,0,0,Qt::AlignBottom);   //放置于底部



}

Widget::~Widget()
{
}

