#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    connect(ui->actionQuit,&QAction::triggered,[=](){
        if(QMessageBox::Yes==QMessageBox::warning(this,"退出","是否退出游戏？",QMessageBox::Yes,QMessageBox::No))
            this->close();
    });

    connect(ui->actionPlay,&QAction::triggered,[=](){
        QMessageBox *play=new QMessageBox;
        QPixmap pix;
        pix.load(":/Slide_Picture/howtoplay.JPG");
        play->setIconPixmap(pix);
        play->setWindowTitle("游戏玩法");
        play->show();
    });

    //设置主窗口属性
    this->setFixedSize(1100,700);
    this->setWindowTitle("Slide");
    this->setWindowIcon(QIcon(":/Slide_Picture/title.jpg"));

    //开始按钮的创建
    MyPushButton *start =new MyPushButton(":/Slide_Picture/start.png");
    start->setParent(this);
    start->move(this->width()*0.5-start->width()*0.5,225);

    //创建选择关卡的场景
    recordscene=new Record_Scene;
    choosescene = new ChooseScene;
    //监听选择关卡场景的返回信号
    connect(choosescene,&ChooseScene::back_mainscene,[=](){
        choosescene->hide();
        this->show();
    });
    //关卡选择场景
    connect(start,&MyPushButton::clicked,[=](){
        start->Zoom1();
        start->Zoom2();
        //延时进入
        QTimer::singleShot(400,this,[=](){
            //主场景隐藏
            this->hide();
            choosescene->show();    //进入到第二个场景
        });
    });

    //创建读取游戏按钮
    MyPushButton *record =new MyPushButton(":/Slide_Picture/record.png");
    record->setParent(this);
    record->move(this->width()*0.5-start->width()*0.5,350);

    connect(recordscene,&Record_Scene::back_mainscene,[=](){
        recordscene->hide();
        this->show();
    });
    connect(record,&MyPushButton::clicked,[=](){
        record->Zoom1();
        record->Zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            recordscene->show();    //进入到读取游戏场景
        });
    });

    //退出按钮的创建
    MyPushButton *quit =new MyPushButton(":/Slide_Picture/quit.png");
    quit->setParent(this);
    quit->move(this->width()*0.5-quit->width()*0.5,475);
    connect(quit,&MyPushButton::clicked,[=](){
        if(QMessageBox::Yes==QMessageBox::warning(this,"退出","是否退出游戏？",QMessageBox::Yes,QMessageBox::No))
            this->close();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/Slide_Picture/MainScene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/Slide_Picture/slide.png");
    painter.drawPixmap(300,0,pix);
}
