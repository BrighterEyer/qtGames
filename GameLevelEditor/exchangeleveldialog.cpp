#include "exchangeleveldialog.h"
#include "ui_exchangeleveldialog.h"

#include "leveltreeitem.h"

#include "mainwindow.h"


//关卡信息
struct LevelInfo{

    int index;
    QString strName;

};

ExchangeLevelDialog::ExchangeLevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeLevelDialog)
{

    setWindowTitle("Exchange Level");
    ui->setupUi(this);
}

ExchangeLevelDialog::~ExchangeLevelDialog()
{
    delete ui;
}

void ExchangeLevelDialog::on_pushButton_2_clicked()
{
    close();
}

void ExchangeLevelDialog::exchangeLevel()
{
    setModal(true);

    //当前关卡名称
    LevelTreeItem* levelItem = (LevelTreeItem*)MainWindow::sharedInstance()->treeWidget->currentItem();
    QString levelName = levelItem->getName();


    qDebug()<<"levelName:"<<levelName;

    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(levelName);
    ui->comboBox_2->setEnabled(false);

    //添加待交换列表
    //ui->comboBox->current
    int treeItemCount = MainWindow::sharedInstance()->treeItemsArray.size();
    ui->comboBox->clear();
    for(int i=0;i<treeItemCount;++i)
    {

        LevelTreeItem* levelItem = (LevelTreeItem*)MainWindow::sharedInstance()->treeItemsArray[i];



        if(levelItem->getName()!=levelName)
        {
            ui->comboBox->addItem(levelItem->getName());
        }

    }
     exec();
}

void ExchangeLevelDialog::on_pushButton_clicked()
{
    QString currentText = ui->comboBox->currentText();

    int treeItemCount = MainWindow::sharedInstance()->treeItemsArray.size();

    qDebug()<<"ExchangeLevelDialog:currentText:"<<currentText;

   //当前关卡
    LevelTreeItem *curLevelItem = NULL;

   //等交换关卡

    for(int i=0;i<treeItemCount;++i)
    {
        LevelTreeItem* levelItem = (LevelTreeItem*)MainWindow::sharedInstance()->treeItemsArray[i];
         if(levelItem->getName()==ui->comboBox_2->currentText())
         {
               curLevelItem = levelItem;

               qDebug()<<"赋值当前关卡!!!";
         }
    }
    for(int i=0;i<treeItemCount;++i)
    {

        LevelTreeItem* levelItem = (LevelTreeItem*)MainWindow::sharedInstance()->treeItemsArray[i];

        qDebug()<<"search file name:"<<levelItem->getName();

//        qDebug()<<"current fileName:"<<ui->comboBox_2->currentText();

//        if(levelItem->getName()==ui->comboBox_2->currentText())
//        {
//            curLevelItem = levelItem;
//            qDebug()<<"当前关卡:"<<curLevelItem->getName();

//        }
        if(levelItem->getName()==currentText&&curLevelItem!=NULL)
        {
           //关卡交换
            qDebug()<<"交换关卡:"<<curLevelItem->getName();


            //交换行列
            int tmpRow = curLevelItem->getRow();
            int tmpColumn = curLevelItem->getColumn();


            //保存当前关卡的数据
            levelTreeItemsArray.clear();

            for(int i=0;i<curLevelItem->getRow();++i)
                {
                for(int j=0;j<curLevelItem->getColumn();++j)
                {
                    int id = i*curLevelItem->getColumn()+j;

                    GraphicsBlockItem *item = (GraphicsBlockItem*)curLevelItem->blockItemArray[id];


                    GraphicsBlockItem *newItem = new GraphicsBlockItem();
                    newItem->setIndex(id);
                    newItem->setPos(j*newItem->width(),i*newItem->height());
                    newItem->initDefaultPosition(j*newItem->width(),i*newItem->height());
                    newItem->setGroundFrame(item->getGroundType());

                    newItem->setGroundLayer(item->getGroundLayer());

                    newItem->setBlockItem(item->getBlockType());
                    newItem->setLockInFlag(item->isLockIn());

                    levelTreeItemsArray.push_back(newItem);


                }
            }

            //保存关卡属性
            int tmpRound = curLevelItem->round;
            int tmpTime = curLevelItem->time;

            QVector<int> tmpVecSpecialBlockType;

            for(int i=0;i<curLevelItem->vecSpecialBlockType.size();++i)
            {
                int blockType = curLevelItem->vecSpecialBlockType[i];
                tmpVecSpecialBlockType.push_back(blockType);
            }
            //指定分数
            int tmpScore = curLevelItem->score;
            //钻石 数量
            int tmpDiamond = curLevelItem->diamond;
            //N次生成特殊道具
            int tmpSpecialBonusCount = curLevelItem->specialBonusCount;

            //消除胡萝卜N个
            int tmpSingleCarrotCount = curLevelItem->singleCarrotCount;

            //消除卷心菜N个

            int tmpsingleCabbageCount = curLevelItem->singleCabbageCount;


            //消除西红柿N个
            int tmpsignleTomatoCount = curLevelItem->signleTomatoCount;

            //消除玉米N个
            int tmpsingleCornCount = curLevelItem->singleCornCount;

            //消除茄子N个
            int tmpsignleEggplantCount = curLevelItem->signleEggplantCount;

            //消除所有的冰块
            bool tmpremoveAllIce = curLevelItem->removeAllIce;


            //消除所有的地面
            bool tmpremoveAllFloor = curLevelItem->removeAllFloor;

            //消除所有的蘑菇
            bool tmpremoveAllMushRoom = curLevelItem->removeAllMushRoom;
            //消除所有的特殊类型
            bool tmpremoveAllSpecialType = curLevelItem->removeAllSpecialType;
            //消除所有特殊胡萝卜
            bool tmpremoveAllCarrot = curLevelItem->removeAllCarrot;

            //消除所有特殊卷心菜
            bool tmpremoveAllCabbage = curLevelItem->removeAllCabbage;

            //消除所有的玉米
            bool tmpremoveAllCorn = curLevelItem->removeAllCorn;

            //消除所有的茄子
            bool tmpremoveAllEggplant = curLevelItem->removeAllEggplant;

            //消除所有的西红柿
            bool tmpremoveAllTomato = curLevelItem->removeAllTomato;

            //消除所有的特殊蔬菜
            bool tmpremoveAllVegetable = curLevelItem->removeAllVegetable;

            //消除所有的飘虫
            bool tmprevemoAllLadyBug = curLevelItem->removeAllLaydBug;

            //消除所有的雪地
            bool tmpremoveAllSnowField = curLevelItem->removeAllSnowField;

            //星级分数
            int tmpStar1Score = curLevelItem->star1Score;
            int tmpStar2Score = curLevelItem->star2Score;
            int tmpStar3Score = curLevelItem->star3Score;

            //开始交换属性

            curLevelItem->round = levelItem->round;
            curLevelItem->time = levelItem->time;
            curLevelItem->score = levelItem->score;
            curLevelItem->diamond = levelItem->diamond;
            curLevelItem->specialBonusCount = levelItem->specialBonusCount;
            curLevelItem->singleCarrotCount = levelItem->singleCarrotCount;
            curLevelItem->singleCabbageCount = levelItem->singleCabbageCount;
            curLevelItem->signleTomatoCount = levelItem->signleTomatoCount;

            curLevelItem->singleCornCount = levelItem->singleCornCount;
            curLevelItem->signleEggplantCount = levelItem->signleEggplantCount;

            curLevelItem->removeAllIce = levelItem->removeAllIce;
            curLevelItem->removeAllFloor = levelItem->removeAllFloor;
            curLevelItem->removeAllMushRoom = levelItem->removeAllMushRoom;
            curLevelItem->removeAllSpecialType = levelItem->removeAllSpecialType;
            curLevelItem->removeAllCarrot = levelItem->removeAllCarrot;
            curLevelItem->removeAllCabbage = levelItem->removeAllCabbage;
            curLevelItem->removeAllCorn = levelItem->removeAllCorn;
            curLevelItem->removeAllEggplant = levelItem->removeAllEggplant;
            curLevelItem->removeAllTomato = levelItem->removeAllTomato;
            curLevelItem->removeAllVegetable = levelItem->removeAllVegetable;
            curLevelItem->removeAllLaydBug = levelItem->removeAllLaydBug;
            curLevelItem->removeAllSnowField = levelItem->removeAllSnowField;

            curLevelItem->star1Score = levelItem->star1Score;
            curLevelItem->star2Score = levelItem->star2Score;
            curLevelItem->star3Score = levelItem->star3Score;

            levelItem->round = tmpRound;
            levelItem->time = tmpTime;
            levelItem->score = tmpScore;
            levelItem->diamond = tmpDiamond;
            levelItem->specialBonusCount = tmpSpecialBonusCount;
            levelItem->singleCarrotCount = tmpSingleCarrotCount;
            levelItem->singleCabbageCount = tmpsingleCabbageCount;
            levelItem->signleTomatoCount = tmpsignleTomatoCount;
            levelItem->singleCornCount = tmpsingleCornCount;
            levelItem->signleEggplantCount = tmpsignleEggplantCount;

            levelItem->removeAllIce = tmpremoveAllIce;
            levelItem->removeAllFloor = tmpremoveAllFloor;
            levelItem->removeAllMushRoom = tmpremoveAllMushRoom;
            levelItem->removeAllSpecialType = tmpremoveAllSpecialType;
            levelItem->removeAllCarrot = tmpremoveAllCarrot;
            levelItem->removeAllCabbage = tmpremoveAllCabbage;
            levelItem->removeAllCorn = tmpremoveAllCorn;
            levelItem->removeAllEggplant = tmpremoveAllEggplant;
            levelItem->removeAllTomato = tmpremoveAllTomato;
            levelItem->removeAllVegetable = tmpremoveAllVegetable;
            levelItem->removeAllLaydBug = tmprevemoAllLadyBug;
            levelItem->removeAllSnowField = tmpremoveAllSnowField;

            levelItem->star1Score = tmpStar1Score;
            levelItem->star2Score = tmpStar2Score;
            levelItem->star3Score = tmpStar3Score;


            //开始交换
            curLevelItem->setRow(levelItem->getRow());
            curLevelItem->setColumn(levelItem->getColumn());

            levelItem->setRow(tmpRow);
            levelItem->setColumn(tmpColumn);



            //设置当前关卡数据
            curLevelItem->blockItemArray.clear();

            for(int i=0;i<curLevelItem->getRow();++i)
                {
                for(int j=0;j<curLevelItem->getColumn();++j)
                {
                    int id = i*curLevelItem->getColumn()+j;

                    GraphicsBlockItem *item = (GraphicsBlockItem*)levelItem->blockItemArray[id];


                    GraphicsBlockItem *newItem = new GraphicsBlockItem();
                    newItem->setIndex(id);
                    newItem->setPos(j*newItem->width(),i*newItem->height());
                    newItem->initDefaultPosition(j*newItem->width(),i*newItem->height());
                    newItem->setGroundFrame(item->getGroundType());

                    newItem->setGroundLayer(item->getGroundLayer());

                    newItem->setBlockItem(item->getBlockType());
                    newItem->setLockInFlag(item->isLockIn());

                    curLevelItem->blockItemArray.push_back(newItem);


                }
            }

            //设置待交换关卡数据
            levelItem->blockItemArray.clear();

            for(int i=0;i<levelItem->getRow();++i)
                {
                for(int j=0;j<levelItem->getColumn();++j)
                {
                    int id = i*levelItem->getColumn()+j;

                    GraphicsBlockItem *item = (GraphicsBlockItem*)levelTreeItemsArray[id];


                    GraphicsBlockItem *newItem = new GraphicsBlockItem();
                    newItem->setIndex(id);
                    newItem->setPos(j*newItem->width(),i*newItem->height());
                    newItem->initDefaultPosition(j*newItem->width(),i*newItem->height());
                    newItem->setGroundFrame(item->getGroundType());

                    newItem->setGroundLayer(item->getGroundLayer());

                    newItem->setBlockItem(item->getBlockType());
                    newItem->setLockInFlag(item->isLockIn());

                    levelItem->blockItemArray.push_back(newItem);


                }

            }
        }
    }

    MainWindow::sharedInstance()->treeWidget->doubleClickItem(curLevelItem);
   // curLevelItem->setSelected(true);

    close();

}
