#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QWidget>
#include "common.h"

class musicInfo : public QWidget
{
    Q_OBJECT
private:
    void init();
    void initUI();
public:
    explicit musicInfo(QWidget *parent = nullptr);

signals:

};

#endif // MUSICINFO_H
