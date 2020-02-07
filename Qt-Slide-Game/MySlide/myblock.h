#ifndef MYBLOCK_H
#define MYBLOCK_H

#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>

class MyBlock : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyBlock(QWidget *parent = 0);
    MyBlock(int num,int m,int size);

    //向下跳跃
    void Zoom1();
    //向上跳跃
    void Zoom2();

signals:

public slots:
};

#endif // MYBLOCK_H
