#ifndef MYBOX_H
#define MYBOX_H

#include <QGraphicsObject>
#include <QGraphicsItemGroup>

//添加OneBox的定义
class OneBox:public QGraphicsObject
{
public:
    OneBox(const QColor &color=Qt::red);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
private:
    QColor brushColor;
};

//添加BoxGroup的定义
class BoxGroup:public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    //使用枚举类型定义8个方形形状
    enum BoxShape{
        IShape,
        JShape,
        LShape,
        OShape,
        SShape,
        TShape,
        ZShape,
        RandomShape //随机性状，若指定了该形状，就在前面7个形状中随机取一个
    };
    BoxGroup();
    QRectF boundingRect() const;
    bool isColliding();
    void createBox(const QPointF &point=QPointF(0,0),BoxShape shape=RandomShape);
    void clearBoxGroup(bool destoryBox=false);
    BoxShape getCurrentShape()
    {
        return currentShape;
    }
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void needNewBox();
    void gameFinished();
public slots:
    void moveOneStep();
    void startTimer(int interval);
    void stopTimer();
private:
    BoxShape currentShape;
    QTransform oldTransform;
    QTimer *timer;
};

#endif // MYBOX_H
