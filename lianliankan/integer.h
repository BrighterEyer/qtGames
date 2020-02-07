#ifndef INTEGER_H
#define INTEGER_H
class Integer{
    int it;//数值
    int num;//记录被调用次数
public:
    Integer(int it = 0);
    ~Integer();
    Integer(const Integer& ige);
    Integer& operator = (const Integer& ige);
    int getNum();//获取计数
    void numAdd();//计数加一
    int getIt();//获取数值
};
#endif // INTEGER_H
