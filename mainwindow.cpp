#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    //初始化变量
    player = new QMediaPlayer;

    //配置信号和槽
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(time_process(qint64)));       //绑定进度改变事件，用来调整音乐进度
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(duration(qint64)));   //用于获取总时长
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::button1_clicked);   //播放/暂停事件
    connect(ui->stop_button,&QPushButton::clicked,this,&MainWindow::stop_play);    //停止播放
    connect(ui->slider,SIGNAL(sliderMoved(int)),this,SLOT(slider_move(int)));       //滑动条滑动
    connect(ui->volume_adjust_slider,SIGNAL(sliderMoved(int)),this,SLOT(volume_adjust(int)));    //音量调节
    connect(ui->open_folder_button,SIGNAL(clicked()),this,SLOT(open_folder()));
    connect(ui->music_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(select_changed(QListWidgetItem*)));    //音乐选中事件
    connect(this->player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playing_state_changed(QMediaPlayer::State)));

    //读取历史
    QStringList history = read_history();

    //设置播放列表
    QString path;
    if(history.size() > 0) path = history.at(0);
    if(path != nullptr && path != ""){
        refresh_music_list(path);
        this->base_path = path;
    }
    //设置变量参数
    ui->volume_adjust_slider->setMinimum(0);   //最小音量
    ui->volume_adjust_slider->setMaximum(100);   //最大音量
    ui->volume_adjust_slider->setValue(volume);
    player->setVolume(this->volume);

    //进度条初始化
    ui->slider->setMinimum(0);

    //播放方式初始化
    ui->play_mode_select->addItem("列表循环");
    ui->play_mode_select->addItem("单曲循环");
    ui->play_mode_select->addItem("随机播放");

}

void MainWindow::create_history()
{
    QFile file("./history.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        qDebug() << "创建记录失败";
        return ;
    }
    //写入上一次路径
    QByteArray enter = "\r\n";
    QByteArray str1 = this->base_path.toLatin1();   //路径
    file.write(str1 + enter);

    file.close();

}

QStringList MainWindow::read_history()
{
    QStringList history;
    QFile file("./history.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "读取记录失败";
        return history;
    }
    while(!file.atEnd()){
        QString his(file.readLine());
        his = his.trimmed();
        history << his;
    }
    return history;
}

void MainWindow::refresh_music_list(QString path)
{
    //刷新播放列表功能
    QDir dir(path);
    QStringList filter;
    filter << "*.mp3";
    QStringList results;
    results = dir.entryList(filter,QDir::Files | QDir::Readable,QDir::Name);
    ui->music_list->clear();
    ui->music_list->addItems(results);
}

void MainWindow::time_process(qint64 position)
{
    ui->slider->setValue(position);

    qint64 duration = ui->slider->maximum();  //获取总时间

    QString all = QTime(0,0,0,0).addMSecs(duration).toString(QString::fromLatin1("mm : ss"));
    QString current = QTime(0,0,0,0).addMSecs(position).toString(QString::fromLatin1("mm : ss"));

    QString str = current + " / " + all;
    ui->label->setText(str);

}

void MainWindow::duration(qint64 duration)
{
        qDebug() << "总的时间为：" << duration;
        ui->slider->setMaximum(duration);
}

void MainWindow::slider_move(int current)
{
    //当滑块移动时触发的事件
    player->setPosition(current);
}

void MainWindow::open_folder()
{
    //打开文件夹
    QString path = QFileDialog::getExistingDirectory(this,"选择文件夹","C:/",QFileDialog::ShowDirsOnly);    //打开文件夹窗口
    this->base_path = path;
    qDebug() << path;    //控制台输出路径
    refresh_music_list(path);   //刷新列表
}

void MainWindow::select_changed(QListWidgetItem* item)
{
    //获取选中项
    QString file_name = item->text();
    QString full_path = this->base_path + "/" + file_name;    //获取文件的完整路径名
    if(this->playing_music_path != full_path){
        //如果当前不是正在播放这个音乐，则切换音乐
        player->setMedia(QUrl::fromLocalFile(full_path));
        player->play();
        this->playing_music_path = full_path;
    }else{
        //播放重复，默认先不操作
    }
}

void MainWindow::playing_state_changed(QMediaPlayer::State state)
{
    //当播放状态改变时需要进行的操作
    if(state == QMediaPlayer::PlayingState){
        ui->pushButton->setText("暂停");
    }else if(state == QMediaPlayer::PausedState){
        ui->pushButton->setText("播放");
    }else{
        ui->pushButton->setText("播放");
    }
}

void MainWindow::volume_adjust(int volume)
{
    //音量调节模块
    this->volume = volume;
    player->setVolume(volume);
}

MainWindow::~MainWindow()
{
    create_history();
    delete ui;
}



void MainWindow::button1_clicked()
{
    if(player->state() == QMediaPlayer::PlayingState){   //判断播放状态
        this->player->pause();
    }else if(player->state() == QMediaPlayer::PausedState){
        this->player->play();
    }else{
        if(this->playing_music_path == ""){
            //如果当前没有指定播放的歌曲
        }else{
            this->player->play();

        }

    }
}

void MainWindow::stop_play()
{
    player->stop();
}


