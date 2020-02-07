#ifndef GRAPHICSBLOCKITEM_H
#define GRAPHICSBLOCKITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>


//对于含有玻璃的地面，要加上MASK_VALUE值，判断时，如果ABS大于
//或等于128，则要减去128，得到最终的VALUE值
const static int MASK_VALUE = 128;

class GraphicsBlockItem :public QGraphicsItem
{

public:
     GraphicsBlockItem();

     QRectF  boundingRect() const;

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

     void keyPressEvent(QKeyEvent *event);
     void keyReleaseEvent(QKeyEvent *event);


public:
     //test index
     int index;

     //地表类型
     int groundType;

     //地面层数
     int groundLayer;

     //显示玻璃开关
     bool isShowGlassFlag;


     //方块类型
     int blockType;

     //翻转状态
     int flipState;


     //锁住标识
     bool lockInFlag;

     //地表对象
     QPixmap imgGround;
     //地表上层玻璃对象
     QPixmap imgGlass;

     //地表上的方块对象
     QPixmap imgBlock;

     //锁标志
     QPixmap imgLockIn;


     QPointF pos;

public:
     void setIndex(int _index);

     int getIndex();

     void debug();

     void setGroundFrame(int _frameID);

     void initDefaultPosition(qreal x, qreal y);

     void setGroundType(int _type);

     int getGroundType();

     void updateBlockItem();

     void showGlass(int _layer);

     void hideGlass();

     bool isShowGlass();

     int getBlockType();

     void setBlockType(int _type);

     void setBlockItem(int _type);

     //获取导出后的地面类型数值，会带上地表上玻璃的标识
     int getExportGroundType();

     //获取地面层数
     int getGroundLayer();

     void setGroundLayer(int _layer);

     void setLockInFlag(bool _lock);

     bool isLockIn();

     int width();

     int height();


};

#endif // GRAPHICSBLOCKITEM_H
