#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //保存住正常显示路径和选中后显示的路径
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(this->normalImgPath);
    if(!ret)
    {
        QString str=QString("%1 图片加载失败").arg(this->normalImgPath);
        QMessageBox box(this);
        box.setText(str);
        box.exec();
        return;
    }
    //设置按钮大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButton::Zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动画结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::Zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置动画结束位置
    animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//传入选中后的图片路径不为空
    {
        QPixmap pix;
        bool ret=pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //其他的事情交给父类处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//传入选中后的图片路径不为空
    {
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::mouseReleaseEvent(e);
}
