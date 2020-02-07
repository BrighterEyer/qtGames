#include "myblock.h"


MyBlock::MyBlock(int num,int m,int size)//num:块号，m:针对1*2大小的块的方向,size:块的大小(边长)
{
    QString str1=":/Slide_Picture/block_1_64.png";
    QString str2=":/Slide_Picture/block_22_64.png";
    QString str3=":/Slide_Picture/block_21_64.png";
    QString str4=":/Slide_Picture/block_3_64.png";

    QString ImgPath;

    QPixmap pix;

    switch(num)
    {
    case 1:
        ImgPath=str1;
        break;
    case 2:
        if(m==0)
            ImgPath=str2;
        else
            ImgPath=str3;
        break;
    case 4:
        ImgPath=str4;
        break;
    }
    bool ret=pix.load(ImgPath);
    if(!ret)
    {
        QString str=QString("%1 图片加载失败").arg(ImgPath);
        QMessageBox box(this);
        box.setText(str);
        box.exec();
        return;
    }
    if(num==1)
    {
        this->setFixedSize(size,size);
        this->setStyleSheet("QPushButton{border:0px;}");
        pix.scaled(size,size);
        this->setIcon(pix);
        this->setIconSize(QSize(size,size));
    }
    else if(num==2)
    {
        if(m==0)
        {
            this->setFixedSize(size,2*size);
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pix);
            this->setIconSize(QSize(size,2*size));
        }
        else
        {
            this->setFixedSize(2*size,size);
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pix);
            this->setIconSize(QSize(2*size,size));
        }
    }
    else
    {
        this->setFixedSize(2*size,2*size);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(2*size,2*size));
    }
}
void MyBlock::Zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动画结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y()+2,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyBlock::Zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动画结束位置
    animation->setStartValue(QRect(this->x(),this->y()+2,this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}



