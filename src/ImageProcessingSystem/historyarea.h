#ifndef HISTORYAREA_H
#define HISTORYAREA_H

#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>

class HistoryArea : public QScrollArea
{
public:
    HistoryArea(QWidget* parent = NULL);
    void wheelEvent(QWheelEvent* event);
private:
    QScrollBar *scrollBarx;
};

#endif // HISTORYAREA_H
