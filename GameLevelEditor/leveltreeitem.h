#ifndef LEVELTREEITEM_H
#define LEVELTREEITEM_H

#include <QTreeWidgetItem>

#include <QVector>

#include "graphicsblockitem.h"

class LevelTreeItem : public QTreeWidgetItem
{
public:
    LevelTreeItem();
    LevelTreeItem(QTreeWidget *widget,QString _strName);

public:
    int row;
    int column;

    QString name;

    QVector<GraphicsBlockItem*> blockItemArray;


    //指定颜色种类
    QVector<int> vecSpecialBlockType;


    //胜利条件

    int round;//步数

    int time;//时间

    int score;//游戏积分

    int diamond;//宝石

    int specialBonusCount;//需要生成N次特殊道具数量

    int singleCarrotCount;//消除胡萝卜N个

    int singleCabbageCount;//消除卷心菜N个

    int signleTomatoCount;//消除西红柿N个

    int singleCornCount;//消除玉米N个

    int signleEggplantCount;//消除茄子N个

    bool removeAllIce;//消除所有的冰块

    bool removeAllFloor;//消除所有的地面

    bool removeAllMushRoom;//消除所有的蘑菇

    bool removeAllSpecialType;//消除所有的特殊类型

    bool removeAllCarrot;//消除所有特殊胡萝卜

    bool removeAllCabbage;//消除所有特殊卷心菜

    bool removeAllCorn;//消除所有的玉米

    bool removeAllEggplant;//消除所有的茄子

    bool removeAllTomato;//消除所有的西红柿

    bool removeAllVegetable;//移除所有的蔬菜

    bool removeAllLaydBug;//消除所有的飘虫

    bool removeAllSnowField;//消除所有的雪地

    //星级分数
    int star1Score;
    int star2Score;
    int star3Score;

public:
    const QString &getName();

    void setRow(int _row);
    void setColumn(int _column);

    int getRow() const;
    int getColumn() const;

    void addBlockItem(GraphicsBlockItem* blockItem);

    void debug();

    void release();

    void setLabel(int _index);

    void writeToFile();

    void initLevelCondition();

};

#endif // LEVELTREEITEM_H
