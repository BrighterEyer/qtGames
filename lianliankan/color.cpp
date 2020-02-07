#include"color.h"

MyColor::MyColor(int r = 0, int g = 0, int b = 0):qcr(new QColor(r,g,b)),num(0)
{
}

MyColor::MyColor(const QColor &clor):qcr(new QColor(clor)), num(0)
{
}

MyColor::~MyColor()
{
    delete qcr;
}

MyColor::MyColor(const MyColor &col)
{
    qcr = new QColor(col.qcr->red(), col.qcr->green(), col.qcr->green());
    num = col.num;
}

MyColor &MyColor::operator =(const MyColor &col)
{
    qcr = new QColor(col.qcr->red(), col.qcr->green(), col.qcr->green());
    num = col.num;
    return *this;
}

void MyColor::numAdd()
{
    ++num;
}

void MyColor::numTrac()
{
    num = 0;
}

int MyColor::getNum()
{
    return num; 
}

QColor *MyColor::getPt()
{
    return qcr;
}
