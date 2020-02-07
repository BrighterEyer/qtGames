#include "gamecore.h"
#include "ui_gamecore.h"

GameCore::GameCore(int num,int size,int b) :
    ui(new Ui::GameCore)
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

    S_size=size;
    B_size=b;
    number=num;

    //界面设计
    this->setFixedSize(1000,800);
    if(num==0)
    {
        this->setWindowTitle("入门级");
        this->setWindowIcon(QIcon(":/Slide_Picture/level_1_scene.jpg"));
    }
    else if(num==1)
    {
        this->setWindowTitle("新手级");
        this->setWindowIcon(QIcon(":/Slide_Picture/level_2_scene.jpg"));
    }
    else if(num==2)
    {
        this->setWindowTitle("精英级");
        this->setWindowIcon(QIcon(":/Slide_Picture/level_3_scene.jpg"));
    }
    else if(num==3)
    {
        this->setWindowTitle("高手级");
        // this->setWindowIcon(QIcon(":/Slide_Picture/level_4_scene.jpg"));
    }
    else if(num==4)
    {
        this->setWindowTitle("大师级");
        this->setWindowIcon(QIcon(":/Slide_Picture/level_5_scene.jpeg"));
    }
    else
    {
        this->setWindowTitle("修罗级");
        this->setWindowIcon(QIcon(":/Slide_Picture/level_6_scene.jpg"));
    }
    //返回按钮
    MyPushButton *back=new MyPushButton(":/Slide_Picture/back1.jpg",":/Slide_Picture/back2.jpg");
    back->setParent(this);
    back->move(this->width()-back->width()-20,this->height()-back->height()-20);

    connect(back,&MyPushButton::clicked,[=](){
        QTimer::singleShot(250,this,[=](){
            //关卡选择场景隐藏
            EndState->hide();
            emit this->back_choosescene();
        });
    });

    //生成棋盘

    Graph G=new Gra;
    Game_Graph(G);

    //监听移动信号
    //上
    connect(this,&GameCore::up,this,[=](){
        if(Judge_move(G,G->act,1))
        {
            Data_update(G,G->act,1,B_size);
            G->B[G->act].Mb->move(G->B[G->act].pos[0],G->B[G->act].pos[1]);
            if(Judge_End(G))
                emit this->win();
        }
    });
    //下
    connect(this,&GameCore::down,this,[=](){
        if(Judge_move(G,G->act,2))
        {
            Data_update(G,G->act,2,B_size);
            G->B[G->act].Mb->move(G->B[G->act].pos[0],G->B[G->act].pos[1]);
            if(Judge_End(G))
                emit this->win();
        }
    });
    //左
    connect(this,&GameCore::left,this,[=](){
        if(Judge_move(G,G->act,3))
        {
            Data_update(G,G->act,3,B_size);
            G->B[G->act].Mb->move(G->B[G->act].pos[0],G->B[G->act].pos[1]);
            if(Judge_End(G))
                emit this->win();
        }
    });
    //右
    connect(this,&GameCore::right,this,[=](){
        if(Judge_move(G,G->act,4))
        {
            Data_update(G,G->act,4,B_size);
            G->B[G->act].Mb->move(G->B[G->act].pos[0],G->B[G->act].pos[1]);
            if(Judge_End(G))
                emit this->win();
        }
    });

    //监听胜利信号
    connect(this,&GameCore::win,this,[=](){
        if(QMessageBox::Yes==QMessageBox::warning(this,"胜利","你赢了！是否返回？",QMessageBox::Yes,QMessageBox::No))
            emit this->back_choosescene();
        EndState->hide();    
    });

    //开始游戏按钮
    MyPushButton *start = new MyPushButton(":/Slide_Picture/start.png");
    start->setParent(this);
    start->move(this->width()*0.5-start->width()*0.5,this->height()*0.5-start->height()*0.5);
    connect(start,&MyPushButton::clicked,this,[=](){
        start->hide();
        EndState->show();
    });

    //显示终态按钮
    MyPushButton *see_End = new MyPushButton(":/Slide_Picture/seetheend.png");
    see_End->setParent(this);
    see_End->move(800,this->height()*0.5-see_End->height()*0.5);

    connect(see_End,&MyPushButton::clicked,this,[=](){
        EndState->show();
    });
}

void GameCore::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString str[6],srt[6];
    str[0]=":/Slide_Picture/level_1_scene.jpg";
    str[1]=":/Slide_Picture/level_2_scene.jpg";
    str[2]=":/Slide_Picture/level_3_scene.jpg";
    str[3]=":/Slide_Picture/level_4_scene.jpg";
    str[4]=":/Slide_Picture/level_5_scene.jpeg";
    str[5]=":/Slide_Picture/level_6_scene.jpg";
    //画背景图片
    QPixmap pix;
    pix.load(str[number]);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    srt[0]=":/Slide_Picture/grid_1.jpg";
    srt[1]=":/Slide_Picture/grid_2.JPG";
    srt[2]=":/Slide_Picture/grid_3.JPG";
    srt[3]=":/Slide_Picture/grid_4.jpg";
    srt[4]=":/Slide_Picture/grid_5.jpg";
    srt[5]=":/Slide_Picture/grid_6.jpg";
    pix.scaled(B_size,B_size);
    pix.load(srt[number]);

    int i,j,x,y;
    x=this->width()*0.5-pix.width()*(S_size/2);
    y=this->height()*0.5-pix.height()*(S_size/2);
    for(i=0;i<S_size;i++)
    {
        for(j=0;j<S_size;j++)
            painter.drawPixmap(x+i*B_size,y+50+j*B_size,pix);
    }
    //画网格线
    for(i=0;i<=S_size;i++)
        painter.drawLine(x+i*B_size,y+50,x+i*B_size,y+50+B_size*S_size);
    for(i=0;i<=S_size;i++)
        painter.drawLine(x,y+50+i*B_size,x+B_size*S_size,y+50+i*B_size);
}

void GameCore::Game_Graph(Graph &G)
{
    InitGraph(G,S_size+2);    //初始化棋盘图
    CreateGraph(G,S_size,B_size);         //生成棋盘
    map_EndState(G,B_size);
    TransGraph(G,B_size);          //生成初态
    map_block(this,G,B_size,S_size);      //贴块
    for(int i=0;i<G->num;i++)
    {
        connect(G->B[i].Mb,&MyBlock::clicked,this,[=](){
            G->B[i].Mb->Zoom1();
            G->B[i].Mb->Zoom2();
            G->act=i;
        });
    }
}

void GameCore::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
        emit this->up();
    if(event->key() == Qt::Key_Down)
        emit this->down();
    if(event->key() == Qt::Key_Left)
        emit this->left();
    if(event->key() == Qt::Key_Right)
        emit this->right();
    QMainWindow::keyReleaseEvent(event);
}

void GameCore::map_EndState(Graph G,int B_size)
{
    EndState=new QDialog(this);
    EndState->setWindowTitle("最终状态");
    EndState->setFixedSize(S_size*B_size,S_size*B_size);
    int i;
    for(i=0;i<G->num;i++)
    {
        G->B[i].Mb=new MyBlock(G->B[i].size,G->B[i].rect,B_size);
        G->B[i].Mb->setParent(EndState);
        G->B[i].Mb->move((G->B[i].locate[0]-1)*B_size,(G->B[i].locate[1]-1)*B_size);
    }
}

GameCore::~GameCore()
{
    delete ui;
}

