#include"integer.h"
Integer::Integer(int it ):it(it), num(0){}

Integer::~Integer()
{
}

Integer::Integer(const Integer& ige)
{
    it = ige.it;
    num = ige.num;
}

Integer &Integer::operator =(const Integer &ige)
{
    it = ige.it;
    num = ige.num;
}
int Integer::getNum(){
    return num;
}
void Integer::numAdd(){
    ++num;
}

int Integer::getIt()
{
    return it;
}
