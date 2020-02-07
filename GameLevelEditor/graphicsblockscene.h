#ifndef GRAPHICSBLOCKSCENE_H
#define GRAPHICSBLOCKSCENE_H

#include <QGraphicsScene>

#include <QVector>

#include "graphicsblockitem.h"

#include "LevelTreeItem.h"

class GraphicsBlockScene:public QGraphicsScene
{

public:
    explicit GraphicsBlockScene();

signals:

public slots:

public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:

    //QVector<GraphicsBlockItem*> blockItemArray;

    LevelTreeItem* levelItem;

    bool isMouseLeftButtonPressed;



public:
   // void setBlockItemArray(QVector<GraphicsBlockItem*> _blockItemArray);
    void updateBlockItem();

    void setLevelItem(LevelTreeItem* _levelItem);

    void removeAllItems();

    void debug();
};

#endif // GRAPHICSBLOCKSCENE_H
