#include "newleveldialog.h"
#include "ui_newleveldialog.h"

#include "QDebug"

#include "mainwindow.h"

#include "LevelGlobal.h"

const static QString STR_TITLE = "NewFile...";

const static int DEFAULT_ROWS = 9;
const static int DEFAULT_COLUMNS = 7;


NewLevelDialog::NewLevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewLevelDialog),
    treeWidget(NULL),
    scene(NULL),
    //duplicateItem(NULL),
    isEditLevel(NULL)
  ,isDuplicateLevel(false)
{
    ui->setupUi(this);

    setWindowTitle(STR_TITLE);

    ui->spinBox->setValue(DEFAULT_ROWS);
    ui->spinBox_2->setValue(DEFAULT_COLUMNS);


     ui->spinBox_3->setMinimum(1);

     ui->spinBox_4->setMinimum(1);


     ui->spinBox_5->setMinimum(1);
     ui->spinBox_6->setMinimum(1);
     ui->spinBox_7->setMinimum(1);

     int maxInteger = 999999999;//std::numeric_limits<int>::max();

     ui->spinBox_3->setMaximum(maxInteger);
     ui->spinBox_4->setMaximum(maxInteger);
     ui->spinBox_9->setMaximum(maxInteger);
     ui->spinBox_10->setMaximum(maxInteger);
     ui->spinBox_11->setMaximum(maxInteger);
     ui->spinBox_12->setMaximum(maxInteger);
     ui->spinBox_13->setMaximum(maxInteger);
     ui->spinBox_14->setMaximum(maxInteger);
     ui->spinBox_15->setMaximum(maxInteger);
     ui->spinBox_16->setMaximum(maxInteger);

     ui->spinBox_5->setMaximum(maxInteger);
     ui->spinBox_6->setMaximum(maxInteger);
     ui->spinBox_7->setMaximum(maxInteger);

    //设置默认名称
    //qDebug()<<"name:"<<getDefaultLevelName();

    ui->lineEdit->setEnabled(false);
}

NewLevelDialog::~NewLevelDialog()
{
    delete ui;
}

void NewLevelDialog::on_pushButton_clicked()
{


    if(isEditLevel)
    {
        isEditLevel = false;


        LevelTreeItem* levelItem = (LevelTreeItem*)treeWidget->currentItem();

        levelItem->initLevelCondition();

        updateCondition(levelItem);

        updateSpecialBlockType(levelItem);

        qDebug()<<"----------------------EditLevel-------------------";

        return;
    }
    //新建关卡
    LevelTreeItem* levelTreeItem = new LevelTreeItem(treeWidget,getDefaultLevelName());

    //在之后会出现多行的关卡再打开开关

    //duplicate
    if(isDuplicateLevel)
    {

        isDuplicateLevel = false;

        LevelTreeItem* currentLevelItem = (LevelTreeItem*)treeWidget->currentItem();


        qDebug()<<"----------------------duplicate-------------------";
        levelTreeItem->setRow(currentLevelItem->getRow());
        levelTreeItem->setColumn(currentLevelItem->getColumn());

        MainWindow::sharedInstance()->treeItemsArray.push_back(levelTreeItem);

        //创建后，默认选中最新创建的LevelItem
        int treeItemCount = treeWidget->topLevelItemCount();
        for(int i=0;i<treeItemCount;++i)
        {
           treeWidget->topLevelItem(i)->setSelected(false);
        }
        treeWidget->topLevelItem(treeItemCount-1)->setSelected(true);
        treeWidget->topLevelItem(treeItemCount-1)->setExpanded(true);
        treeWidget->update();


        updateCondition(levelTreeItem);

        updateSpecialBlockType(levelTreeItem);

        //duplicateItem = NULL;
        close();

        //创建场景

        for(int i=0;i<levelTreeItem->getRow();++i)
            {
            for(int j=0;j<levelTreeItem->getColumn();++j)
                {

                int id = i*levelTreeItem->getColumn()+j;

                GraphicsBlockItem *item = (GraphicsBlockItem*)currentLevelItem->blockItemArray[id];

                GraphicsBlockItem *newItem = new GraphicsBlockItem();
                newItem->setIndex(id);
                newItem->setPos(j*newItem->width(),i*newItem->height());
                newItem->initDefaultPosition(j*newItem->width(),i*newItem->height());
                newItem->setGroundFrame(item->getGroundType());

              // newItem->setBlockType(item->getBlockType());
                newItem->setGroundLayer(item->getGroundLayer());

                newItem->setBlockItem(item->getBlockType());
                newItem->setLockInFlag(item->isLockIn());



                levelTreeItem->addBlockItem(newItem);



                }

            }



        //删除场景中所有的元素
        scene->removeAllItems();

        scene->setLevelItem(levelTreeItem);
    }else
    {

        qDebug()<<"----------------------new level-------------------";
        //新建关卡
        levelTreeItem->setRow(ui->spinBox->value());
        levelTreeItem->setColumn(ui->spinBox_2->value());

        MainWindow::sharedInstance()->treeItemsArray.push_back(levelTreeItem);


        close();

        //创建场景

        for(int i=0;i<levelTreeItem->getRow();++i)
            {
            for(int j=0;j<levelTreeItem->getColumn();++j)
                {
                    GraphicsBlockItem *item = new GraphicsBlockItem();
                    item->setIndex(i*levelTreeItem->getColumn()+j);
                   // scene->addItem(item);
                    item->setPos(j*item->width(),i*item->height());
                    item->initDefaultPosition(j*item->width(),i*item->height());

                    item->setGroundFrame(GROUND_MAP_DATA[i][j]);

                    levelTreeItem->addBlockItem(item);

                }

            }



        //删除场景中所有的元素
        scene->removeAllItems();

        scene->setLevelItem(levelTreeItem);


        updateCondition(levelTreeItem);

        updateSpecialBlockType(levelTreeItem);

        levelTreeItem->debug();
        //close();

        //创建后，默认选中最新创建的LevelItem
        int treeItemCount = treeWidget->topLevelItemCount();
        for(int i=0;i<treeItemCount;++i)
        {
           treeWidget->topLevelItem(i)->setSelected(false);
        }
        treeWidget->topLevelItem(treeItemCount-1)->setSelected(true);
         //treeWidget->topLevelItem(treeItemCount-1)->setCheckState(0,CheckState::);

    }

}

void NewLevelDialog::setTreeWidget(QTreeWidget *treeWidget)
{
    this->treeWidget = treeWidget;
}

int NewLevelDialog::getTreeItemsCount() const
{
    return MainWindow::sharedInstance()->treeItemsArray.count()+1;
}

QString NewLevelDialog::getDefaultLevelName() const
{
    return QString(STR_DEFAULT_NAME+QString::number(getTreeItemsCount()));
}

void NewLevelDialog::createNewLevel()
{
    isEditLevel = false;
    isDuplicateLevel = false;

    initCondition();
    //init
    ui->radioButton_2->setChecked(true);

    setModal(true);
     ui->lineEdit->setText(getDefaultLevelName());
     exec();
}

void NewLevelDialog::editLevel()
{
    if(treeWidget->currentItem()!=NULL)
    {
        isEditLevel =true;

        treeWidget->layout();

        LevelTreeItem* levelItem = (LevelTreeItem*)treeWidget->currentItem();

        if(levelItem!=NULL)
         {
            //胜利条件

            //步数
            int round = levelItem->round;

            ui->radioButton_2->setChecked(round==0?false:true);
            ui->spinBox_3->setValue(round);


            //时间
            int time = levelItem->time;

            ui->radioButton->setChecked(time==0?false:true);
            ui->spinBox_4->setValue(time);


            //指定分数

            int score = levelItem->score;

            ui->checkBox_2->setChecked(score==0?false:true);
            ui->spinBox_9->setValue(score);


            //消除钻石数量
            int diamond = levelItem->diamond;

            ui->checkBox_7->setChecked(diamond==0?false:true);
            ui->spinBox_10->setValue(diamond);


            //需要生成N次特殊道具数量

            int specialBonusCount = levelItem->specialBonusCount;
            ui->checkBox_8->setChecked(specialBonusCount==0?false:true);
            ui->spinBox_11->setValue(specialBonusCount);



            //消除胡萝卜N个
            int singleCarrotCount = levelItem->singleCarrotCount;
            ui->checkBox_39->setChecked(singleCarrotCount==0?false:true);
            ui->spinBox_12->setValue(singleCarrotCount);


            //消除卷心菜N个
            int singleCabbageCount = levelItem->singleCabbageCount;
            ui->checkBox_41->setChecked(singleCabbageCount==0?false:true);
            ui->spinBox_14->setValue(singleCabbageCount);

            //消除西红柿N个
            int signleTomatoCount = levelItem->signleTomatoCount;
            ui->checkBox_40->setChecked(signleTomatoCount==0?false:true);
            ui->spinBox_13->setValue(signleTomatoCount);

            //消除玉米N个
            int singleCornCount = levelItem->singleCornCount;
            ui->checkBox_42->setChecked(singleCornCount==0?false:true);
            ui->spinBox_15->setValue(singleCornCount);


            //消除茄子N个
            int signleEggplantCount = levelItem->signleEggplantCount;
            ui->checkBox_43->setChecked(signleEggplantCount==0?false:true);
            ui->spinBox_16->setValue(signleEggplantCount);

            //消除所有的冰块


            ui->checkBox_3->setChecked(levelItem->removeAllIce);


            //消除所有的地面

            ui->checkBox_9->setChecked(levelItem->removeAllFloor);

            //消除所有蘑菇

            ui->checkBox_10->setChecked(levelItem->removeAllMushRoom);


            //消除所有的特殊类型

            ui->checkBox_11->setChecked(levelItem->removeAllSpecialType);


            //消除所有特殊胡萝卜

            ui->checkBox_12->setChecked(levelItem->removeAllCarrot);

            //消除所有特殊卷心菜

            ui->checkBox_14->setChecked(levelItem->removeAllCabbage);

            //消除所有的玉米

            ui->checkBox_25->setChecked(levelItem->removeAllCorn);

            //消除所有的茄子

            ui->checkBox_26->setChecked(levelItem->removeAllEggplant);

            //消除所有的西红柿

            ui->checkBox_13->setChecked(levelItem->removeAllTomato);

            //消除所有的特殊蔬菜
            ui->checkBox_16->setChecked(levelItem->removeAllVegetable);

            //消除所有的飘虫
            ui->checkBox_17->setChecked(levelItem->removeAllLaydBug);

            //消除所有的雪地
            ui->checkBox_18->setChecked(levelItem->removeAllSnowField);

            //星级分数
            ui->spinBox_7->setValue(levelItem->star1Score);
            ui->spinBox_6->setValue(levelItem->star2Score);
            ui->spinBox_5->setValue(levelItem->star3Score);

            qDebug()<<"star1:"<<levelItem->star1Score<<"star2:"<<levelItem->star2Score<<"star3:"<<levelItem->star3Score;

         }

        //指定类型
        ui->checkBox_15->setChecked(false);
        ui->checkBox_6->setChecked(false);
        ui->checkBox_5->setChecked(false);
        ui->checkBox_4->setChecked(false);
        ui->checkBox->setChecked(false);

        for(int i=0;i<levelItem->vecSpecialBlockType.size();++i)
        {
            int type = levelItem->vecSpecialBlockType[i];
            switch(type)
            {
            case TOOL_TOMATO:
            ui->checkBox_6->setChecked(true);
                break;
            case TOOL_CARROT:
                ui->checkBox_15->setChecked(true);
                break;
            case TOOL_CABBAGE:
            ui->checkBox_5->setChecked(true);
                break;

            case TOOL_CORN:
            ui->checkBox_4->setChecked(true);
                break;

            case TOOL_EGGPLANT:
            ui->checkBox->setChecked(true);
                break;

            }
        }


        setModal(true);
         ui->lineEdit->setText(levelItem->getName());
         //ui->pushButton->setEnabled(false);
         exec();
}
}

void NewLevelDialog::duplicateLevel(LevelTreeItem* _levelItem)
{
    if(_levelItem!=NULL)
    {

        isDuplicateLevel = true;
       // duplicateItem = _levelItem;

        //属性设置

        //胜利条件

        //步数
        int round = _levelItem->round;

        ui->radioButton_2->setChecked(round==0?false:true);
        ui->spinBox_3->setValue(round);


        //时间
        int time = _levelItem->time;

        ui->radioButton->setChecked(time==0?false:true);
        ui->spinBox_4->setValue(time);


        //指定分数

        int score = _levelItem->score;

        ui->checkBox_2->setChecked(score==0?false:true);
        ui->spinBox_9->setValue(score);


        //消除钻石数量
        int diamond = _levelItem->diamond;

        ui->checkBox_7->setChecked(diamond==0?false:true);
        ui->spinBox_10->setValue(diamond);


        //需要生成N次特殊道具数量

        int specialBonusCount = _levelItem->specialBonusCount;
        ui->checkBox_8->setChecked(specialBonusCount==0?false:true);
        ui->spinBox_11->setValue(specialBonusCount);



        //消除胡萝卜N个
        int singleCarrotCount = _levelItem->singleCarrotCount;
        ui->checkBox_39->setChecked(singleCarrotCount==0?false:true);
        ui->spinBox_12->setValue(singleCarrotCount);


        //消除卷心菜N个
        int singleCabbageCount = _levelItem->singleCabbageCount;
        ui->checkBox_41->setChecked(singleCabbageCount==0?false:true);
        ui->spinBox_14->setValue(singleCabbageCount);

        //消除西红柿N个
        int signleTomatoCount = _levelItem->signleTomatoCount;
        ui->checkBox_40->setChecked(signleTomatoCount==0?false:true);
        ui->spinBox_13->setValue(signleTomatoCount);

        //消除玉米N个
        int singleCornCount = _levelItem->singleCornCount;
        ui->checkBox_42->setChecked(singleCornCount==0?false:true);
        ui->spinBox_15->setValue(singleCornCount);


        //消除茄子N个
        int signleEggplantCount = _levelItem->signleEggplantCount;
        ui->checkBox_43->setChecked(signleEggplantCount==0?false:true);
        ui->spinBox_16->setValue(signleEggplantCount);

        //消除所有的冰块


        ui->checkBox_3->setChecked(_levelItem->removeAllIce);


        //消除所有的地面

        ui->checkBox_9->setChecked(_levelItem->removeAllFloor);

        //消除所有蘑菇

        ui->checkBox_10->setChecked(_levelItem->removeAllMushRoom);


        //消除所有的特殊类型

        ui->checkBox_11->setChecked(_levelItem->removeAllSpecialType);


        //消除所有特殊胡萝卜

        ui->checkBox_12->setChecked(_levelItem->removeAllCarrot);

        //消除所有特殊卷心菜

        ui->checkBox_14->setChecked(_levelItem->removeAllCabbage);

        //消除所有的玉米

        ui->checkBox_25->setChecked(_levelItem->removeAllCorn);

        //消除所有的茄子

        ui->checkBox_26->setChecked(_levelItem->removeAllEggplant);

        //消除所有的西红柿

        ui->checkBox_13->setChecked(_levelItem->removeAllTomato);

        //消除所有的特殊蔬菜
        ui->checkBox_16->setChecked(_levelItem->removeAllVegetable);

        //消除所有的飘虫
        ui->checkBox_17->setChecked(_levelItem->removeAllVegetable);

        //消除所有的雪地
        ui->checkBox_18->setChecked(_levelItem->removeAllVegetable);



        ui->spinBox_5->setValue(_levelItem->star1Score);
        ui->spinBox_6->setValue(_levelItem->star2Score);
        ui->spinBox_7->setValue(_levelItem->star3Score);

        setModal(true);
         ui->lineEdit->setText(getDefaultLevelName());
         exec();
    }
}

void NewLevelDialog::setSceneDelegate(GraphicsBlockScene *_scene)
{
    scene = _scene;
}

void NewLevelDialog::initCondition()
{

    //胜利条件

    //步数
    ui->radioButton_2->setChecked(false);
    ui->spinBox_3->setValue(0);


    //时间

    ui->radioButton->setChecked(false);
    ui->spinBox_4->setValue(0);


    //指定分数


    ui->checkBox_2->setChecked(false);
    ui->spinBox_9->setValue(0);


    //消除钻石数量

    ui->checkBox_7->setChecked(false);
    ui->spinBox_10->setValue(0);


    //需要生成N次特殊道具数量


    ui->checkBox_8->setChecked(false);
    ui->spinBox_11->setValue(0);



    //消除胡萝卜N个

    ui->checkBox_39->setChecked(false);
    ui->spinBox_12->setValue(0);


    //消除卷心菜N个

    ui->checkBox_41->setChecked(false);
    ui->spinBox_14->setValue(0);

    //消除西红柿N个

    ui->checkBox_40->setChecked(false);
    ui->spinBox_13->setValue(0);

    //消除玉米N个

    ui->checkBox_42->setChecked(false);
    ui->spinBox_15->setValue(0);


    //消除茄子N个

    ui->checkBox_43->setChecked(false);
    ui->spinBox_16->setValue(0);

    //消除所有的冰块


    ui->checkBox_3->setChecked(false);


    //消除所有的地面

    ui->checkBox_9->setChecked(false);

    //消除所有蘑菇

    ui->checkBox_10->setChecked(false);


    //消除所有的特殊类型

    ui->checkBox_11->setChecked(false);


    //消除所有特殊胡萝卜

    ui->checkBox_12->setChecked(false);

    //消除所有特殊卷心菜

    ui->checkBox_14->setChecked(false);

    //消除所有的玉米

    ui->checkBox_25->setChecked(false);

    //消除所有的茄子

    ui->checkBox_26->setChecked(false);

    //消除所有的西红柿

    ui->checkBox_13->setChecked(false);

    //指定类型
    ui->checkBox_15->setChecked(true);
    ui->checkBox_6->setChecked(true);
    ui->checkBox_5->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->checkBox->setChecked(true);


}

void NewLevelDialog::updateCondition(LevelTreeItem* levelTreeItem)
{
    //胜利条件

    //步数
    if(ui->radioButton_2->isChecked())
    {
       levelTreeItem->round = ui->spinBox_3->value();

        qDebug()<<"round:"<<levelTreeItem->round;
    }

    //时间
    if(ui->radioButton->isChecked())
    {
        levelTreeItem->time = ui->spinBox_4->value();
    }


    //指定分数
    if(ui->checkBox_2->isChecked())
    {
        levelTreeItem->score = ui->spinBox_9->value();

        qDebug()<<"score:"<<ui->spinBox_9->value();
    }

    //消除钻石数量
    if(ui->checkBox_7->isChecked())
    {
        levelTreeItem->diamond = ui->spinBox_10->value();
    }

    //需要生成N次特殊道具数量
    if(ui->checkBox_8->isChecked())
    {
        levelTreeItem->specialBonusCount = ui->spinBox_11->value();
    }

    //消除胡萝卜N个
    if(ui->checkBox_39->isChecked())
    {
        levelTreeItem->singleCarrotCount = ui->spinBox_12->value();
    }

    //消除卷心菜N个
    if(ui->checkBox_41->isChecked())
    {
        levelTreeItem->singleCabbageCount = ui->spinBox_14->value();
    }

    //消除西红柿N个
    if(ui->checkBox_40->isChecked())
    {
        levelTreeItem->signleTomatoCount = ui->spinBox_13->value();
    }
    //消除玉米N个
    if(ui->checkBox_42->isChecked())
    {
        levelTreeItem->singleCornCount = ui->spinBox_15->value();
    }
    //消除茄子N个
    if(ui->checkBox_43->isChecked())
    {
        levelTreeItem->signleEggplantCount = ui->spinBox_16->value();
    }
    //消除所有的冰块
    if(ui->checkBox_3->isChecked())
    {
        levelTreeItem->removeAllIce = true;
    }

    //消除所有的地面
    if(ui->checkBox_9->isChecked())
    {
        levelTreeItem->removeAllFloor = true;
    }

    //消除所有蘑菇
    if(ui->checkBox_10->isChecked())
    {
        levelTreeItem->removeAllMushRoom = true;
    }

    //消除所有的特殊类型
    if(ui->checkBox_11->isChecked())
    {
    levelTreeItem->removeAllSpecialType = true;
    }
    //消除所有特殊胡萝卜
    if(ui->checkBox_12->isChecked())
    {
        levelTreeItem->removeAllCarrot = true;
    }
    //消除所有特殊卷心菜
    if(ui->checkBox_14->isChecked())
    {
        levelTreeItem->removeAllCabbage = true;
    }
    //消除所有的玉米
    if(ui->checkBox_25->isChecked())
    {
         levelTreeItem->removeAllCorn = true;
    }
    //消除所有的茄子
    if(ui->checkBox_26->isChecked())
    {
        levelTreeItem->removeAllEggplant = true;
    }
    //消除所有的西红柿自己
    if(ui->checkBox_13->isChecked())
    {
        levelTreeItem->removeAllTomato = true;
    }

    //消除所有的特殊蔬菜
    if(ui->checkBox_16->isChecked())
    {
        levelTreeItem->removeAllVegetable = true;
    }

    //消除所有的飘虫
    if(ui->checkBox_17->isChecked())
    {
        levelTreeItem->removeAllLaydBug = true;
    }

    //消除所有的雪地
    if(ui->checkBox_18->isChecked())
    {
        levelTreeItem->removeAllSnowField = true;
    }

    //星级分数
    levelTreeItem->star1Score = ui->spinBox_7->value();
    levelTreeItem->star2Score = ui->spinBox_6->value();
    levelTreeItem->star3Score = ui->spinBox_5->value();

}

void NewLevelDialog::updateSpecialBlockType(LevelTreeItem* _levelTreeItem)
{
    if(_levelTreeItem!=NULL)
    {
        _levelTreeItem->vecSpecialBlockType.clear();

        //胡萝卜
        if(ui->checkBox_15->isChecked())
        {
            _levelTreeItem->vecSpecialBlockType.push_back(TOOL_CARROT);
        }
        //西红柿
        if(ui->checkBox_6->isChecked())
        {
           _levelTreeItem->vecSpecialBlockType.push_back(TOOL_TOMATO);
        }

        //卷心菜
        if(ui->checkBox_5->isChecked())
        {
            _levelTreeItem->vecSpecialBlockType.push_back(TOOL_CABBAGE);
        }

        //玉米
        if(ui->checkBox_4->isChecked())
        {
             _levelTreeItem->vecSpecialBlockType.push_back(TOOL_CORN);
        }

        //茄子
        if(ui->checkBox->isChecked())
        {
              _levelTreeItem->vecSpecialBlockType.push_back(TOOL_EGGPLANT);
        }
        //remove

        //debug
        for(int i=0;i<_levelTreeItem->vecSpecialBlockType.size();++i)
        {
            qDebug()<<"special block type:"<<_levelTreeItem->vecSpecialBlockType[i];
        }
    }
}

void NewLevelDialog::debug()
{


}

//void NewLevelDialog::setTreeItemsArray(QVector<LevelTreeItem *> _treeItemsArray)
//{
//    treeItemsArray = _treeItemsArray;
//}

void NewLevelDialog::on_checkBox_12_clicked()
{

}
