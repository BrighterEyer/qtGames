#ifndef CORE_H
#define CORE_H

#include <myblock.h>
#include <QMainWindow>
#include <QWidget>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <stdio.h>

class MyBlock;

typedef struct
{
    int size;   //块的大小：1,2,4
    int locate[2];   //块在矩阵中位置，统一为右上角
    int pos[2];      //块在图画上的位置
    MyBlock *Mb;
    int rect;   //对正方形无用，但是对长方形而言，0为垂直方向，1为水平方向
}Block,*Blo;

typedef struct
{
    int size;   //棋盘图的size*size规模大小
    int **Begin_State;  //游戏开始时的状态
    int **End_State;    //游戏最终要达到的状态
    int num;    //块的个数
    Block *B;   //每个块的信息
    int act;    //记录下激活的块号
}*Graph,Gra;


void InitGraph(Graph &G,int size);//初始化分配空间
void CreateGraph(Graph &G,int S_size,int B_size);  //生成随机矩阵(最终状态)
void map_block(QMainWindow *parent,Graph &G,int B_size,int S_size); //贴图
//num：要计算位置的块号；
//pos：块在矩阵中的位置
//S_size：棋盘大小S_size*S_size
//B_size：块的大小B_size*B_size
void Calculation_pos(Graph &G,int num,int S_size,int B_size);   //计算块在图中的位置
void TransGraph(Graph G,int B_size);    //生成随机矩阵(初始状态)
void Data_update(Graph G,int num,int direction,int B_size);//移动后图的数据更新
bool Judge_move(Graph G,int num,int direction); //判断是否能够移动
bool Judge_End(Graph G);    //判断是否移动到了最终状态

#endif // CORE_H
