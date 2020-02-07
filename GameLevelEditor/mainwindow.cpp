#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "leveltreeitem.h"

#include "graphicsblockitem.h"

#include <QDebug>

#include "graphicsblockscene.h"

#include "LevelGlobal.h"

#include <QKeyEvent>

#include <QStandardItemModel>

#include <QFileDialog>

#include <QMessageBox>


/*
 *导出数据结构：文件名：data.bin
 *
 *关卡的总数量：levelSize
 *关卡的行与列：levelRow,levelColumn
 *关卡的胜利条件的数量
 *关卡的胜利条件开关，分值时间 等 后期处理
 *根据行与列：关卡的地表层数据，对于存在玻璃地面的+128
 *方块数据：5种颜色，阻碍物，空类型等
 *
 *在C++端：存相应的类型
 *
 */

/*
 *编辑器后期功能添加：
 *关卡复制：可以复制某一个关卡，方便在基础上修改
 *关卡交换：如果第30关和第29关想调换一下，可以进行数据交换
 */
float MainWindow::scaleRadio = 1.0;

int MainWindow::toolButtonTypes =TOOL_GROUND;

bool MainWindow::isPressCtrl = false;

MainWindow *MainWindow::instance = NULL;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    newLevelDialog(NULL),
    scene(NULL),
    rectItem(NULL),
    groundDialog(NULL),
    treeWidget(NULL),
    exchangeDialog(NULL)



{
    ui->setupUi(this);

    treeWidget = new LevelTreeWidget();
    treeWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    //treeWidget->setTreeItemsArray(treeItemsArray);

    treeWidget->setColumnCount(1);

    treeWidget->setHeaderLabel(STR_LEVEL_HEADER_NAME);

    ui->verticalLayout_2->addWidget(treeWidget);

    newLevelDialog = new NewLevelDialog(this);
    newLevelDialog->setTreeWidget(treeWidget);
    //newLevelDialog->setTreeItemsArray(treeItemsArray);

    groundDialog = new GroundDialog(this);

    exchangeDialog = new ExchangeLevelDialog(this);

   // groundDialog = new GroundDialog(this);

    //groundDialog = new GroundDialog();


    //将工具按钮添加到toolButtonArray中
    toolButtonArray.push_back(ui->toolButton_1);
    toolButtonArray.push_back(ui->toolButton_2);
    toolButtonArray.push_back(ui->toolButton_3);
    toolButtonArray.push_back(ui->toolButton_4);
    toolButtonArray.push_back(ui->toolButton_5);
    toolButtonArray.push_back(ui->toolButton_6);
    toolButtonArray.push_back(ui->toolButton_7);
    toolButtonArray.push_back(ui->toolButton_8);
     toolButtonArray.push_back(ui->toolButton_10);
    toolButtonArray.push_back(ui->toolButton_11);
    toolButtonArray.push_back(ui->toolButton_12);
    toolButtonArray.push_back(ui->toolButton_13);
    toolButtonArray.push_back(ui->toolButton_16);
    toolButtonArray.push_back(ui->toolButton_14);
    toolButtonArray.push_back(ui->toolButton_15);
    toolButtonArray.push_back(ui->toolButton_17);

    toolButtonArray.push_back(ui->toolButton_18);
    toolButtonArray.push_back(ui->toolButton_19);
    toolButtonArray.push_back(ui->toolButton_20);
    toolButtonArray.push_back(ui->toolButton_21);
    toolButtonArray.push_back(ui->toolButton_22);
    toolButtonArray.push_back(ui->toolButton_23);

    toolButtonArray.push_back(ui->toolButton_24);
    toolButtonArray.push_back(ui->toolButton);



    scene = new GraphicsBlockScene();
    newLevelDialog->setSceneDelegate(scene);
    treeWidget->setSceneDelegate(scene);

    ui->graphicsView->setScene(scene);

    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    scene->setBackgroundBrush(grayBrush);


    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);

    //添加树Tree双击事件


    //添加背景
   // scene->addPixmap(QPixmap(":Icon/res/battle_background.png"));
    //QGraphicsPixmapItem pixmap = new QGraphicsPixmapItem()
//    for(int i=0;i<DEFAULT_MAP_ROWS;++i)
//    {
//        for(int j=0;j<DEFAULT_MAP_COLUMNS;++j)
//        {
//            GraphicsBlockItem *item = new GraphicsBlockItem();
//            item->setIndex(i*7+j);
//            scene->addItem(item);
//            item->setPos(j*item->width(),i*item->height());
//            item->initDefaultPosition(j*width,i*width);

//            item->setGroundFrame(groundMapData[i][j]);
//            blockItemArray.push_back(item);

//        }

//    }

//    scene->setBlockItemArray(blockItemArray);



    // ui->treeWidget->addTopLevelItem(rootItem1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNewFile_triggered()
{
    newLevelDialog->createNewLevel();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"HELO";

}

void MainWindow::mousePressEvent(QMouseEvent *)
{
     qDebug()<<"mousePressEvent";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();

    if((event->modifiers() & Qt::ControlModifier))
    {
        isPressCtrl = true;
        qDebug()<<"pressed";
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
   isPressCtrl = false;
}

void MainWindow::zoom()
{

    int count = scene->levelItem->blockItemArray.count();
    for(int i=0;i<count;++i)
    {
        GraphicsBlockItem* item = (GraphicsBlockItem*)scene->levelItem->blockItemArray[i];

        int x = item->pos.x()*scaleRadio;
        int y = item->pos.y()*scaleRadio;
        item->setPos(x,y);
        item->update();
    }

}

//void MainWindow::zoomOut()
//{
//    if(scaleRadio<=0.25f)
//    {
//        scaleRadio = 0.25f;
//    }
//    scaleRadio -= 0.25f;

//    //update pos
//    int count = blockItemArray.count();
//    for(int i=0;i<count;++i)
//    {
//        GraphicsBlockItem* item = (GraphicsBlockItem*)blockItemArray[i];

//        int x = item->pos.x()*scaleRadio;
//        int y = item->pos.y()*scaleRadio;
//        item->setPos(x,y);
//    }


//}

float MainWindow::getScaleRadio()
{
    return scaleRadio;
}

void MainWindow::hideAllToolButtons()
{
    for(int i=0;i<toolButtonArray.count();++i)
    {
        QToolButton* button = (QToolButton*)toolButtonArray[i];
        button->setChecked(false);
    }
}

void MainWindow::setToolButtonType(int _type)
{

    hideAllToolButtons();

    toolButtonTypes = _type;
    switch(toolButtonTypes)
    {
        case TOOL_GROUND:
        ui->toolButton_1->setChecked(true);
        groundDialog->show();
        break;
    case TOOL_GLASS:
        ui->toolButton_2->setChecked(true);

        break;
    case TOOL_TOMATO:
        ui->toolButton_3->setChecked(true);
        break;
    case TOOL_GLASS2:
        ui->toolButton_16->setChecked(true);
        break;

    case TOOL_CARROT:
        ui->toolButton_4->setChecked(true);

        break;
    case TOOL_CABBAGE:
        ui->toolButton_5->setChecked(true);

        break;
    case TOOL_CORN:
        ui->toolButton_6->setChecked(true);

        break;
    case TOOL_EGGPLANT:
        ui->toolButton_7->setChecked(true);

        break;
    case TOOL_REMOVE:
        ui->toolButton->setChecked(true);

        break;
    case TOOL_BARRIER_CLONE:
        ui->toolButton_10->setChecked(true);

        break;
    case TOOL_BARRIER:
        ui->toolButton_8->setChecked(true);

        break;

    case TOOL_LOCKIN:
        ui->toolButton_14->setChecked(true);

        break;
    case TOOL_EMPTY:
        ui->toolButton_11->setChecked(true);

        break;

    case TOOL_BARRIER_HIDE:
    ui->toolButton_12->setChecked(true);

        break;
    case TOOL_BARRIER_MUSHROOM:
        ui->toolButton_13->setChecked(true);

        break;
    case TOOL_DIAMOND:
        ui->toolButton_15->setChecked(true);
        break;

    case TOOL_BARRIER_MUSHROOMx2:
        ui->toolButton_17->setChecked(true);
        break;

    case TOOL_TOMATO_LARGE:
        ui->toolButton_19->setChecked(true);
        break;
    case TOOL_CARROT_LARGE:
        ui->toolButton_18->setChecked(true);
        break;
    case TOOL_CABBAGE_LARGE:
        ui->toolButton_21->setChecked(true);
        break;
    case TOOL_CORN_LARGE:
        ui->toolButton_22->setChecked(true);
        break;
    case TOOL_EGGPLANT_LARGE:
        ui->toolButton_20->setChecked(true);
        break;

    case TOOL_BARRIER_SPECIAL:
        ui->toolButton_23->setChecked(true);
        break;

    case TOOL_MUSHROOM_MOVEABLE:
        ui->toolButton_24->setChecked(true);
        break;
    }

    if(_type==TOOL_GROUND)
    {
        groundDialog->show();
    }else
    {
        if(!groundDialog->isHidden())
        {
                groundDialog->hide();
        }

    }
}

MainWindow *MainWindow::sharedInstance()
{
    if(instance==NULL)
    {
        instance = new MainWindow();
    }
    return instance;
}

void MainWindow::writeLevels()
{

    int size = treeItemsArray.count();

    if(size==0)
    {
        return;
    }

    QFile file("Levels"+STR_PROJECT_SUFFIX);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"couldn't write files";
        return;
    }

    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_4_7);

    //写入文件校验码
    out<<quint32(FILE_CHECK_HEADER_CODE);
    //关卡数量
    out<<size;
    //每一关的数据

    for(int i=0;i<size;++i)
    {
        LevelTreeItem* levelItem = (LevelTreeItem*)treeItemsArray[i];

        //写入基础属性
        out<<levelItem->round;
        out<<levelItem->time;
        //定入类型长度
        int specialBlockTypeSize = levelItem->vecSpecialBlockType.size();
        out<<specialBlockTypeSize;

        for(int i=0;i<specialBlockTypeSize;++i)
        {
            out<<levelItem->vecSpecialBlockType[i];
        }

        out<<levelItem->score;
        out<<levelItem->diamond;

        out<<levelItem->specialBonusCount;

        out<<levelItem->singleCarrotCount;
        out<<levelItem->singleCabbageCount;
        out<<levelItem->signleTomatoCount;

        out<<levelItem->singleCornCount;
        out<<levelItem->signleEggplantCount;

        out<<levelItem->removeAllIce;
        out<<levelItem->removeAllFloor;
        out<<levelItem->removeAllMushRoom;
        out<<levelItem->removeAllSpecialType;
        out<<levelItem->removeAllCarrot;
        out<<levelItem->removeAllCabbage;
        out<<levelItem->removeAllCorn;
        out<<levelItem->removeAllEggplant;
        out<<levelItem->removeAllTomato;

        out<<levelItem->removeAllVegetable;

        out<<levelItem->removeAllLaydBug;
        out<<levelItem->removeAllSnowField;

        //out<<levelItem->star3Score;
        //out<<levelItem->star2Score;
        //out<<levelItem->star1Score;


        out<<levelItem->star1Score;
        out<<levelItem->star2Score;
        out<<levelItem->star3Score;






        //写入关卡行与列
        out<<levelItem->getRow();
        out<<levelItem->getColumn();

        int itemCount = levelItem->blockItemArray.count();

        for(int j=0;j<itemCount;++j)
        {
            GraphicsBlockItem* blockItem = (GraphicsBlockItem*)levelItem->blockItemArray[j];

            //x,y,index,groundType,blockType
            out<<(int)blockItem->pos.x();
            out<<(int)blockItem->pos.y();
            out<<(int)blockItem->getIndex();
            //是否显示玻璃
//            if(blockItem->isShowGlass())
//            {
//                out<<(int)1;
//            }else
//            {
//                out<<(int)0;
//            }

            if(blockItem->isShowGlass())
            {
                out<<(int)blockItem->getGroundLayer();
            }else
            {
                out<<(int)GROUND_TYPE_FLOOR;
            }

            out<<(int)blockItem->getGroundType();
            out<<(int)blockItem->getBlockType();

            //写入锁住标识
            if(blockItem->isLockIn())
            {
                out<<(int)1;
                qDebug()<<"isLockIn:111111111111111111";
            }else
            {
                out<<(int)0;
            }



        }

    }


    file.flush();
    file.close();

    qDebug()<<"write levels success!!!";

    QMessageBox::information(this,tr("提示"),tr("存储完成!"));
}

/*
 *
 *  1.总量size:

    2.每一关的row,column


    5.是全空块，空块要进行随机，非空的直接填充。


    3.地图的地形值

    4.地块值

 */
void MainWindow::exportLevels()
{
    int size = treeItemsArray.count();

    if(size==0)
    {
        return;
    }

    QFile file("levels"+STR_LEVEL_SUFFIX);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"couldn't write files";
        return;
    }

    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_4_7);

    //关卡数量
    out<<size;
    //每一关的数据

    for(int i=0;i<size;++i)
    {
        LevelTreeItem* levelItem = (LevelTreeItem*)treeItemsArray[i];

        //写入基础属性

        out<<(int)levelItem->round;
        out<<(int)levelItem->time;
        //定入类型长度
        int specialBlockTypeSize = levelItem->vecSpecialBlockType.size();
        out<<(int)specialBlockTypeSize;

        for(int i=0;i<specialBlockTypeSize;++i)
        {
            out<<(int)levelItem->vecSpecialBlockType[i];
        }

        out<<(int)levelItem->score;
        out<<(int)levelItem->diamond;

        out<<(int)levelItem->specialBonusCount;

        out<<(int)levelItem->singleCarrotCount;
        out<<(int)levelItem->signleTomatoCount;
        out<<(int)levelItem->singleCabbageCount;

        out<<(int)levelItem->singleCornCount;
        out<<(int)levelItem->signleEggplantCount;

        out<<(int)levelItem->removeAllIce;
        out<<(int)levelItem->removeAllFloor;
        out<<(int)levelItem->removeAllMushRoom;
        out<<(int)levelItem->removeAllSpecialType;
        out<<(int)levelItem->removeAllTomato;
        out<<(int)levelItem->removeAllCarrot;
        out<<(int)levelItem->removeAllCabbage;
        out<<(int)levelItem->removeAllCorn;
        out<<(int)levelItem->removeAllEggplant;

        out<<(int)levelItem->removeAllVegetable;

        out<<(int)levelItem->removeAllLaydBug;
        out<<(int)levelItem->removeAllSnowField;

        out<<(int)levelItem->star1Score;
        out<<(int)levelItem->star2Score;
        out<<(int)levelItem->star3Score;

        //写入地面的数量
        int grassTypeCount = getSpecialBlockTypeCount(levelItem,TOOL_GLASS);
        out<<(int)grassTypeCount;
        qDebug()<<"grassTypeCount:"<<grassTypeCount;
        //写入石头数量
        int stoneTypeCount = getSpecialBlockTypeCount(levelItem,TOOL_BARRIER_MUSHROOM);
        out<<(int)stoneTypeCount;
        qDebug()<<"stoneTypeCount:"<<stoneTypeCount;
        //写入同色类型数量
        int largeTypeCount = getSpecialBlockTypeCount(levelItem,TOOL_CARROT_LARGE);
        out<<(int)largeTypeCount;
        qDebug()<<"largeTypeCount:"<<largeTypeCount;
        //写入特别类型数量
        int specialTypeCount = getSpecialBlockTypeCount(levelItem,TOOL_BARRIER_SPECIAL);
        out<<(int)specialTypeCount;
        qDebug()<<"specialTypeCount:"<<specialTypeCount;
        //写入飘虫数量
        int ladyBugCount = getSpecialBlockTypeCount(levelItem,TOOL_MUSHROOM_MOVEABLE);
         qDebug()<<"{ladyBugCount:"<<ladyBugCount;
        out<<(int)ladyBugCount;
        //写入雪地数量
        int snowFieldCount = getSpecialBlockTypeCount(levelItem,TOOL_BARRIER_CLONE);
        qDebug()<<"{snowFieldCount:"<<snowFieldCount;
        out<<(int)snowFieldCount;


        //写入关卡的行列
        out<<levelItem->getRow();
        out<<levelItem->getColumn();

        int itemCount = levelItem->blockItemArray.count();

        for(int j=0;j<itemCount;++j)
        {
            GraphicsBlockItem* blockItem = (GraphicsBlockItem*)levelItem->blockItemArray[j];

            if(blockItem->isShowGlass())
            {
                out<<blockItem->getGroundLayer();
            }else
            {
                out<<GROUND_TYPE_FLOOR;
            }

            //groundType,blockType
            out<<(int)blockItem->getExportGroundType();


            out<<(int)blockItem->getBlockType();

            //写入锁住标识
            if(blockItem->isLockIn())
            {
                out<<(int)1;
            }else
            {
                out<<(int)0;
            }

        }

    }

    file.flush();
    file.close();

    qDebug()<<"write levels success!!!";

    QMessageBox::information(this,tr("提示"),tr("已导出二进制文件!"));

}

int MainWindow::getSpecialBlockTypeCount(LevelTreeItem* levelItem,int _type)
{
    int count = 0;

    for(int i=0;i<levelItem->blockItemArray.size();++i)
    {
        GraphicsBlockItem* blockItem = (GraphicsBlockItem*)levelItem->blockItemArray[i];


        switch(_type)
        {
           case TOOL_GLASS:
            if(blockItem->isShowGlassFlag)
            {
              //  qDebug()<<"showGlass!!!!";
                count++;
            }
            break;
        case TOOL_LOCKIN:

            if(blockItem->isLockIn())
            {
                  count++;

              //    qDebug()<<"TOOL_LOCKIN!!!!";
            }

            break;
        case TOOL_BARRIER_MUSHROOMx2:
        case TOOL_BARRIER_MUSHROOM:
            // qDebug()<<"TOOL_MUSHROOM!!!!";
             if(blockItem->getBlockType()==TOOL_BARRIER_MUSHROOM||blockItem->getBlockType()==TOOL_BARRIER_MUSHROOMx2)
             {
                count++;
             }
            break;
        case TOOL_TOMATO_LARGE:
        case TOOL_CARROT_LARGE:
        case TOOL_CABBAGE_LARGE:
        case TOOL_CORN_LARGE:
        case TOOL_EGGPLANT_LARGE:
            if(blockItem->getBlockType()==TOOL_TOMATO_LARGE
                    ||blockItem->getBlockType()==TOOL_CARROT_LARGE
                    ||blockItem->getBlockType()==TOOL_CABBAGE_LARGE
                    ||blockItem->getBlockType()==TOOL_CORN_LARGE
                    ||blockItem->getBlockType()==TOOL_EGGPLANT_LARGE)
            {
               //  qDebug()<<"special vegetable!!!!";
               count++;
            }
            break;

        case TOOL_BARRIER_SPECIAL:
            if(blockItem->getBlockType()==TOOL_BARRIER_SPECIAL)
            {
            //qDebug()<<"TOOL_BARRIER_SPECIAL!!!!";
                count++;

            }
            break;
           // case TOOL_

        case TOOL_MUSHROOM_MOVEABLE://飘虫
            if(blockItem->getBlockType()==TOOL_MUSHROOM_MOVEABLE)
            {
                count++;
            }
            break;
        case TOOL_BARRIER_CLONE://雪地
            if(blockItem->getBlockType()==TOOL_BARRIER_CLONE)
            {
                count++;
            }
            break;

        }

    }

    //qDebug()<<"special block:"<<count;

    return count;

}

void MainWindow::loadLevels(QString _strName)
{
     scene->removeAllItems();

     //scene->levelItem = NULL;

     qDebug()<<"_strName:"<<_strName;

    treeWidget->clear();
    treeItemsArray.clear();


    int size = 0;

    QFile file(_strName);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"couldn't read files";
        return;
    }

    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_4_7);

    //写入文件校验码
    int fileCheckHeadCode = 0;
    out>>fileCheckHeadCode;

    qDebug()<<"校验:"<<fileCheckHeadCode;


    if(fileCheckHeadCode!=FILE_CHECK_HEADER_CODE)
    {
        QMessageBox::warning(this,tr("错误日志"),tr("文件头不正确,文件无效!"));
        return;
    }


    //关卡数量
    out>>size;

    qDebug()<<"关卡数量:"<<size;

    //每一关的数据
    for(int i=0;i<size;++i)
    {
        LevelTreeItem* levelItem = new LevelTreeItem(treeWidget,newLevelDialog->getDefaultLevelName());

       treeItemsArray.push_back(levelItem);

       //写入基础属性
       out>>levelItem->round;
       out>>levelItem->time;
       //定入类型长度
       int specialBlockTypeSize = 0;

       out>>specialBlockTypeSize;

       for(int i=0;i<specialBlockTypeSize;++i)
       {
           int blockType = 0;
           out>>blockType;
           levelItem->vecSpecialBlockType.push_back(blockType);

          // out<<levelItem->vecSpecialBlockType[i];
       }

       out>>levelItem->score;
       out>>levelItem->diamond;

       out>>levelItem->specialBonusCount;

       out>>levelItem->singleCarrotCount;
       out>>levelItem->singleCabbageCount;
       out>>levelItem->signleTomatoCount;

       out>>levelItem->singleCornCount;
       out>>levelItem->signleEggplantCount;

       out>>levelItem->removeAllIce;
       out>>levelItem->removeAllFloor;
       out>>levelItem->removeAllMushRoom;
       out>>levelItem->removeAllSpecialType;
       out>>levelItem->removeAllCarrot;
       out>>levelItem->removeAllCabbage;
       out>>levelItem->removeAllCorn;
       out>>levelItem->removeAllEggplant;
       out>>levelItem->removeAllTomato;

       out>>levelItem->removeAllVegetable;



       out>>levelItem->removeAllLaydBug;
       out>>levelItem->removeAllSnowField;

       out>>levelItem->star1Score;
       out>>levelItem->star2Score;
       out>>levelItem->star3Score;

       //行与列
       out>>levelItem->row;
       out>>levelItem->column;

       qDebug()<<"row:"<<levelItem->getRow()<<",column:"<<levelItem->getColumn();

       int itemCount = levelItem->getRow()*levelItem->getColumn();

       int row = 0;
       int col = 0;
       for(int j=0;j<itemCount;++j)
       {
             GraphicsBlockItem* item = new GraphicsBlockItem();

              int x = 0;
              int y = 0;
              int index = 0;
              int groundType = 0;
              int blockType = 0;


              //

             // col = j/6;


               //读取x,y
               out>>x;
               out>>y;
               out>>index;
              int glassLayer =0;
              out>>glassLayer;

              out>>groundType;
              out>>blockType;

              //读取是否被锁住
             int lockInFlag = -1;

              out>>lockInFlag;

              qDebug()<<"x:"<<x<<",y:"<<y<<",index:"<<index<<",groundType:"<<groundType<<",blockType:"<<blockType;

              item->setPos(x,y);
              item->initDefaultPosition(x,y);

              //设置锁住开关
             item->setLockInFlag(lockInFlag);


              if(glassLayer==GROUND_LAYER_1)
              {
                  item->showGlass(GROUND_LAYER_1);
              }
              else if(glassLayer==GROUND_LAYER_2)
              {
                  item->showGlass(GROUND_LAYER_2);
              }
              else
              {
                  item->hideGlass();
              }

               item->setIndex(index);
               //处理地表

               item->setGroundFrame(groundType);




               row = j/levelItem->getColumn();
               qDebug()<<"row:"<<row;

//               if(row==8)
//               {
//                   item->setBlockItem(TOOL_EMPTY);
//                    item->setLockInFlag(false);
//               }else
//               {
//                   //处理方块层
//                   item->setBlockItem(blockType);

//               }


               //处理方块层
               item->setBlockItem(blockType);


//               item->setBlockItem(TOOL_EMPTY);
//               item->setLockInFlag(false);
               levelItem->addBlockItem(item);


       }
    }


    //处理树表
    int treeItemCount = treeWidget->topLevelItemCount();
    for(int i=0;i<treeItemCount;++i)
    {
       treeWidget->topLevelItem(i)->setSelected(false);
    }
    //默认选中最后一项
    treeWidget->topLevelItem(treeItemCount-1)->setSelected(true);

    //删除场景中所有的元素
    scene->removeAllItems();

    scene->setLevelItem(treeItemsArray[treeItemCount-1]);

    scene->update();


    file.flush();
    file.close();

    qDebug()<<"read levels success!!!";
}



void MainWindow::on_actionZoomIn_triggered()
{
    if(treeWidget->currentItem()!=NULL)
    {
        if(scaleRadio>=1)
            {
                scaleRadio = 1;
                return;
            }
            scaleRadio+=0.25f;

            zoom();
    }

}

void MainWindow::on_actionZoomOut_triggered()
{
    if(treeWidget->currentItem()!=NULL)
    {
        if(scaleRadio<=0.75f)
        {
            scaleRadio = 0.75f;
        }
        scaleRadio -= 0.25f;

       zoom();
    }

}

void MainWindow::on_actionDebug_triggered()
{
    qDebug()<<"--------------";

//    for(int i=0;i<blockItemArray.count();++i)
//    {
//        GraphicsBlockItem *item = (GraphicsBlockItem*)blockItemArray[i];
//        item->debug();
//    }

    //qDebug()<<treeItemsArray.count();


    //LevelTreeItem* item = (LevelTreeItem*)treeItemsArray[0];
//    LevelTreeItem* item = (LevelTreeItem*)treeWidget->currentItem();

//    if(item!=NULL)
//    {
//        item->debug();
//    }

    //groundDialog->show();

   // int spe = getSpecialBlockTypeCount(TOOL_BARRIER_SPECIAL);
   // int mushroom2 = getSpecialBlockTypeCount(TOOL_BARRIER_MUSHROOMx2);

   // qDebug()<<"MUSH_ROOM:"<<mushroom;

    //qDebug()<<"value:"<<getSpecialBlockTypeCount(scene->levelItem,TOOL_BARRIER_SPECIAL);

   // getSpecialBlockTypeCount(levelItem,TOOL_MUSHROOM_MOVEABLE);

   // qDebug()<<"mushroom:"<<spe;
   // groundDialog->show();


    //写入地面的数量
    int grassTypeCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_GLASS);

    qDebug()<<"grassTypeCount:"<<grassTypeCount;
    //写入石头数量
    int stoneTypeCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_BARRIER_MUSHROOM);

    qDebug()<<"stoneTypeCount:"<<stoneTypeCount;
    //写入同色类型数量
    int largeTypeCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_CARROT_LARGE);

    qDebug()<<"largeTypeCount:"<<largeTypeCount;
    //写入特别类型数量
    int specialTypeCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_BARRIER_SPECIAL);

    qDebug()<<"specialTypeCount:"<<specialTypeCount;
    //写入飘虫数量
    int ladyBugCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_MUSHROOM_MOVEABLE);
     qDebug()<<"{ladyBugCount:"<<ladyBugCount;

    //写入雪地数量
    int snowFieldCount = getSpecialBlockTypeCount(scene->levelItem,TOOL_BARRIER_CLONE);
    qDebug()<<"{snowFieldCount:"<<snowFieldCount;





}


void MainWindow::on_toolButton_1_clicked()
{
    setToolButtonType(TOOL_GROUND);

}

void MainWindow::on_toolButton_2_clicked()
{
    setToolButtonType(TOOL_GLASS);
}

void MainWindow::on_toolButton_3_clicked()
{
    setToolButtonType(TOOL_TOMATO);
}

void MainWindow::on_toolButton_4_clicked()
{
    setToolButtonType(TOOL_CARROT);
}

void MainWindow::on_toolButton_5_clicked()
{
    setToolButtonType(TOOL_CABBAGE);
}

void MainWindow::on_toolButton_6_clicked()
{
    setToolButtonType(TOOL_CORN);
}

void MainWindow::on_toolButton_7_clicked()
{
    setToolButtonType(TOOL_EGGPLANT);
}

void MainWindow::on_toolButton_8_clicked()
{
    setToolButtonType(TOOL_BARRIER);
}

void MainWindow::on_toolButton_10_clicked()
{
    setToolButtonType(TOOL_BARRIER_CLONE);
}

void MainWindow::on_toolButton_11_clicked()
{
    setToolButtonType(TOOL_EMPTY);
}

void MainWindow::on_action_Delete_triggered()
{
//    LevelTreeItem* treeItem = (LevelTreeItem*)treeWidget->currentItem();

//    qDebug()<<treeItem->getName();


    //are you sure to delete this level


    if(treeWidget->currentItem()!=NULL)
    {
        int msg = QMessageBox::question(this,tr("删除关卡"),tr("你确定要删除本关卡吗?"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);

       if(msg==QMessageBox::Cancel)
       {
           return;
       }

        int index = treeWidget->currentIndex().row();

        treeWidget->takeTopLevelItem(index);

        scene->removeAllItems();

        treeItemsArray.remove(index);

        for(int i=0;i<treeItemsArray.count();++i)
        {
            LevelTreeItem* levelItem = (LevelTreeItem*)treeItemsArray[i];
            levelItem->setLabel(i+1);
        }
    }


}

void MainWindow::on_actionSave_triggered()
{
    int size = treeItemsArray.count();

    writeLevels();

    exportLevels();
}

void MainWindow::on_actionOpen_Project_triggered()
{

    const QFileDialog::Options options = QFlag(1);
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("打开项目文件..."),
                                                    "data.proj",
                                tr("*.proj"),
                                &selectedFilter,
                                options);


    qDebug()<<"fileName:"<<fileName;

    if(!fileName.isEmpty())
    {
        loadLevels(fileName);
    }

//    QFile file("Level_1.l");

//    if(!file.open(QFile::ReadOnly))
//    {
//        qDebug()<<"couldn't read file!";

//        return;
//    }


//    QDataStream in(&file);
//    in.setVersion(QDataStream::Qt_5_0);



//    int Num = 0;
//    QString str("");

//    in<<str;
//    qDebug()<<"read:"<<str;



//    file.flush();

//    file.close();
}

void MainWindow::on_action_Export_Bin_triggered()
{
    exportLevels();
}

void MainWindow::on_toolButton_12_clicked()
{
    setToolButtonType(TOOL_BARRIER_HIDE);
}

void MainWindow::on_action_About_triggered()
{
    char*  info;

    QByteArray ba = strInformation.toLatin1();

    info=ba.data();
    QMessageBox::information(this,tr("关于信息"),tr(info));
}

void MainWindow::on_toolButton_13_clicked()
{
    setToolButtonType(TOOL_BARRIER_MUSHROOM);
}

void MainWindow::on_toolButton_16_clicked()
{
    setToolButtonType(TOOL_GLASS2);
}

void MainWindow::on_toolButton_14_clicked()
{
    setToolButtonType(TOOL_LOCKIN);
}

void MainWindow::on_toolButton_15_clicked()
{
    setToolButtonType(TOOL_DIAMOND);
}

void MainWindow::on_toolButton_17_clicked()
{
      setToolButtonType(TOOL_BARRIER_MUSHROOMx2);
}

void MainWindow::on_toolButton_18_clicked()
{
    setToolButtonType(TOOL_CARROT_LARGE);
}

void MainWindow::on_toolButton_19_clicked()
{
     setToolButtonType(TOOL_TOMATO_LARGE);
}

void MainWindow::on_toolButton_21_clicked()
{
    setToolButtonType(TOOL_CABBAGE_LARGE);
}

void MainWindow::on_toolButton_20_clicked()
{
    setToolButtonType(TOOL_EGGPLANT_LARGE);
}

void MainWindow::on_toolButton_22_clicked()
{
    setToolButtonType(TOOL_CORN_LARGE);
}

void MainWindow::on_toolButton_23_clicked()
{
     setToolButtonType(TOOL_BARRIER_SPECIAL);
}

void MainWindow::on_action_2_triggered()
{
    //关卡交换
    if(treeWidget->currentItem()!=NULL)
    {
      //  LevelTreeItem* levelItem = (LevelTreeItem*)treeWidget->currentItem();

        exchangeDialog->exchangeLevel();
    }
}

void MainWindow::on_action_Paste_triggered()
{
    if(treeWidget->currentItem()!=NULL)
    {
        LevelTreeItem* levelItem = (LevelTreeItem*)treeWidget->currentItem();

        newLevelDialog->isEditLevel = false;

        if(levelItem!=NULL)
        {
            qDebug()<<"level name:"<<levelItem->getName();

            newLevelDialog->duplicateLevel(levelItem);

        }

    }else
    {
        qDebug()<<"you don't choose any level!";
    }
}

void MainWindow::on_action111_triggered()
{

    newLevelDialog->editLevel();
}

void MainWindow::on_toolButton_24_clicked()
{
    setToolButtonType(TOOL_MUSHROOM_MOVEABLE);
}

void MainWindow::on_toolButton_clicked()
{
      setToolButtonType(TOOL_REMOVE);
}
