#include "controller.h"

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    init();
}
void Controller::init()
{
    initUI();
}

void Controller::initUI()
{
    //用于测试颜色，方便观察颜色
    setColor(this);

    //初始化控制栏界面
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QPushButton* play_button = new QPushButton;      //播放按钮
    play_button->setText("播放");

    QPushButton* prev_button = new QPushButton;      //上一首
    prev_button->setText("上一首");

    QPushButton* next_button = new QPushButton;      //下一首
    next_button->setText("下一首");

    QPushButton* play_way_button = new QPushButton;      //播放方式
    play_way_button->setText("播放方式");

    QPushButton* volume_button = new QPushButton;      //音量
    play_way_button->setText("音量");

    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->addWidget(play_way_button);
    h_layout->addWidget(prev_button); 
    h_layout->addWidget(play_button);
    h_layout->addWidget(next_button);
    h_layout->addWidget(volume_button);


    QProgressBar* progress_bar = new QProgressBar;
    QLabel* spend_time_label = new QLabel("经过时间");  //经过的时间
    QLabel* duration_time_label = new QLabel("总时间");    //总时间

    QHBoxLayout* progress_layout = new QHBoxLayout;
    progress_layout->addWidget(spend_time_label);
    progress_layout->addWidget(progress_bar);
    progress_layout->addWidget(duration_time_label);

    mainLayout->addItem(progress_layout);
    mainLayout->addItem(h_layout);
    this->setLayout(mainLayout);
}
