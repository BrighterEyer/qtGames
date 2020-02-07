#include "graphicsblockscene.h"
#include <QDebug>

#include <QGraphicsSceneMouseEvent>


GraphicsBlockScene::GraphicsBlockScene()
    :isMouseLeftButtonPressed(false),
      levelItem(NULL)
{

}

int index = 1;
void GraphicsBlockScene::updateBlockItem()
{
    int count = levelItem->blockItemArray.count();

    for(int i=0;i<count;++i)
    {
        GraphicsBlockItem* blockItem = (GraphicsBlockItem*)levelItem->blockItemArray[i];

        if(blockItem->isUnderMouse())
        {

            blockItem->updateBlockItem();
            break;
        }

    }
}

void GraphicsBlockScene::setLevelItem(LevelTreeItem *_levelItem)
{
    levelItem = _levelItem;
    qDebug()<<"AAA";
    levelItem->debug();

    for(int i=0;i<levelItem->blockItemArray.count();++i)
    {
        GraphicsBlockItem *item = (GraphicsBlockItem*)levelItem->blockItemArray[i];
        //addItem(item);
        //addItem(it);
        //item->update();
        //qDebug()<<"HH";
        item->setVisible(true);
        addItem(item);
        //qDebug()<<"B:"<<item->getIndex();

    }

}

void GraphicsBlockScene::removeAllItems()
{
    if(levelItem!=NULL)
    {
        for(int i=0;i<levelItem->blockItemArray.count();++i)
        {
            GraphicsBlockItem* item = (GraphicsBlockItem*)levelItem->blockItemArray[i];
            removeItem(item);
        }
    }

   // levelItem = NULL;

}

void GraphicsBlockScene::debug()
{
    levelItem->debug();
}

void GraphicsBlockScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!isMouseLeftButtonPressed)
    {
        return;
    }
    index++;

    if(levelItem!=NULL)
    {
        updateBlockItem();
    }

}

void GraphicsBlockScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button()==Qt::LeftButton)
    {
        isMouseLeftButtonPressed = true;
        if(levelItem!=NULL)
        {
            updateBlockItem();
        }

    }
}

void GraphicsBlockScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isMouseLeftButtonPressed = false;
}

//void GraphicsBlockScene::setBlockItemArray(QVector<GraphicsBlockItem *> _blockItemArray)
//{
//     blockItemArray = _blockItemArray;
//     qDebug()<<"111111:"<<blockItemArray.count();

//     //update
//     for(int i=0;i<blockItemArray.count();++i)
//     {
//         GraphicsBlockItem* blockItem = (GraphicsBlockItem*)blockItemArray[i];
//         //blockItem->update();
//         qDebug()<<blockItem->getIndex();
//     }
//}
