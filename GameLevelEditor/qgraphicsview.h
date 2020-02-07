#ifndef QGRAPHICSVIEW_H
#define QGRAPHICSVIEW_H

#include <QGraphicsView>

class QGraphicsView :public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsView();

public:
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // QGRAPHICSVIEW_H
