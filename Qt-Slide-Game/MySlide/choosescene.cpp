#include "choosescene.h"
#include <mainscene.h>
#include <QDebug>

ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    //选择关卡场景的属性设定
    this->setFixedSize(900,700);
    this->setWindowTitle("关卡选择");
    this->setWindowIcon(QIcon(":/Slide_Picture/game.png"));
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


    for(int i=1;i<=6;i++)
    {
        QString str=QString(":/Slide_Picture/level_%1.jpg").arg(i);
        MyPushButton *level=new MyPushButton(str);
        level->setParent(this);
        level->move(260+250*(i/4),220+((i-1)%3)*100);

        GameCore *gamecore=new GameCore(i-1,2+i*2,68-i*4);
        connect(gamecore,&GameCore::back_choosescene,this,[=](){
            gamecore->hide();
            this->show();
        });
        connect(level,&MyPushButton::clicked,this,[=](){
            level->Zoom1();
            level->Zoom2();
            QTimer::singleShot(500,this,[=](){
                this->hide();
                gamecore->show();
            });
        });
    }
}

void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //画背景图片
    QPixmap pix;
    pix.load(":/Slide_Picture/choosescene.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/Slide_Picture/choose_title.png");
    painter.drawPixmap(200,25,pix);
}



