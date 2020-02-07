#include "qgraphicsview.h"

#include <QDebug>

QGraphicsView::QGraphicsView()
{
    setMouseTracking(true);
}

void QGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"AAA";
}
