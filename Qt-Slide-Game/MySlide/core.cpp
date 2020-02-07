#include "core.h"

void InitGraph(Graph &G,int size)
{
    int i,j;
    G->size=size;					//大小，外加一层围墙
    G->num=0;						//块的个数初始为0，同时也为块的标号
    G->B=(Blo)malloc(sizeof(Block));	//块的信息，初始化一个
    G->Begin_State=(int **)malloc(sizeof(int *)*size);	//块的初始状态矩阵
    G->End_State=(int **)malloc(sizeof(int *)*size);		//块的结束状态矩阵
    for(i=0;i<size;i++)				//分配空间
    {
        G->Begin_State[i]=(int *)malloc(sizeof(int)*size);
        G->End_State[i]=(int *)malloc(sizeof(int)*size);
    }

    for(i=0;i<size;i++)				//初始化
    {
        G->Begin_State[0][i]=-1;
        G->Begin_State[size-1][i]=-1;
        G->Begin_State[i][0]=-1;
        G->Begin_State[i][size-1]=-1;
        G->End_State[0][i]=-1;
        G->End_State[size-1][i]=-1;
        G->End_State[i][0]=-1;
        G->End_State[i][size-1]=-1;
    }
    for(i=1;i<size-1;i++)
    {
        for(j=1;j<size-1;j++)
        {
            G->Begin_State[i][j]=0;
            G->End_State[i][j]=0;
        }
    }
    G->End_State[G->size-3][G->size-3]=-1;
    G->End_State[G->size-2][G->size-3]=-1;
    G->End_State[G->size-3][G->size-2]=-1;
    G->End_State[G->size-2][G->size-2]=-1;
}

void CreateGraph(Graph &G,int S_size,int B_size)//终态
{
    int num,x,y;
    int s_i,s_j;
    int i1,i2,i3,j1,j2,j3;
    srand(time(NULL));
    Block *t;
    for(x=1;x<G->size-1;x++)
    {
        for(y=1;y<G->size-1;y++)
        {
            if(G->End_State[x][y]==0)
            {
                num=rand()%3+1;             //随机生成一种块
                switch(num)
                {
                    case 1:					//将大小为1的块安置
                        G->B[G->num].size=1;    //块的大小
                        G->B[G->num].locate[0]=y;   //块在图上的位置
                        G->B[G->num].locate[1]=x;
                        G->B[G->num].rect=0;    //对于1*2的块记录形状
                        Calculation_pos(G,G->num,S_size,B_size);    //计算块在实际棋盘上的位置
                        G->num++;
                        G->End_State[x][y]=G->num;
                        t=(Blo)realloc(G->B,sizeof(Block)*(G->num+1));
                        G->B=t;
                        break;
                    case 2:					//将大小为2的块安置
                    if(G->End_State[x][y+1]==0)
                    {
                        s_i=x;	s_j=y+1;
                        G->B[G->num].rect=1;  //水平
                    }
                    else if(G->End_State[x+1][y]==0)
                    {
                        s_i=x+1;	s_j=y;
                        G->B[G->num].rect=0;  //垂直
                    }
                    else
                    {
                        y--;
                        break;
                    }
                    G->B[G->num].size=2;
                    G->B[G->num].locate[0]=y;
                    G->B[G->num].locate[1]=x;
                    Calculation_pos(G,G->num,S_size,B_size);
                    G->num++;
                    t=(Blo)realloc(G->B,sizeof(Block)*(G->num+1));
                    G->B=t;
                    G->End_State[x][y]=G->num;
                    G->End_State[s_i][s_j]=G->num;
                    break;
                    case 3:					//将大小为4的块安置
                    if(G->End_State[x][y+1]==0&&G->End_State[x+1][y+1]==0&&G->End_State[x+1][y]==0)
                    {
                        i1=x;     j1=y+1;
                        i2=x+1;   j2=y+1;
                        i3=x+1;   j3=y;
                    }
                    else
                    {
                        y--;
                        break;
                    }
                    G->B[G->num].size=4;
                    G->B[G->num].locate[0]=y;
                    G->B[G->num].locate[1]=x;
                    Calculation_pos(G,G->num,S_size,B_size);
                    G->num++;
                    t=(Blo)realloc(G->B,sizeof(Block)*(G->num+1));
                    G->B=t;
                    G->End_State[x][y]=G->num;
                    G->End_State[i1][j1]=G->num;
                    G->End_State[i2][j2]=G->num;
                    G->End_State[i3][j3]=G->num;
                    break;
                }
            }
        }
    }
    G->End_State[G->size-3][G->size-3]=0;
    G->End_State[G->size-2][G->size-3]=0;
    G->End_State[G->size-3][G->size-2]=0;
    G->End_State[G->size-2][G->size-2]=0;
    for(int i=0;i<G->size;i++)
        for(int j=0;j<G->size;j++)
            G->Begin_State[i][j]=G->End_State[i][j];
}

void map_block(QMainWindow *parent,Graph &G,int B_size,int S_size)
{
    int i;
    for(i=0;i<G->num;i++)
    {
        G->B[i].Mb=new MyBlock(G->B[i].size,G->B[i].rect,B_size);
        G->B[i].Mb->setParent(parent);
        G->B[i].Mb->move(parent->width()*0.5-B_size*(S_size/2)+(G->B[i].locate[0]-1)*B_size,parent->height()*0.5-B_size*(S_size/2)+(G->B[i].locate[1]-1)*B_size+50);
    }
}

void Calculation_pos(Graph &G,int num,int S_size,int B_size)
{
    G->B[num].pos[0]=500-B_size*(S_size/2)+(G->B[num].locate[0]-1)*B_size;
    G->B[num].pos[1]=400-B_size*(S_size/2)+(G->B[num].locate[1]-1)*B_size+50;
}

void TransGraph(Graph G,int B_size)
{
    int dir,i,j,k;
    srand(time(NULL));
    for(i=0;i<10000;i++)
    {
        for(j=G->num-1;j>=0;j--)
        {
            for(k=G->num-1;k>=0;k--)
            {
                dir=rand()%4+1;    //随机产生一个移动方向
                if(Judge_move(G,j,dir)) //判断是否能够移动
                    Data_update(G,j,dir,B_size);
            }
        }
    }
}

void Data_update(Graph G,int num,int direction,int B_size)
{
    //图信息的更新

    if(G->B[num].size==1)
    {
        switch(direction)
        {
        case 1:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]]=num+1;
            break;
        case 2:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=num+1;
            break;
        case 3:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1]=num+1;
            break;
        case 4:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=num+1;
            break;
        }
    }
    else if(G->B[num].size==2)
    {
        if(G->B[num].rect==0)
        {
            switch(direction)
            {
            case 1:
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]]=num+1;
                break;
            case 2:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]]=num+1;
                break;
            case 3:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1]=num+1;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]-1]=num+1;
                break;
            case 4:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=num+1;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1]=num+1;
                break;
            }
        }
        else
        {
            switch(direction)
            {
            case 1:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=0;
                G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]]=num+1;
                G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]+1]=num+1;
                break;
            case 2:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=0;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=num+1;
                G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1]=num+1;
                break;
            case 3:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1]=num+1;
                break;
            case 4:
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
                G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+2]=num+1;
                break;
            }
        }
    }
    else
    {
        switch(direction)
        {
        case 1:
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1]=0;
            G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]]=num+1;
            G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]+1]=num+1;
            break;
        case 2:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=0;
            G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]]=num+1;
            G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]+1]=num+1;
            break;
        case 3:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1]=0;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1]=0;
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1]=num+1;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]-1]=num+1;
            break;
        case 4:
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]]=0;
            G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+2]=num+1;
            G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+2]=num+1;
            break;
        }
    }
    //块信息的更新
    switch(direction)
    {
    case 1:
        G->B[num].locate[1]--;
        G->B[num].pos[1]=G->B[num].pos[1]-B_size;
        break;
    case 2:
        G->B[num].locate[1]++;
        G->B[num].pos[1]=G->B[num].pos[1]+B_size;
        break;
    case 3:
        G->B[num].locate[0]--;
        G->B[num].pos[0]=G->B[num].pos[0]-B_size;
        break;
    case 4:
        G->B[num].locate[0]++;
        G->B[num].pos[0]=G->B[num].pos[0]+B_size;
        break;
    }
}

bool Judge_move(Graph G,int num,int direction)
{

    if(G->B[num].size==1)
    {
        switch(direction)
        {
        case 1:
            if((G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]])==0)
                return true;
            break;
        case 2:
            if((G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]])==0)
                return true;
            break;
        case 3:
            if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1])==0)
                return true;
            break;
        case 4:
            if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1])==0)
                return true;
            break;
        }
    }
    else if(G->B[num].size==2)
    {
        if(G->B[num].rect==0)
        {
            switch(direction)
            {
            case 1:
                if((G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]])==0)
                    return true;
                break;
            case 2:
                if((G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]])==0)
                    return true;
                break;
            case 3:
                if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1])==0&&(G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]-1])==0)
                    return true;
                break;
            case 4:
                if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+1])==0&&(G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1])==0)
                    return true;
                break;
            }
        }
        else
        {
            switch(direction)
            {
            case 1:
                if((G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]])==0&&(G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]+1])==0)
                    return true;
                break;
            case 2:
                if((G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]])==0&&(G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+1])==0)
                    return true;
                break;
            case 3:
                if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1])==0)
                    return true;
                break;
            case 4:
                if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+2])==0)
                    return true;
                break;
            }
        }
    }
    else
    {
        switch(direction)
        {
        case 1:
            if((G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]])==0&&(G->Begin_State[G->B[num].locate[1]-1][G->B[num].locate[0]+1])==0)
                return true;
            break;
        case 2:
            if((G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]])==0&&(G->Begin_State[G->B[num].locate[1]+2][G->B[num].locate[0]+1])==0)
                return true;
            break;
        case 3:
            if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]-1])==0&&(G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]-1])==0)
                return true;
            break;
        case 4:
            if((G->Begin_State[G->B[num].locate[1]][G->B[num].locate[0]+2])==0&&(G->Begin_State[G->B[num].locate[1]+1][G->B[num].locate[0]+2])==0)
                return true;
            break;
        }
    }
    return false;
}
bool Judge_End(Graph G)
{
    int i,n,n2,n4,n24;
    for(i=0;i<G->num;i++)
    {
        n=G->End_State[G->B[i].locate[1]][G->B[i].locate[0]]-1;
        n2=G->End_State[G->B[i].locate[1]+1][G->B[i].locate[0]]-1;
        n4=G->End_State[G->B[i].locate[1]][G->B[i].locate[0]+1]-1;
        n24=G->End_State[G->B[i].locate[1]+1][G->B[i].locate[0]+1]-1;   //右下
        switch(G->B[i].size)
        {
        case 1:
            if(G->B[n].size!=1) //对于大小为1的块只需大小相同即可
                return false;
            break;
        case 2:                 //对于大小为2的块
            if(G->B[i].rect==0) //垂直
            {
                if(G->B[n].size!=2||n2!=n)
                    return false;
            }
            else
            {
                if(G->B[n].size!=2||n4!=n)
                    return false;
            }
            break;
        case 4:
            if(G->B[n].size!=4||n!=n4||n!=n2||n!=n24)
                return false;
            break;
        }
    }
    return true;
}
