#include "musiclist.h"

MusicList::MusicList(QWidget *parent) : QWidget(parent)
{
    init();      //初始化
}

void MusicList::init()
{
    player = new QMediaPlayer(this);
    music_list = new QVector<Music>;
    initUI();

    //初始化工作
    initConnect();
}

void MusicList::initUI()
{
    setColor(this);
//    this->list_widget = new QListWidget(this);
    this->list_widget = new QTableWidget(this);
    this->list_widget->setColumnCount(3);       //初始化列数
    this->list_widget->setRowCount(0);          //初始化行数
    this->list_widget->verticalHeader()->setVisible(false);         //隐藏行号
    this->list_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);         //行自动拉伸长度
    this->list_widget->setSelectionBehavior(QTableWidget::SelectRows);       //设置一次只能选中一行
    this->list_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);     //保证控件充满整个布局
    this->list_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);         //设置列表内容不可修改


    QStringList name;
    name.append("序号");
    name.append("歌曲名");
    name.append("时长");
    list_widget->setHorizontalHeaderLabels(name);

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
    connect(this->player,&QMediaPlayer::metaDataAvailableChanged,this,[&](bool available){    //用来处理player媒体改变的相应
        if(available){
            this->music.duration = player->duration();
            music_list->replace(music_list->size() - 1,this->music);
            refresh_list();
        }
    });
    connect(this->add_file_button,&QPushButton::clicked,this,&MusicList::addFile);        //添加文件
    connect(this->add_folder_button,&QPushButton::clicked,this,&MusicList::addFolder);        //添加文件夹
    connect(this->list_widget,&QTableWidget::cellDoubleClicked,this,&MusicList::switchMusic);
}


void MusicList::refresh_list()       //flag = 0（添加文件）    1（添加文件夹）
{
    this->list_widget->setRowCount(0);       //清空列表
    print_list(music_list);
    for(auto it = music_list->begin();it != music_list->end();it++){
        this->list_widget->setRowCount(this->list_widget->rowCount() + 1);       //添加新行
        this->list_widget->setItem(this->list_widget->rowCount() - 1,0,new QTableWidgetItem(QString::number(it - music_list->begin())));
        this->list_widget->setItem(this->list_widget->rowCount() - 1,1,new QTableWidgetItem(it->name));
        this->list_widget->setItem(this->list_widget->rowCount() - 1,2,new QTableWidgetItem(getDuration(it->duration)));
    }
}

void MusicList::packMusic(QString file)
{
    QFileInfo info(file);
    music.name = info.baseName();
    music.path = info.filePath();
    music.suffix = info.suffix();        //封装music信息
    music_list->append(music);
    player->setMedia(QUrl::fromLocalFile(file));          //修改媒体
}

QString MusicList::getDuration(qint64 duration)
{
    QTime time(0,0,0,0);
    time = time.addMSecs(duration);
    return time.toString("hh:mm:ss");
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
    for(auto it = this->music_list->begin();it != this->music_list->end();it++){
        if(it->path == file){          //当前歌曲已经存在
            flag = true;
        }
    }
    if(flag == false){       //将music添加到music_list
        packMusic(file);

    }else{
        qDebug() << "歌曲已经存在于列表中";
        QMessageBox::information(this,"提示","该音乐已经存在于列表中");
    }
}

void MusicList::addFolder()
{
    QString path = QFileDialog::getExistingDirectory(this,tr("打开文件夹"),"/",QFileDialog::ShowDirsOnly);
    if(path == nullptr){
        qDebug() << "用户未选择文件夹";
        return;
    }
    //寻找路径下所有音乐文件
   QDir dir(path);
   QStringList filter;
   filter << "*.mp3";         //获取所有mp3格式的文件
   QStringList result = dir.entryList(filter,QDir::Files | QDir::Readable);

   //对音乐文件进行查重
   for(auto it = result.begin();it != result.end();it++){
       QString current_path = path + "/" +  *it;         //获取当前文件夹下音频文件的完整路径
       bool flag = false;
       for(auto i = this->music_list->begin();i != this->music_list->end();i++){
           if(current_path == i->path){        //发现重复
               flag  = true;
               break;
           }
       }
       if(!flag){      //未发现重复歌曲，插入到music_list中
           packMusic(current_path);
       }else{
           //do nothing
       }
   }
}

void MusicList::switchMusic(int row,int column)
{
    //我只要行
    //这里保证list_widget和music_list中的内容严格对应，所以只需要根据行号找到对应的歌曲即可
    Music m = this->music_list->at(row);
    print_music(m);


}
