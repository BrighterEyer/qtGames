#ifndef LOOK_H
#define LOOK_H
#include<QPushButton>
#include<QLabel>
#include<QRect>
#include<QDialog>
#include<QVector>
#include<QLine>
#include<QPoint>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include<QSound>
#include<QMessageBox>
#include<QString>
#include<QTextCodec>
#include<iostream>
#include<stdio.h>
#include"color.h"
#include"integer.h"
using namespace std;
#define LEN 30
class Look : public QDialog{
    Q_OBJECT
    QVector<QRect*> vec;//矩形方块向量
    QVector<MyColor*> clr;//颜色向量
    QVector<Integer*> ran;//保存Mycolor向量的下标
    QVector<Integer*> use;//保存QRect向量将要填充颜色的下标
    QVector<int> paint;//保存被隐藏的QRect的向量下标
    QLine* qln[3];//消除线数组
    QRect* first;//鼠标点击的两个方块之一
    QRect* next;//鼠标点击的两个方块之一
    QTimer* tm;//调用paintEvent函数
    QTimer* tm1;//调用自定义槽函数
    QLabel* qpb;//计分器
    QPushButton* sur;//认输
    QPushButton* prompt;//提示可行路线
    int score;//得分
    int count;//矩形方块选择标识
    int catchNum;//对关卡计数
    int cth[3];//关卡重置数组
    bool isPaint;//判定是否消除
    bool confirm;//提示状态
public:
    Look();
    ~Look();
    void mousePressEvent(QMouseEvent *e);//鼠标点击事件
    bool paintOrNot(int);//矩形方块是否显示
    void buttonRemove();//测试函数
    void paintEvent (QPaintEvent* );//绘图事件
    bool allCheck(QRect* rec1, QRect* rec2);//检查是否消除
    bool oneLineCheck(QRect* rec1, QRect* rec2);//单线消除算法
    bool twoLineCheck(QRect* rec1, QRect* rec2);//双线消除算法
    bool threeLineCheck(QRect* rec1, QRect* rec2);//三线消除算法
    bool specialCheck(QRect* rec1, QRect* rec2);//特殊消除算法
    bool checkSlotB(int, int);//二次检查

public slots:
    bool checkSlot();//根据方块状态进行的行为操作
    void checkCall();//判定方块状态
    void callBack();//初始化界面
    void surrender();//投降
    void requestHelp();//提示最便捷的可消除路线
public : signals:
    void sig();
};
#endif // LOOK_H
