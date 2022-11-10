#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QFile>
#include <QListWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    enum PLAY_MODE{
            LIST_CIRCULATION = 1,
            SINGAL_CIRCULATION = 2,
            RANDOM_PLAYING = 3
    };

    //初始化
    void init();

    void create_history();      //记录上一次播放的路径，音乐名称，进度
    QStringList read_history();       //读取历史
    void refresh_music_list(QString path);

    ~MainWindow();

private slots:
    void button1_clicked();
    void stop_play();
    void time_process(qint64 position);
    void duration(qint64 duration);
    void slider_move(int current);
    void open_folder();
    void select_changed(QListWidgetItem* item);     //用户选择列表中的音乐
    void playing_state_changed(QMediaPlayer::State state);
    void volume_adjust(int volume);


private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;

    //维护一些状态
    QString base_path;    //打开文件的基目录
    QString playing_music_path;    //当前正在播放音乐的路径
    int volume = 50;    //当前音量
    PLAY_MODE play_mode = PLAY_MODE::LIST_CIRCULATION;
};
#endif // MAINWINDOW_H
