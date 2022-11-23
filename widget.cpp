#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

void Widget::init()
{
    initUI();      //初始化界面
    initConnect();   //初始化connect

    //初始化工作
    player = new QMediaPlayer;

}

void Widget::initUI()         //初始化界面功能
{
    //设置初始大小
    this->resize(1100,650);

    //设置整体布局
    QGridLayout* mainLayout = new QGridLayout;
    this->setLayout(mainLayout);

    //歌曲详情
    music_info_widget = new musicInfo;
    music_info_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);     //保证控件充满整个布局
    mainLayout->addWidget(music_info_widget,0,0);

    //播放列表
    music_list_widget = new MusicList;
    music_list_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->addWidget(music_list_widget,0,1);
    //底部控制栏
    controller = new Controller;
    controller->setMinimumHeight(80);
    controller->setMaximumHeight(80);
    mainLayout->addWidget(controller,1,0,1,2,Qt::AlignBottom);   //放置于底部
}

void Widget::initConnect()
{
    connect(this->music_list_widget,&MusicList::music_changed,this,&Widget::music_changed);
}

Widget::~Widget()
{
}

void Widget::music_changed(QString path)
{
    qDebug() << "音乐切换" << path;
    this->player->setMedia(QUrl::fromLocalFile(path));
    this->player->play();
}

