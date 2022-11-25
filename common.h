#ifndef COMMON_H
#define COMMON_H
/*解决转移到vs中乱码问题*/
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/adler32.h>
#include <libavfilter/avfilter.h>
}

#include <QPushButton>
#include <QGridLayout>
#include <QMediaContent>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir> 
#include <QUrl>
#include <QThread>
#include <QTime>
#include <QStringList>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPalette>
#include <QVector>
#include <QList>
#include <QMediaPlayer>

struct Music{
    QString path;    //音乐路径
    QString name;  //音乐名称
    QString suffix;     //音乐类型后缀
    qint64 duration = 0;     //音乐时长
};
void setColor(QWidget* widget);
void print_music(Music music);
void print_list(QVector<Music>* list);


#endif // COMMON_H
