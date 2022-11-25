#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
    //main中添加了一行注释
}
