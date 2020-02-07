#ifndef LEVELTREEWIDGET_H
#define LEVELTREEWIDGET_H

#include <QTreeWidget>

#include "graphicsblockscene.h"

#include "leveltreeitem.h"

class LevelTreeWidget :public QTreeWidget
{
public:
    LevelTreeWidget();

    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void mousePressEvent();

public:
    GraphicsBlockScene* scene;

   // QVector<LevelTreeItem*> treeItemsArray;

public:
    void setSceneDelegate(GraphicsBlockScene* _scene);

    //双击显示当前关卡
    void doubleClickItem(LevelTreeItem* _levelTreeItem);
    //void setTreeItemsArray(QVector<LevelTreeItem*> _treeItemsArray);
};

#endif // LEVELTREEWIDGET_H
