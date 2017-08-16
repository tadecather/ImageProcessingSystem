#include "historyarea.h"

HistoryArea::HistoryArea(QWidget *parent) : QScrollArea(parent)
{
    scrollBarx = horizontalScrollBar();
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void HistoryArea::wheelEvent(QWheelEvent* event)
{
    if(event->delta() > 0)
    {
        scrollBarx->setValue(scrollBarx->value()-18);
    }
    else
    {
        scrollBarx->setValue(scrollBarx->value()+18);
    }
}
