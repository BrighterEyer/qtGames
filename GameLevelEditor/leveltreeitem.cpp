#include "leveltreeitem.h"
#include "QDebug"

#include "graphicsblockitem.h"

#include <QFile>

#include "LevelGlobal.h"

LevelTreeItem::LevelTreeItem()
{
    initLevelCondition();
}

LevelTreeItem::LevelTreeItem(QTreeWidget *widget,QString _strName)
    :name(_strName)
    ,round(0)
    ,time(0)
    ,score(0)
    ,diamond(0)
    ,specialBonusCount(0)
    ,singleCarrotCount(0)
    ,singleCabbageCount(0)
    ,signleTomatoCount(0)
    ,singleCornCount(0)
    ,signleEggplantCount(0)
    ,removeAllIce(false)
    ,removeAllFloor(false)
    ,removeAllMushRoom(false)
    ,removeAllSpecialType(false)
    ,removeAllCarrot(false)
    ,removeAllCabbage(false)
    ,removeAllCorn(false)
    ,removeAllEggplant(false)
    ,removeAllTomato(false)
    ,removeAllVegetable(false)
    ,removeAllLaydBug(false)
    ,removeAllSnowField(false)
    ,star1Score(0)
    ,star2Score(0)
    ,star3Score(0)
{

    qDebug()<<"name:"<<name;
    setText(0,name);
    widget->addTopLevelItem(this);

    //qdebug()<<"child:"<<widget->children().size();
}

const QString &LevelTreeItem::getName()
{
    return name;
}

void LevelTreeItem::setRow(int _row)
{
    row = _row;
}

void LevelTreeItem::setColumn(int _column)
{
    column = _column;
}

int LevelTreeItem::getRow() const
{
    return row;
}

int LevelTreeItem::getColumn() const
{
    return column;
}

void LevelTreeItem::addBlockItem(GraphicsBlockItem *blockItem)
{

    blockItemArray.push_back(blockItem);
}



void LevelTreeItem::debug()
{
    qDebug()<<"blockItemArray size:"<<blockItemArray.count();
    for(int i=0;i<blockItemArray.count();++i)
    {
        GraphicsBlockItem* item = (GraphicsBlockItem*)blockItemArray[i];
        qDebug()<<"blockItemType:"<<item->getBlockType();
    }


    qDebug()<<"round:"<<round;
    qDebug()<<"time:"<<time;
    qDebug()<<"score:"<<score;
    qDebug()<<"diamond:"<<diamond;
    qDebug()<<"specialBonusCount:"<<specialBonusCount;
    qDebug()<<"singleCarrotCount:"<<singleCarrotCount;
    qDebug()<<"signleTomatoCount:"<<signleTomatoCount;
    qDebug()<<"singleCabbageCount:"<<singleCabbageCount;

    qDebug()<<"singleCornCount:"<<singleCornCount;
    qDebug()<<"signleEggplantCount:"<<signleEggplantCount;
    qDebug()<<"removeAllIce:"<<removeAllIce;
    qDebug()<<"removeAllFloor:"<<removeAllFloor;
    qDebug()<<"removeAllMushRoom:"<<removeAllMushRoom;
    qDebug()<<"removeAllSpecialType:"<<removeAllSpecialType;
    qDebug()<<"removeAllCarrot:"<<removeAllCarrot;
    qDebug()<<"removeAllCabbage:"<<removeAllCabbage;
    qDebug()<<"removeAllCorn:"<<removeAllCorn;
    qDebug()<<"removeAllTomato:"<<removeAllTomato;

    qDebug()<<"removeAllEggplant:"<<removeAllEggplant;
    qDebug()<<"removeAllVegetable:"<<removeAllVegetable;

    qDebug()<<"removeAllLadyBug:"<<removeAllLaydBug;
    qDebug()<<"removeAllSnowField:"<<removeAllSnowField;

    qDebug()<<"star1score:"<<star1Score;
    qDebug()<<"star2score:"<<star2Score;
    qDebug()<<"star3score:"<<star3Score;

}


void LevelTreeItem::setLabel(int _index)
{
    name = "Level_"+QString::number(_index);
    setText(0,name);
}



void LevelTreeItem::writeToFile()
{

    QFile file(getName()+STR_LEVEL_SUFFIX);

    qDebug()<<"file name:"<<file.fileName();

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"couldn't write files";
        return;
    }

    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_4_7);

    //out<<quint32(FILE_CHECK_HEADER_CODE);

    //write row &column

    int Num = 10;

    out<<"A";

    file.flush();
    file.close();

    qDebug()<<"write file success!!!";




}


void LevelTreeItem::initLevelCondition()
{
          round = 0;
          time = 0;
          score= 0;
          diamond = 0;
          specialBonusCount= 0;
          singleCarrotCount= 0;
          singleCabbageCount= 0;
          signleTomatoCount= 0;
          singleCornCount= 0;
          signleEggplantCount = 0;
          removeAllMushRoom = false;
          removeAllIce = false;
          removeAllFloor = false;
          removeAllSpecialType = false;
          removeAllCarrot = false;
          removeAllCabbage = false;
          removeAllCorn = false;
          removeAllEggplant = false;
          removeAllTomato = false;
          removeAllVegetable = false;
          removeAllLaydBug = false;
          removeAllSnowField = false;

          star1Score = 0;
          star2Score = 0;
          star3Score = 0;


}
