#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QTableWidget>

class CustomTableWidget : public QTableWidget
{
    Q_OBJECT
private:
    QMenu* pop_menu;
public:
    CustomTableWidget();
    void contextMenuEvent(QContextMenuEvent* event);
};

#endif // CUSTOMTABLEWIDGET_H
