#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QWidget>
#include "common.h"
#include <QTableWidgetItem>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>

class MusicList : public QWidget
{
    Q_OBJECT
private:
    QMediaPlayer* player;
    QTableWidget* list_widget;
    QPushButton* add_file_button;    //打开文件
    QPushButton* add_folder_button;   //打开文件夹
    QVector<Music>* music_list;     //音乐列表
    Music music;



    /* 功能函数 */
    void init();
    void initUI();       //初始化UI界面
    void initConnect();     //初始化connect连接
    void refresh_list();     //刷新列表
    void packMusic(QString path);      //封装歌曲信息，包含了插入到music_list和刷新列表功能

    QString getDuration(qint64 duration);   //毫秒转化为分钟格式
public:
    explicit MusicList(QWidget *parent = nullptr);
public slots:
    void addFile();
    void addFolder();
    void switchMusic(int row,int columu);    //用户双击列表切换时间

signals:
    void meta_changed(QString path);
    void music_changed(QString path);    //用户双击列表切换时间
};

#endif // MUSICLIST_H
