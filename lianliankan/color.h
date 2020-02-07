#ifndef COLOR_H
#define COLOR_H
#include<QColor>
class MyColor{
    //Q_OBJECT
    QColor* qcr;//颜色
    int num;//标记此类颜色被使用次数
    public:
    MyColor(int r, int g, int b);
    MyColor(const QColor& clor);
    ~MyColor();
    MyColor(const MyColor& col);
    MyColor& operator = (const MyColor& col);
    void numAdd();//被使用一次，计数加1
    void numTrac();//计数清0
    int getNum();//获取计数 
    QColor* getPt();//获取颜色类对象指针
};
#endif // MYTHREAD_H
