#include "graphicsblockitem.h"

#include "mainwindow.h"

#include "LevelGlobal.h"

#include "grounddialog.h"

#include <QKeyEvent>

const static int RECT_WIDTH = 85;
const static int RECT_HEIGHT = 85;

const static QString STR_GROUND_1 = ":Icon/res/floor_1.png";
const static QString STR_GROUND_2 = ":Icon/res/floor_2.png";
const static QString STR_GROUND_3 = ":Icon/res/floor_3.png";
const static QString STR_GROUND_4 = ":Icon/res/floor_4.png";
const static QString STR_GROUND_5 = ":Icon/res/floor_5.png";
const static QString STR_GROUND_6 = ":Icon/res/floor_6.png";
const static QString STR_GROUND_7 = ":Icon/res/floor_7.png";
const static QString STR_GROUND_8 = ":Icon/res/floor_8.png";

const static QString STR_EMPTY = ":Icon/res/empty.png";

const static QString STR_GLASS = ":Icon/res/earth.png";
const static QString STR_GLASS2 = ":Icon/res/earth2.png";

const static QString STR_TOMATO = ":Icon/res/gem0.png";
const static QString STR_CARROT = ":Icon/res/gem2.png";
const static QString STR_CABBAGE = ":Icon/res/gem4.png";
const static QString STR_CORN = ":Icon/res/gem6.png";
const static QString STR_EGGPLANT = ":Icon/res/gem8.png";
const static QString STR_ONION = ":Icon/res/onion_cartoon.png";
const static QString STR_BARRIER = ":Icon/res/barrier0.png";
const static QString STR_LIMIT = ":Icon/res/limit.png";
const static QString STR_BARRIER_HIDE = ":Icon/res/barrier1.png";
const static QString STR_BARRIER_MUSHROOM = ":Icon/res/mushroom.png";
const static QString STR_BARRIER_CLONE = ":Icon/res/clone.png";
const static QString STR_REMOVE = ":Icon/res/empty1.png";

//const static QString STR_BARRIER_CLONE = ":Icon/res/clone.png";

const static QString STR_LOCKIN = ":Icon/res/lock.png";

const static QString STR_DIAMOND = ":Icon/res/diamond.png";

const static QString STR_BARRIER_MUSHROOMx2 = ":Icon/res/mushroomx2.png";


const static QString STR_CARROT_LARGE = ":Icon/res/carrot_large.png";
const static QString STR_CORN_LARGE = ":Icon/res/corn_large.png";
const static QString STR_CABBAGE_LARGE = ":Icon/res/cabbage_large.png";
const static QString STR_TOMATO_LARGE = ":Icon/res/tomato_large.png";
const static QString STR_EGGPLANT_LARGE = ":Icon/res/eggplant_large.png";

const static QString STR_BARRIER_SPECIAL = ":Icon/res/specialBarrier.png";

const static QString STR_MUSHROOM_MOVEABLE = ":Icon/res/mushroom3.png";

GraphicsBlockItem::GraphicsBlockItem()
    :index(-1)
    ,flipState(-1)
    ,groundType(NULL_VALUE)
    ,groundLayer(-1)
    ,isShowGlassFlag(false)
    ,blockType(NULL_VALUE)
    ,lockInFlag(false)

{
    setFlag(ItemIsMovable);
    //setFlag(ItemIsMovable,true);

   // imgGround = QPixmap(STR_GROUND_1);

    setGroundFrame(1);

    imgGlass = QPixmap(STR_EMPTY);

    imgBlock = QPixmap(STR_EMPTY);

    imgLockIn = QPixmap(STR_EMPTY);
}


QRectF GraphicsBlockItem::boundingRect() const
{
    return QRectF(0,0,RECT_WIDTH*MainWindow::getScaleRadio(),RECT_HEIGHT*MainWindow::getScaleRadio());
}

void GraphicsBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rectF = boundingRect();

    QBrush brush(Qt::green);

    //painter->fillRect(rectF,brush);


    float width = imgGround.width();
    float height = imgGround.height();


    painter->scale(MainWindow::getScaleRadio(),MainWindow::getScaleRadio());
   // painter->translate(width*MainWindow::getScaleRadio()/2,height*MainWindow::getScaleRadio()/2);
    switch(flipState)
    {
    case 0://normal
        painter->drawPixmap(0,0,width,height,imgGround);

        break;
    case 1://H
        painter->save();
        painter->translate(width/2,height/2); //让图片的中心作为旋转的中心
           painter->rotate(180); //顺时针旋转90度

           painter->translate(-width/2,-height/2); //使原点复原

           painter->drawPixmap(0,0,width,height,imgGround);
        painter->restore();
        break;
    case 2://V
        painter->save();
        painter->translate(width/2,height/2); //让图片的中心作为旋转的中心
           painter->rotate(180); //顺时针旋转90度

           painter->translate(-width/2,-height/2); //使原点复原

           painter->drawPixmap(0,0,width,height,imgGround);
        painter->restore();
        break;
    case 3://90度
        painter->save();
        painter->translate(width/2,height/2); //让图片的中心作为旋转的中心
           painter->rotate(90); //顺时针旋转90度

           painter->translate(-width/2,-height/2); //使原点复原

           painter->drawPixmap(0,0,width,height,imgGround);
        painter->restore();

           break;
    case 4:
        painter->save();
        painter->translate(width/2,height/2); //让图片的中心作为旋转的中心
           painter->rotate(270); //顺时针旋转90度

           painter->translate(-width/2,-height/2); //使原点复原

           painter->drawPixmap(0,0,width,height,imgGround);

           //qDebug()<<"####";
         painter->restore();
        break;

    }

    //绘制地面上层玻璃
    painter->drawPixmap(0,0,width,height,imgGlass);
    //qDebug()<<"Update!";
    //绘制地面方块类型

    painter->drawPixmap(0,0,width,height,imgBlock);


    //绘制LockIn
    painter->drawPixmap(0,0,width,height,imgLockIn);


}

void GraphicsBlockItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // qDebug()<<"mousePressEvent";
    qDebug()<<"mousePrssed:index:"<<getIndex();

    updateBlockItem();

    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   // qDebug()<<"mouseReleaseEvent";
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphicsBlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //setPos(0,0);
    qDebug()<<"mouseMoveEvent:"<<getIndex();
    //updateBlockItem();
    update();
    //  QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsBlockItem::keyPressEvent(QKeyEvent *event)
{

    qDebug()<<"CTRL";
}

void GraphicsBlockItem::keyReleaseEvent(QKeyEvent *event)
{
     //isPressCtrl = false;
}

void GraphicsBlockItem::setIndex(int _index)
{
    index = _index;
}

int GraphicsBlockItem::getIndex()
{
    return index;
}

void GraphicsBlockItem::debug()
{
    //qDebug()<<"index:"<<getIndex();

    //qDebug()<<"groundType:"<<getExportGroundType();

    qDebug()<<"blockType:"<<blockType;
}

void GraphicsBlockItem::setGroundFrame(int _frameID)
{
    QString strImgFrameName[9] = {
        "NULL",
        STR_GROUND_1,
        STR_GROUND_2,
        STR_GROUND_3,
        STR_GROUND_4,
        STR_GROUND_5,
        STR_GROUND_6,
        STR_GROUND_7,
        STR_GROUND_8,

    };


    setGroundType(_frameID);
    //int flipState = 0;

    if(_frameID==-5)
    {
        qDebug()<<"5555";
        flipState = 4;
    }else
    if(_frameID==-1)
    {
        //90度
        flipState = 3;
    }else
    if(_frameID==-2||_frameID==-6)
        {
            //左右翻转
            flipState = 1;
        }else
        if(_frameID==-7||_frameID==-3)
        {
            //上下翻转
            flipState = 2;
        }
        else
        {
            flipState = 0;
        }
        _frameID = abs(_frameID);

        //qDebug()<<"frameID:"<<_frameID<<"flipState:"<<flipState;


    imgGround= QPixmap(strImgFrameName[_frameID]);

}

void GraphicsBlockItem::initDefaultPosition(qreal x, qreal y)
{
    pos = QPointF(x,y);
}

void GraphicsBlockItem::setGroundType(int _type)
{
    groundType = _type;
}

int GraphicsBlockItem::getGroundType()
{
    return groundType;
}

void GraphicsBlockItem::updateBlockItem()
{


    switch(MainWindow::toolButtonTypes)
    {
        case TOOL_GROUND:
        qDebug()<<"getGroundType:"<<GroundDialog::getGroundType();

        setGroundFrame(GroundDialog::getGroundType());
        break;
    case TOOL_GLASS:
        qDebug()<<MainWindow::isPressCtrl;

        if(blockType!=TOOL_EMPTY)
        {
            if(MainWindow::isPressCtrl)
            {
                hideGlass();
            }else
            {
                showGlass(GROUND_LAYER_1);
            }
        }

        break;
    case TOOL_GLASS2:
        qDebug()<<MainWindow::isPressCtrl;

        if(blockType!=TOOL_EMPTY)
        {
            if(MainWindow::isPressCtrl)
            {
                hideGlass();
            }else
            {
                showGlass(GROUND_LAYER_2);
            }
        }

        break;
    case TOOL_TOMATO:

        setBlockItem(TOOL_TOMATO);


        break;
    case TOOL_CARROT:
        setBlockItem(TOOL_CARROT);


        break;
    case TOOL_CABBAGE:
        setBlockItem(TOOL_CABBAGE);

        break;
    case TOOL_CORN:
        setBlockItem(TOOL_CORN);

        break;
    case TOOL_EGGPLANT:
        setBlockItem(TOOL_EGGPLANT);

        break;
    case TOOL_REMOVE:
        setBlockItem(TOOL_REMOVE);

        break;

    case TOOL_ONION:
        setBlockItem(TOOL_ONION);

        break;
    case TOOL_BARRIER_HIDE:
        setBlockItem(TOOL_BARRIER_HIDE);
        setLockInFlag(false);
        break;
    case TOOL_BARRIER_MUSHROOM:
        setBlockItem(TOOL_BARRIER_MUSHROOM);
        setLockInFlag(false);
        break;
    case TOOL_BARRIER_CLONE:
        setBlockItem(TOOL_BARRIER_CLONE);
         setLockInFlag(false);
        break;

    case TOOL_BARRIER:
        setBlockItem(TOOL_BARRIER);
        setLockInFlag(false);
        break;
    case TOOL_EMPTY:
        setBlockItem(TOOL_EMPTY);

        break;
    case TOOL_LOCKIN:
      //  setBlockItem(TOOL_LOCKIN);
      //  imgLockIn = QPixmap(STR_LOCKIN);
       // setBlockItem(NULL_VALUE);

        if(blockType!=TOOL_EMPTY)
        {
            if(MainWindow::isPressCtrl)
            {
                setLockInFlag(false);
             }else
             {
                 setLockInFlag(true);
             }
         }




        if(blockType==TOOL_BARRIER
               ||blockType==TOOL_BARRIER_CLONE
                ||blockType==TOOL_BARRIER_MUSHROOM
                ||blockType==TOOL_BARRIER_HIDE
                ||blockType==TOOL_EMPTY
                ||blockType==TOOL_DIAMOND
                ||blockType==TOOL_BARRIER_MUSHROOMx2
                ||blockType==TOOL_TOMATO_LARGE
                ||blockType==TOOL_CABBAGE_LARGE
                ||blockType==TOOL_CORN_LARGE
                ||blockType==TOOL_EGGPLANT_LARGE
                ||blockType==TOOL_CARROT_LARGE
                ||blockType==TOOL_BARRIER_SPECIAL
                ||blockType==TOOL_MUSHROOM_MOVEABLE
                ||blockType==TOOL_REMOVE)
        {
                setBlockItem(NULL_VALUE);
                imgBlock = QPixmap(STR_EMPTY);
        }

        break;
    case TOOL_DIAMOND:
        setBlockItem(TOOL_DIAMOND);
        setLockInFlag(false);
        break;

    case TOOL_BARRIER_MUSHROOMx2:
        setBlockItem(TOOL_BARRIER_MUSHROOMx2);
           setLockInFlag(false);
        break;

    case TOOL_CARROT_LARGE:
        setBlockItem(TOOL_CARROT_LARGE);
          setLockInFlag(false);
        break;
    case TOOL_TOMATO_LARGE:
        setBlockItem(TOOL_TOMATO_LARGE);
          setLockInFlag(false);
        break;
    case TOOL_CABBAGE_LARGE:
         setBlockItem(TOOL_CABBAGE_LARGE);
           setLockInFlag(false);
        break;
    case TOOL_CORN_LARGE:
         setBlockItem(TOOL_CORN_LARGE);
           setLockInFlag(false);
        break;
    case TOOL_EGGPLANT_LARGE:
         setBlockItem(TOOL_EGGPLANT_LARGE);
           setLockInFlag(false);
        break;
    case TOOL_BARRIER_SPECIAL:
        setBlockItem(TOOL_BARRIER_SPECIAL);
          setLockInFlag(false);
        break;
    case TOOL_MUSHROOM_MOVEABLE:
        setBlockItem(TOOL_MUSHROOM_MOVEABLE);
          setLockInFlag(false);
        break;

    }

    update();
}

void GraphicsBlockItem::showGlass(int _layer)
{

    setGroundLayer(_layer);

    switch(_layer)
    {
    case 1:
        if(blockType!=TOOL_BARRIER)
        {
            imgGlass = QPixmap(STR_GLASS);
            isShowGlassFlag = true;
        }
        break;
    case 2:
        if(blockType!=TOOL_BARRIER)
        {
            imgGlass = QPixmap(STR_GLASS2);
            isShowGlassFlag = true;
        }
        break;

    }



}

void GraphicsBlockItem::hideGlass()
{
    imgGlass = QPixmap(STR_EMPTY);
    isShowGlassFlag = false;
    setGroundLayer(GROUND_TYPE_FLOOR);

}

bool GraphicsBlockItem::isShowGlass()
{
    return isShowGlassFlag;
}

int GraphicsBlockItem::getBlockType()
{
    return blockType;
}

void GraphicsBlockItem::setBlockType(int _type)
{
    if(_type==-1)
    {
        _type = NULL_VALUE;
    }
    blockType = _type;
}

void GraphicsBlockItem::setBlockItem(int _type)
{

    qDebug()<<"setBlockItem:type:"<<_type;


    setBlockType(_type);
    if(MainWindow::isPressCtrl)
    {
       // setBlockItem(TOOL_NULL);
         setBlockType(NULL_VALUE);
         setLockInFlag(false);

         imgBlock = QPixmap(STR_EMPTY);
         imgLockIn = QPixmap(STR_EMPTY);

        return;
    }
    switch(_type)
    {
    case TOOL_NULL:
        imgBlock = QPixmap(STR_EMPTY);

        break;
     case TOOL_TOMATO:
        imgBlock = QPixmap(STR_TOMATO);
        break;
     case  TOOL_CARROT://1
    imgBlock = QPixmap(STR_CARROT);
     break;
      case  TOOL_CABBAGE://2
      imgBlock = QPixmap(STR_CABBAGE);
     break;
      case  TOOL_CORN://3
        imgBlock = QPixmap(STR_CORN);
     break;
      case  TOOL_EGGPLANT://4
        imgBlock = QPixmap(STR_EGGPLANT);
     break;
    case  TOOL_REMOVE://105
      imgBlock = QPixmap(STR_REMOVE);
   break;
      case  TOOL_ONION://5
        imgBlock = QPixmap(STR_ONION);
     break;
      case  TOOL_BARRIER://6
        imgBlock = QPixmap(STR_BARRIER);
        hideGlass();
     break;
    case TOOL_BARRIER_HIDE://6*2
        imgBlock = QPixmap(STR_BARRIER_HIDE);
        hideGlass();
        break;

    case TOOL_EMPTY:
        imgBlock = QPixmap(STR_LIMIT);
         hideGlass();
        break;
    case TOOL_BARRIER_MUSHROOM:
        imgBlock = QPixmap(STR_BARRIER_MUSHROOM);
        hideGlass();
        break;
    case TOOL_BARRIER_CLONE:
        imgBlock = QPixmap(STR_BARRIER_CLONE);
        hideGlass();
        break;
    case TOOL_LOCKIN:
        imgLockIn = QPixmap(STR_LOCKIN);

        break;
    case TOOL_DIAMOND:
        imgBlock = QPixmap(STR_DIAMOND);

        break;

    case TOOL_BARRIER_MUSHROOMx2:
        imgBlock = QPixmap(STR_BARRIER_MUSHROOMx2);
        hideGlass();
        break;

    case TOOL_CARROT_LARGE:
        imgBlock = QPixmap(STR_CARROT_LARGE);
        break;
    case TOOL_TOMATO_LARGE:
        imgBlock = QPixmap(STR_TOMATO_LARGE);
        break;
    case TOOL_CABBAGE_LARGE:
        imgBlock = QPixmap(STR_CABBAGE_LARGE);
        break;
    case TOOL_EGGPLANT_LARGE:
        imgBlock = QPixmap(STR_EGGPLANT_LARGE);
        break;
    case TOOL_CORN_LARGE:
        imgBlock = QPixmap(STR_CORN_LARGE);
        break;
    case TOOL_BARRIER_SPECIAL:
        imgBlock = QPixmap(STR_BARRIER_SPECIAL);
        break;
    case TOOL_MUSHROOM_MOVEABLE:
    imgBlock = QPixmap(STR_MUSHROOM_MOVEABLE);
        break;
    }
}

int GraphicsBlockItem::getExportGroundType()
{
//    if(groundType>0)
//    {
//         //正常地表
//        return isShowGlassFlag?groundType+MASK_VALUE:groundType;
//    }else
//    {
//        //翻转地表
//        return isShowGlassFlag?groundType-MASK_VALUE:groundType;
//    }

   return groundType>0?groundType:groundType+MASK_VALUE;
   return groundType;
}

int GraphicsBlockItem::getGroundLayer()
{
    return groundLayer;
}

void GraphicsBlockItem::setGroundLayer(int _layer)
{
    groundLayer = _layer;
}

void GraphicsBlockItem::setLockInFlag(bool _lock)
{
    lockInFlag = _lock;

    if(!_lock)
    {
         imgLockIn = QPixmap(STR_EMPTY);

    }else
    {
        imgLockIn = QPixmap(STR_LOCKIN);

    }
}

bool GraphicsBlockItem::isLockIn()
{
    return lockInFlag;
}

int GraphicsBlockItem::width()
{
    return imgGround.width();
}

int GraphicsBlockItem::height()
{
    return imgGround.height();
}
