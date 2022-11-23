#ifndef COMMON_H
#define COMMON_H

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QUrl>
#include <QStringList>
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
    long duration;     //音乐时长
};
void setColor(QWidget* widget);
void print_music(Music music);


#endif // COMMON_H
