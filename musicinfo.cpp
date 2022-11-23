#include "musicinfo.h"

void musicInfo::init()
{
    initUI();
}

void musicInfo::initUI()
{
    setColor(this);
}

musicInfo::musicInfo(QWidget *parent) : QWidget(parent)
{
    init();
}
