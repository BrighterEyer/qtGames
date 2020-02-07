#ifndef GAMECORE_H
#define GAMECORE_H

#include <QMainWindow>
#include <QPainter>
#include <myblock.h>
#include <core.h>
#include <QDialog>
#include <QMessageBox>
#include <mypushbutton.h>
#include <QTimer>
#include <stdio.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>


namespace Ui {
class GameCore;
}

class GameCore : public QMainWindow
{
    Q_OBJECT

public:
    GameCore(int num,int size,int b);
    ~GameCore();

    void Game_Graph(Graph &G);        //生成棋盘
    void map_EndState(Graph G,int B_size);  //显示最终状态
    void paintEvent(QPaintEvent *);

    int S_size;     //棋盘大小
    int B_size;     //块的大小
    int number;     //游戏编号

    QDialog *EndState;  //显示最终状态的对话框指针

    //键盘事件
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::GameCore *ui;

signals:
    void back_choosescene();    //返回选择关卡场景信号

    void up();
    void down();
    void left();
    void right();
    void win();
};

#endif // GAMECORE_H



