#include "musiclist.h"

void MusicList::init()
{
    initUI();

    //初始化工作
    initConnect();

}

void MusicList::initUI()
{
    setColor(this);
    this->list_widget = new QListWidget(this);

    //按钮栏
    add_file_button = new QPushButton(this);
    add_file_button->setText("打开文件");

    add_folder_button = new QPushButton(this);
    add_folder_button->setText("打开文件夹");

    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->addWidget(add_file_button);
    h_layout->addWidget(add_folder_button);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(h_layout,0,0);
    mainLayout->addWidget(list_widget,1,0);

    this->setLayout(mainLayout);
}

void MusicList::initConnect()
{
    connect(this->add_file_button,&QPushButton::clicked,this,&MusicList::addFile);        //添加文件
    connect(this->add_folder_button,&QPushButton::clicked,this,&MusicList::addFolder);        //添加文件夹
}


void MusicList::refresh_list(QString path,int flag = 0)       //flag = 0（添加文件）    1（添加文件夹）
{
//    QFileInfo file_info(path);
//    qDebug() << "-----------------";
//    qDebug() << file_info.baseName();
//    qDebug() << file_info.fileName();
//    qDebug() << file_info.filePath();
//    qDebug() << "-----------------";
    if(flag == 0){       //添加文件

    }else if(flag == 1){        //添加文件夹

    }
}

Music MusicList::pack_music(QString path)
{
    Music music;
    QFileInfo file_info(path);
    music.path = path;
    music.name = file_info.baseName();
    music.suffix = file_info.suffix();
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(path));
//    connect(player,&QMediaPlayer::durationChanged,this,&MusicList::setDuration);
    connect(player,&QMediaPlayer::durationChanged,this,[&](qint64 duration){
        this->temp = new Music;
        this->temp->duration = duration;
        print_music(*this->temp);
    });
//    print_music(music);
    return music;
}

MusicList::MusicList(QWidget *parent) : QWidget(parent)
{
    init();      //初始化
}

void MusicList::addFile()
{
    QString file = QFileDialog::getOpenFileName(this,tr("打开音乐"),"/",tr("音频文件(*.mp3 *.wav)"));
    if(file == nullptr){
        qDebug() << "用户未选择文件";
        return;
    }
    //检测是否重复
    bool flag = false;
    for(auto it = music_list.begin();it != music_list.end();it++){
        if(it->path == file){
            qDebug() << "该音乐已经存在";
            flag = true;
        }
    }
    if(flag == false){
        qDebug() << "fllllllllllllllll" << file;
        pack_music(file);
    }

    emit music_changed(file);

}

void MusicList::addFolder()
{
    QString file = QFileDialog::getExistingDirectory(this,tr("打开文件夹"),"/",QFileDialog::ShowDirsOnly);
    if(file == nullptr){
        qDebug() << "用户未选择文件夹";
        return;
    }
    //刷新列表
    emit music_changed(file);
}

void MusicList::setDuration(qint64 duration)
{

}
