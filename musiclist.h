#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QWidget>
#include "common.h"
#include <QListWidget>

class MusicList : public QWidget
{
    Q_OBJECT
private:
    QListWidget* list_widget;      //列表
    QPushButton* add_file_button;    //打开文件
    QPushButton* add_folder_button;   //打开文件夹
    QVector<Music> music_list;        //音乐数组
    Music* playing_music;      //正在播放的音乐

    void init();
    void initUI();
    void initConnect();     //初始化connect连接
    void refresh_list(QString path,int flag);     //刷新列表
    Music pack_music(QString path);         //根据路径封装struct Music
public:
    explicit MusicList(QWidget *parent = nullptr);
    Music* temp;          //临时音乐变量
public slots:
    void addFile();
    void addFolder();
    void setDuration(qint64 duration);

signals:
    void music_changed(QString path);
};

#endif // MUSICLIST_H
