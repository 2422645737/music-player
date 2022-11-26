#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget()
{
    this->pop_menu = new QMenu(this);
}

void CustomTableWidget::contextMenuEvent(QContextMenuEvent* event)
{
    this->pop_menu->clear();

    if(this->itemAt(event->pos()) != NULL){
        QAction* action_play = new QAction(this);     //播放
        QAction* action_delete = new QAction(this);    //删除
        QAction* action_up = new QAction(this);       //上移
        QAction* action_down = new QAction(this);     //下移
        QAction* action_prop = new QAction(this);     //属性

        action_play->setText("播放");
        action_delete->setText("从列表中删除");
        action_up->setText("上移");
        action_down->setText("下移");
        action_prop->setText("属性");
        this->pop_menu->addAction(action_play);
        this->pop_menu->addAction(action_delete);
        this->pop_menu->addSeparator();
        this->pop_menu->addAction(action_up);
        this->pop_menu->addAction(action_down);
        this->pop_menu->addSeparator();
        this->pop_menu->addAction(action_prop);

        this->pop_menu->exec(QCursor::pos());
        event->accept();
    }
}
