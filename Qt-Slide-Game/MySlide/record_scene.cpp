#include "record_scene.h"
#include "ui_record_scene.h"

#include <QTimer>
#include <QDebug>
#include <gamecore.h>
Record_Scene::Record_Scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Record_Scene)
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

    //读取游戏场景的属性设定
    this->setFixedSize(1000,700);
    this->setWindowTitle("读取游戏");
    this->setWindowIcon(QIcon(":/Slide_Picture/record_title.png"));

    //返回按钮
    MyPushButton *back=new MyPushButton(":/Slide_Picture/back1.jpg",":/Slide_Picture/back2.jpg");
    back->setParent(this);
    back->move(this->width()-back->width()-20,this->height()-back->height()-20);


    connect(back,&MyPushButton::clicked,[=](){
        QTimer::singleShot(250,this,[=](){
            //关卡选择场景隐藏
            emit this->back_mainscene();
        });
    });

    connect(ui->pushButton_1,&QPushButton::clicked,[=](){
        qDebug()<<"读取第一条记录"<<endl;
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        qDebug()<<"读取第二条记录"<<endl;
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        qDebug()<<"读取第三条记录"<<endl;
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        qDebug()<<"读取第四条记录"<<endl;
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=](){
        qDebug()<<"读取第五条记录"<<endl;
    });
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        qDebug()<<"读取第六条记录"<<endl;
    });
    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        qDebug()<<"读取第七条记录"<<endl;
    });


}

Record_Scene::~Record_Scene()
{
    delete ui;
}

void Record_Scene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/Slide_Picture/record_scene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

