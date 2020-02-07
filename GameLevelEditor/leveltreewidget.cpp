#include "leveltreewidget.h"

#include <QDebug>

#include <QKeyEvent>
#include <QMouseEvent>


#include "graphicsblockitem.h"
#include "leveltreeitem.h"

#include "mainwindow.h"

LevelTreeWidget::LevelTreeWidget()
    :scene(NULL)
{
}



void LevelTreeWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"LevelTreeWidget";
}

void LevelTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    qDebug()<<"currentIndex().row():"<<currentIndex().row();

    int curIndex = currentIndex().row();
    if(curIndex!=-1)
    {
//        LevelTreeItem *levelItem = (LevelTreeItem*)MainWindow::sharedInstance()->treeItemsArray[curIndex];
        LevelTreeItem *levelItem = (LevelTreeItem*)currentItem();

        if(levelItem!=NULL)
        {
           qDebug()<<"levelItem:"<<levelItem->getRow();
//            //更新场景中的元素，先清除场景，再将指定LevelItem中的元素加入
           //不能清空对象，clear会释放掉对象，采用数据交换的形式
          // scene->clear();

           doubleClickItem(levelItem);


//            //qDebug()<<"blockItemArraysize:"<<blockItemArray.count();

           // levelItem->debug();
//            for(int i=0;i<levelItem->blockItemArray.count();++i)
//            {
//                GraphicsBlockItem* item = (GraphicsBlockItem*)levelItem->blockItemArray[i];
//               // scene->addItem(item);
//                qDebug()<<item->getIndex();
//                levelItem->debug();
//            }
        }
    }


}

void LevelTreeWidget::mousePressEvent()
{
    qDebug()<<"AAAAA";
}

void LevelTreeWidget::setSceneDelegate(GraphicsBlockScene *_scene)
{
    scene = _scene;
}

void LevelTreeWidget::doubleClickItem(LevelTreeItem *_levelTreeItem)
{
    scene->removeAllItems();

     _levelTreeItem->debug();

   scene->setLevelItem(_levelTreeItem);
}

//void LevelTreeWidget::setTreeItemsArray(QVector<LevelTreeItem *> _treeItemsArray)
//{
//    treeItemsArray = _treeItemsArray;
//}
