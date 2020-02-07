#include"look.h"
#include<QPalette>
#include<QTime>
#include<QPen>
#include <unistd.h>
Look::Look()
{
    catchNum = 0;
    isPaint = false;
    confirm = false;
    cth[0] = 10;
    cth[1] = 4;
    cth[2] = 2;
    qln[0] = NULL;
    qln[1] = NULL;
    qln[2] = NULL;
    score = 0;
    QTextCodec* code = QTextCodec::codecForName("UTF-8");
    //    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);

    char sc[256] = {0};
    sprintf(sc, "Level %d\n\n%d\nScore", catchNum + 1, score);
    qpb = new QLabel("0",this);
    qpb->setMargin(1);
    qpb->setLineWidth(2);
    qpb->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    qpb->setText(sc);
    qpb->resize(60,100);
    qpb->move(360,60);
    QString str = QObject::tr("认输");
    sur = new QPushButton(str, this);
    sur->move(350, 200);
    prompt = new QPushButton(tr("提示"), this);
    prompt->move(350, 240);
    first = NULL;
    next = NULL;
    count = 0;
    qsrand (QTime::currentTime ().msec ());
    callBack();
    int x = 0, y = LEN, m = LEN, n = LEN;
    for(int i = 0; i != 50; ++i){//分配前50个矩形
        vec.push_back(new QRect(x += LEN, y, m, n));
        if((i+1)%10 == 0){
            x = 0;
            y += LEN;
        }
    }
    y += 0;
    for(int i = 50; i != 100; ++i){//分配后50个矩形
        vec.push_back(new QRect(x += LEN, y , m ,n));
        if((i+1)%10 == 0){
            x = 0;
            y += LEN;
        }
    }
    tm = new QTimer();
    tm->setInterval (1);
    tm->start ();
    tm1 = new QTimer();
    tm1->setInterval(200);
    tm1->start();
    connect (tm1, SIGNAL(timeout()), this, SLOT(checkCall()));
    connect(this, SIGNAL(sig()), tm1, SLOT(start()));
    connect(sur, SIGNAL(clicked()), this, SLOT(surrender()));
    connect(prompt, SIGNAL(clicked()), this, SLOT(requestHelp()));
}
Look::~Look (){

    vec.clear();
    clr.clear();
    ran.clear();
    use.clear();
}

void Look::mousePressEvent(QMouseEvent *e)//鼠标点击事件
{
    if(e->button() == Qt::LeftButton){
        for(int i = 0; i != 100; ++i){
            if(!paintOrNot (i)){
                if(e->x() >= vec[i]->x() && e->x() <= (vec[i]->x()+LEN) && e->y() >= vec[i]->y() &&
                        e->y() <= (vec[i]->y()+LEN)){
                    count++;
                    if(count%2){
                        first = vec[i];
                        cout << "first:" << clr[use[i]->getIt()]->getPt() << '(' << i << ')' << endl;
                    }
                    else{
                        cout << "next:" << clr[use[i]->getIt()]->getPt() << '(' << i << ')' << endl;
                        next = vec[i];
                    }
                    if(confirm){
                        confirm = false;
                    }else{
                        if(first && next){
                            //cout << "mouse2" << endl;
                            if(checkSlot()){
                                switch(catchNum){
                                case 1: score += 10;break;
                                case 2: score += 20;break;
                                case 3: score += 50;break;
                                }
                                char sc[30];
                                sprintf(sc, "Level %d\n\n%d\nScore", catchNum, score);
                                qpb->setText(sc);
                                if(paint.size() == 100){
                                    if(catchNum == 3){//判定是否通关
                                        QMessageBox qmb;
                                        QPushButton* pb = qmb.addButton(tr("神功大成"), QMessageBox::ActionRole);
                                        QString str = QObject::tr("全部通关！");
                                        qmb.setText(str);
                                        qmb.exec();
                                        if(qmb.clickedButton() == pb) {
                                            this->close();
                                        }
                                    }
                                    //弹出框是否继续闯关
                                    QMessageBox qmb;
                                    qmb.resize(120,50);
                                    QPushButton* qb1 = qmb.addButton(tr("必须的"), QMessageBox::ActionRole);
                                    QPushButton* qb2 = qmb.addButton(tr("我想回家"), QMessageBox::ActionRole);
                                    //qmb.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
                                    char msg[256] = {0} ;
                                    sprintf(msg, "第%d关完成，继续 ?", catchNum);
                                    QString str = tr(msg);
                                    qmb.setText(str);
                                    qmb.exec();
                                    if(qmb.clickedButton() == qb2){
                                        this->close();
                                    }else{
                                        first = NULL;
                                        next = NULL;
                                        callBack();
                                        char sc[30];
                                        sprintf(sc, "Level %d\n\n%d\nScore", catchNum, score);
                                        qpb->setText(sc);
                                        update();
                                    }
                                }
                                isPaint = true;
                                emit(sig());
                            }
                        }
                    }
                    update();
                    break;
                }
            }
        }
    }
}
bool Look::checkSlot(){//根据方块状态进行的行为操作
    QColor firstColor, nextColor;
    int num1, num2;
    if(first && next){
        for(int i = 0; i != 100; ++i){
            if(!paintOrNot (i)){
                if(first == vec[i]){
                    firstColor = *(clr[use[i]->getIt()]->getPt());
                    num1 = i;

                }
                if(next == vec[i]){
                    nextColor = *(clr[use[i]->getIt()]->getPt());
                    num2 = i;
                }
            }
        }
        if(firstColor == nextColor && first != next){
            //        cout << "checkSlot" << endl;
            if(first->y() < next->y()){
                if(allCheck(first, next)){
                    paint.push_back (num1);
                    paint.push_back (num2);
                    count = 0;
                    return true;
                }
            }else if(first->y() > next->y()){
                if(allCheck(next, first)){
                    paint.push_back (num1);
                    paint.push_back (num2);
                    count = 0;
                    return true;
                }
            }else{
                if(first->x() < next->x()){
                    //   cout << "checkSlot1" << endl;
                    if(oneLineCheck(first, next) || specialCheck(first, next)){
                        paint.push_back (num1);
                        paint.push_back (num2);
                        count = 0;
                        return true;
                    }
                }else if (first->x() > next->x()){
                    //   cout << "checkSlot2" << endl;
                    if(oneLineCheck(next, first) || specialCheck(next, first)){
                        paint.push_back (num1);
                        paint.push_back (num2);
                        count = 0;
                        return true;
                    }
                }
                //  cout << "checkSlot3" << endl;
            }
        }
        return false;
    }
    return false;

}
void Look::checkCall()//判定方块状态
{
    if(isPaint){
        isPaint = false;
        update();
    }
}

void Look::buttonRemove()//测试函数
{
    //QVector<QPushButton*>::iterator it = vec.begin ();
    // vec.erase (it + 2);
    //it = vec.begin ();
    //vec.erase (it + 52);
    //  paint.push_back (2);
}
bool Look::paintOrNot(int num){//矩形方块是否显示
    for(QVector<int>::iterator it = paint.begin ();  it != paint.end (); ++it){
        if(*it == num)
            return true;
    }
    return false;
}
void Look::paintEvent(QPaintEvent *)//绘图事件
{
    qsrand (QTime::currentTime ().msec ());
    QPainter* pt = new QPainter(this);
    QPen cpen = pt->pen();
    for(int i = 0; i != 100; ++i){
        QColor* temp = clr[use[i]->getIt()]->getPt();
        if(!paintOrNot (i)){
            pt->fillRect (*vec[i], *temp);
            if(first == vec[i]){
                QPen pen = QPen(QColor(0, 0, 0));
                pen.setWidth(6);
                pt->setPen(pen);
                pt->drawRect(*first);
                pt->setPen(cpen);

            }
            if(next == vec[i]){

                QPen pen = QPen(QColor(0, 0, 0));
                pen.setWidth(6);
                pt->setPen(pen);
                pt->drawRect(*next);
                pt->setPen(cpen);

            }
            pt->drawRect (*vec[i]);
        }
    }
    if(isPaint && !confirm){
        QPen pen = QPen(QColor(52, 204, 248));
        pen.setWidth(4);
        pt->setPen(pen);
        for(int i = 0; i != 3; ++i){
            //cout << "qln[" << i << "] = " << qln[i] << endl;
            if(qln[i]){
                pt->drawLine(*qln[i]);
            }
        }
        pt->setPen(cpen);
        for(int i = 0; i != 3; ++i){
            if(qln[i]){
                delete qln[i];
                qln[i] = NULL;
            }
        }
    }
}

bool Look::allCheck(QRect *rec1, QRect *rec2)//检查是否消除
{
    return oneLineCheck (rec1, rec2) || twoLineCheck (rec1, rec2) ||
            threeLineCheck (rec1, rec2);
}

bool Look::oneLineCheck(QRect *rec1, QRect *rec2)//单线消除算法
{  // cout << "oneLine" << endl;
    int dx = qAbs(rec1->x () - rec2->x ()) / LEN;
    int dy = qAbs(rec1->y () - rec2->y ()) / LEN;

    for(int i = 0; i != 100; ++i){
        if(rec1 == vec[i] || rec2 == vec[i]){
            if(rec1->x() == rec2->x()){
                if(dy==1){
                    //        cout << "O1" << endl;
                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15, rec2->x()+15, rec2->y()+15);
                    return true;
                }
                else if(dy > 1){
                    for(int j = i + 10; j != i + dy*10; j += 10){
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dy*10 - 10){
                            //           cout << "O2" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15, rec2->x()+15, rec2->y()+15);
                            return true;
                        }
                    }
                }
            }
            if(rec1->y() == rec2->y()){
                if(dx == 1){
                    //  cout << "O3" << endl;
                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15, rec2->x()+15, rec2->y()+15);
                    return true;
                }
                else if(dx > 1){
                    // cout << "00" << endl;
                    for(int j = i + 1; j < i + dx ; ++j){
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dx - 1){
                            //     cout << "O4" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15, rec2->x()+15, rec2->y()+15);
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }
}

//用vec下标进行循环判断  两条线段一个拐点
bool Look::twoLineCheck(QRect *rec1, QRect *rec2){//双线消除算法
    // cout << "twoLine" << endl;
    int dx = qAbs(rec1->x () - rec2->x ()) / LEN;
    int dy = qAbs(rec1->y () - rec2->y ()) / LEN;
    for(int i = 0; i != 100; ++i){
        if(vec[i] == rec1 && !(dx == 0 && dy == 0)){
            //rec1在左上
            if(rec1->x () < rec2->x ()){
                for(int j = i + 1; j <= i + dx; ++j){// 先右后下
                    if(!paintOrNot(j))
                        break;
                    if(j == i + dx){
                        for(int k = j; k < j + dy*10; k += 10){
                            if(!paintOrNot(k))
                                break;
                            if(k == j + dy*10 - 10){
                                //   cout << "T1" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   vec[j]->x()+15, vec[j]->y()+15);
                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }
                        }
                    }
                }
                for(int j = i + 10; j <= i + dy*10; j += 10){ //先下后右
                    if(!paintOrNot(j))
                        break;
                    if(j == i + dy*10){
                        for(int k = j; k < j + dx; ++k){
                            if(!paintOrNot(k))
                                break;
                            if(k == j + dx - 1){
                                //  cout << "T2" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   vec[j]->x()+15, vec[j]->y()+15);
                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
            //rec1在右上
            else if(rec1->x () > rec2->x ()){
                for(int j = i - 1; j >= i - dx; --j){// 先左后下
                    if(!paintOrNot (j))
                        break;
                    if(j == i - dx){
                        for(int k = j; k < j + dy*10; k += 10){
                            if(!paintOrNot(k))
                                break;
                            if(k == j + dy*10 - 10){
                                //   cout << "T3" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   vec[j]->x()+15, vec[j]->y()+15);
                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }
                        }
                    }
                }
                for(int j = i + 10; j <= i + dy*10; j += 10){ //先下后左
                    if(!paintOrNot(j))
                        break;
                    if(j == i + dy*10){
                        for(int k = j; k > j - dx; --k){
                            if(!paintOrNot(k))
                                break;
                            if(k == j - dx + 1){
                                //  cout << "T4" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   vec[j]->x()+15, vec[j]->y()+15);
                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
        }
    }
    return false;
}

//坐标位置来确定二次折线的可能性

bool Look::threeLineCheck (QRect *rec1, QRect *rec2){//三线消除算法
    //  cout << "threeLine" << endl;
    int dx = (rec2->x () - rec1->x ()) / LEN;
    int dy = (rec2->y () - rec1->y ()) / LEN;
    for(int i = 0; i != 100; ++i){
        if(rec1 == vec[i]){
            //x方向上寻找点 可以实现一次折线
            if(i%10 == 0){//rec1 靠最左边
                if(dx == 0){
                    // cout << "test0" << endl;
                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                       15, rec1->y()+15);
                    qln[1] = new QLine(15, rec1->y()+15,
                                       15, rec2->y()+15);
                    qln[2] = new QLine(15, rec2->y()+15,
                                       rec2->x()+15, rec2->y()+15);
                    return true;
                }
                else if(qAbs(dx) == 9){
                    for(int j = i + 1; j <= i + 9; ++j){ //向右
                        if(!paintOrNot(j)){
                            break;
                        }
                        else if(j == i + 9){
                            //  cout << "test1" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               345, rec1->y()+15);
                            qln[1] = new QLine(345, rec1->y()+15,
                                               345, rec2->y()+15);
                            qln[2] = new QLine(345, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);

                            return true;
                        }else{
                            for(int k = j; k <= j + dy*10; k += 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dy*10){
                                    for(int m = k; m < i + dx + dy*10; ++m){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dx + dy*10 - 1){
                                            // cout << "test1B" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for(int j = i + dy*10; j < i + dx + dy*10; ++j){//向左
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dx + dy*10 - 1){
                            // cout << "test1C" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               15, rec1->y()+15);
                            qln[1] = new QLine(15, rec1->y()+15,
                                               15, rec2->y()+15);
                            qln[2] = new QLine(15, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }
                    }
                }else{
                    for(int j = i + dy*10; j < i + dy*10 + dx; ++j){//向左
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dy*10 + dx - 1){
                            // cout << "test2" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               15, rec1->y()+15);
                            qln[1] = new QLine(15, rec1->y()+15,
                                               15, rec2->y()+15);
                            qln[2] = new QLine(15, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }
                    }
                    for(int j = i + 1; j <= i + 9; ++j){//向右
                        if(!paintOrNot(j))
                            break;
                        else if(j == i + 9){
                            for(int k = j + dy*10; k > i + dx + dy*10; --k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + dy*10 + 1){
                                    // cout << "test2A" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       345, rec1->y()+15);
                                    qln[1] = new QLine(345, rec1->y()+15,
                                                       345, rec2->y()+15);
                                    qln[2] = new QLine(345, rec2->y()+15,
                                                       rec2->x()+15, rec2->y()+15);
                                    return true;
                                }
                            }
                        }else{
                            for(int k = j; k <= j + dy*10; k += 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dy*10){
                                    if(vec[k]->x() > rec2->x()){ //rec2的x坐标较小
                                        for(int m = k; m > i + dx + dy*10; --m){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 + 1){
                                                // cout << "test2B" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[1] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   vec[m]->x()+15, vec[m]->y()+15);
                                                qln[2] = new QLine(vec[m]->x()+15, vec[m]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }else if(vec[k]->x() < rec2->x()){//rec2的x坐标较大
                                        for(int m = k; m < i + dx + dy*10; ++m){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 - 1){
                                                // cout << "test2C" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(i%10 == 9){//rec1 靠最右边
                if(qAbs(dx) == 0){//rec2靠最右
                    // cout << "test2D" << endl;
                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                       345, rec1->y()+15);
                    qln[1] = new QLine(345, rec1->y()+15,
                                       345, rec2->y()+15);
                    qln[2] = new QLine(345, rec2->y()+15,
                                       rec2->x()+15, rec2->y()+15);
                    return true;
                }else if(qAbs(dx) == 9){//rec2靠最左
                    for(int j = i - 1; j >= i - 9; --j){
                        if(!paintOrNot(j))
                            break;
                        else if(j == i - 9){
                            //  cout << "test3" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               15, rec1->y()+15);
                            qln[1] = new QLine(15, rec1->y()+15,
                                               15, rec2->y()+15);
                            qln[2] = new QLine(15, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }else{
                            for(int k = j; k <= j + dy*10; k += 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dy*10){
                                    for(int m = k; m > i + dy*10 + dx; --m){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dy*10 + dx + 1){
                                            //  cout << "test3A" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for(int j = i + dy*10; j > i + dy*10 + dx; --j){
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dx + dy*10 + 1){
                            //  cout << "test3AA" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               345, rec1->y()+15);
                            qln[1] = new QLine(345, rec1->y()+15,
                                               345, rec2->y()+15);
                            qln[2] = new QLine(345, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }

                    }
                }else{//rec2在中部

                    for(int j = i + dy*10; j > i + dy*10 + dx; --j){
                        if(!paintOrNot(j))
                            break;
                        if(j == i + dy*10 + dx + 1){
                            // cout << "test4" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               345, rec1->y()+15);
                            qln[1] = new QLine(345, rec1->y()+15,
                                               345, rec2->y()+15);
                            qln[2] = new QLine(345, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }
                    }
                    for(int j = i - 1; j >= i - 9; --j){
                        if(!paintOrNot(j))
                            break;
                        else if(j == i - 9){
                            for(int k = j + dy*10; k < i + dx + dy*10; ++k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + dy*10 - 1){
                                    //  cout << "test4A" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       15, rec1->y()+15);
                                    qln[1] = new QLine(15, rec1->y()+15,
                                                       15, rec2->y()+15);
                                    qln[2] = new QLine(15, rec2->y()+15,
                                                       rec2->x()+15, rec2->y()+15);
                                    return true;
                                }
                            }
                        }else{

                            for(int k = j; k <= j + dy*10; k += 10){
                                // cout << "靠右 向左 再向下1" << endl;
                                if(!paintOrNot(k)){
                                    //  cout << "靠右 向左 再向下3" << endl;
                                    break;
                                }
                                cout << "靠右 向左 再向下2" << endl;
                                if(k == j + dy*10){
                                    // cout << "靠右 向左 再向下3" << endl;
                                    if(vec[k]->x() > rec2->x()){//rec2的x坐标较小
                                        for(int m = k; m > i + dx + dy*10; --m){
                                            // cout << "靠右 向左 再向下4" << endl;
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 + 1){
                                                //    cout << "test4B" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }else if(vec[k]->x() < rec2->x()){//rec2的x坐标较大
                                        for(int m = k; m < i + dx + dy*10; ++m){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 - 1){
                                                //  cout << "test4C" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else {//rec1在中间
                for(int j = i - 1; j >= i - i%10; --j){ //向左边
                    if(!paintOrNot(j)){
                        break;
                    }else if( j == i - i%10){
                        if(rec2->x() == 30){
                            //   cout << "test5" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               15, rec1->y()+15);
                            qln[1] = new QLine(15, rec1->y()+15,
                                               15, rec2->y()+15);
                            qln[2] = new QLine(15, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }else{
                            for(int k = j + dy*10; k < i + dy*10 + dx; ++k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + dy*10 - 1){
                                    //  cout << "test5B" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       15, rec1->y()+15);
                                    qln[1] = new QLine(15, rec1->y()+15,
                                                       15, rec2->y()+15);
                                    qln[2] = new QLine(15, rec2->y()+15,
                                                       rec2->x()+15, rec2->y()+15);
                                    return true;
                                }
                            }
                        }
                    }else {
                        for(int m = j; m <= j + dy*10; m += 10){
                            if(!paintOrNot(m))
                                break;
                            if(m == j + dy*10){
                                if(vec[m]->x() < rec2->x()){//rec2的x坐标比较大
                                    for(int z = m; z < i + dy*10 + dx; ++z){
                                        if(!paintOrNot(z))
                                            break;
                                        if(z == i + dy*10 + dx - 1){
                                            //cout << "test6" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[m]->x()+15, vec[m]->y()+15);
                                            qln[2] = new QLine(vec[m]->x()+15, vec[m]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }else if (vec[m]->x() > rec2->x()){//rec2的x坐标比较小
                                    for(int z = m; z > i + dy*10 + dx; --z){
                                        if(!paintOrNot(z))
                                            break;
                                        if(z == i + dy*10 + dx + 1){
                                            //cout << "test7" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[m]->x()+15, vec[m]->y()+15);
                                            qln[2] = new QLine(vec[m]->x()+15, vec[m]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                for(int j = i + 1; j <= i - i%10 + 9; ++j){//向右
                    if(!paintOrNot(j)){
                        break;
                    }else if( j == i - i%10 +9){
                        if(rec2->x() == 300){
                            // cout << "test8" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               345, rec1->y()+15);
                            qln[1] = new QLine(345, rec1->y()+15,
                                               345, rec2->y()+15);
                            qln[2] = new QLine(345, rec2->y()+15,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }else{
                            for(int k = j + dy*10; k > i + dy*10 + dx; --k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + dy*10 + 1){
                                    // cout << "test8B" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       345, rec1->y()+15);
                                    qln[1] = new QLine(345, rec1->y()+15,
                                                       345, rec2->y()+15);
                                    qln[2] = new QLine(345, rec2->y()+15,
                                                       rec2->x()+15, rec2->y()+15);
                                    return true;
                                }
                            }
                        }
                    }else{
                        for(int k = j; k <= j + dy*10; k += 10){
                            if(!paintOrNot(k))
                                break;
                            if(k == j + dy*10){
                                if(vec[k]->x() < rec2->x()){//rec2的x坐标较大
                                    for(int m = k; m < i + dy*10 + dx; ++m){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dy*10 + dx - 1){
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            //cout << "test9" << endl;
                                            return true;
                                        }
                                    }
                                }else if(vec[k]->x() > rec2->x()){//rec2的x坐标较小
                                    for(int m = k; m > i + dy*10 + dx; --m){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dy*10 + dx + 1){
                                            // cout << "test10" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15, rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //y方向上寻找点 可以实现一次折线
            if(i/10 == 0){// rec1在最上方
                for(int j = i + dx; j < i + dx + dy*10; j += 10){//向上
                    if(!paintOrNot(j))
                        break;
                    if(j == i + dx + dy*10 -10){
                        // cout << "test12" << endl;
                        qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                           rec1->x()+15, 15);
                        qln[1] = new QLine(rec1->x()+15, 15,
                                           rec2->x()+15, 15);
                        qln[2] = new QLine(rec2->x()+15, 15,
                                           rec2->x()+15, rec2->y()+15);
                        return true;
                    }
                }

                for(int j = i + 10; j <= i + 9*10; j += 10){ //向下
                    if(!paintOrNot(j))
                        break;
                    else if (j == i + 9*10){
                        if(rec2->x() == 300){
                            // cout << "test12B" << endl;
                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                               rec1->x()+15, 345);
                            qln[1] = new QLine(rec1->x()+15, 345,
                                               rec2->x()+15, 345);
                            qln[2] = new QLine(rec2->x()+15, 345,
                                               rec2->x()+15, rec2->y()+15);
                            return true;
                        }else{
                            for(int k = j + dx; k > i + dx + dy*10; k -= 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + dy*10 + 10){
                                    //  cout << "test12C" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       rec1->x()+15, 345);
                                    qln[1] = new QLine(rec1->x()+15, 345,
                                                       rec2->x()+15, 345);
                                    qln[2] = new QLine(rec2->x()+15, 345,
                                                       rec2->x()+15, rec2->y()+15);
                                }
                            }
                        }
                    }else{
                        // cout << "THREELINE" << endl;
                        if(vec[j]->x() < rec2->x()){//rec2的x坐标较大
                            for(int k = j; k <= j + dx; ++k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dx){
                                    if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                        for(int m = k; m < i + dx + dy*10; m += 10){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 - 10){
                                                // cout << "test12D" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                        for(int m = k; m > i + dx + dy*10; m -= 10){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 + 10){
                                                // cout << "test12E" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }else if(vec[j]->x() > rec2->x()){//rec2的x坐标较小
                            for(int k = j; k >= j + dx; --k){

                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dx){
                                    if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                        for(int m = k; m < i + dx + dy*10; m += 10){

                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 - 10){
                                                // cout << "test12F" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                        for(int m = k; m > i + dx + dy*10; m -= 10){
                                            if(!paintOrNot(m))
                                                break;
                                            if(m == i + dx + dy*10 + 10){
                                                // cout << "test12G" << endl;
                                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                   vec[j]->x()+15, vec[j]->y()+15);
                                                qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                   vec[k]->x()+15, vec[k]->y()+15);
                                                qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                   rec2->x()+15, rec2->y()+15);
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // rec1在y轴方向在中间区域
            else{
                for(int j = i - 10; j >= i - i/10*10; j -= 10){// rec1点开始向上
                    if(!paintOrNot(j))
                        break;
                    else{
                        if(j == i - i/10*10){//
                            if(rec2->y() == 30){
                                //  cout << "test12H" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   rec1->x(), 15);
                                qln[1] = new QLine(rec1->x()+15, 15,
                                                   rec2->x()+15, 15);
                                qln[2] = new QLine(rec2->x()+15, 15,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }else{
                                for(int k = j + dx; k < i + dx+ dy*10; k += 10){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == i + dx + dy*10 - 10){
                                        // cout << "test12I" << endl;
                                        qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                           rec1->x()+15, 15);
                                        qln[1] = new QLine(rec1->x()+15, 15,
                                                           rec2->x()+15, 15);
                                        qln[2] = new QLine(rec2->x()+15, 15,
                                                           rec2->x()+15, rec2->y()+15);
                                        return true;
                                    }
                                }
                            }
                        }else{
                            if(vec[j]->x() < rec2->x()){//rec2的x坐标较大
                                for(int k = j; k <= j + dx; ++k){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == j + dx){
                                        if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                            for(int m = k; m < i + dx + dy*10; m += 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 - 10){
                                                    //  cout << "test13" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                            for(int m = k; m > i + dx + dy*10; m -= 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 + 10){
                                                    //  cout << "test13B" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }else if(vec[j]->x() > rec2->x()){//rec2的x坐标较小
                                for(int k = j; k >= j + dx; --k){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == j + dx){
                                        if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                            for(int m = k; m < i + dx + dy*10; m += 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 - 10){
                                                    // cout << "test13C" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                            for(int m = k; m > i + dx + dy*10; m -= 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 + 10){
                                                    //  cout << "test13D" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //rec1点开始向下
                for(int j = i + 10; j <= i + (9-i/10)*10; j += 10){
                    //  cout << "THREELINE" << endl;
                    if(!paintOrNot(j))
                        break;
                    else{
                        if(j == i + (9 - i/10)*10){
                            if(rec2->y() == 300){
                                //  cout << "test13E" << endl;
                                qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                   rec1->x()+15, 345);
                                qln[1] = new QLine(rec1->x()+15, 345,
                                                   rec2->x()+15, 345);
                                qln[2] = new QLine(rec2->x()+15, 345,
                                                   rec2->x()+15, rec2->y()+15);
                                return true;
                            }else{
                                for(int k = j + dx; k > i + dx + dy*10; k -= 10){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == i + dx + dy*10 + 10){
                                        // cout << "test15" << endl;
                                        qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                           rec1->x()+15, 345);
                                        qln[1] = new QLine(rec1->x()+15, 345,
                                                           rec2->x()+15, 345);
                                        qln[2] = new QLine(rec2->x()+15, 345,
                                                           rec2->x()+15, rec2->y()+15);
                                        return true;
                                    }
                                }
                            }
                        }else {
                            if(vec[j]->x() < rec2->x()){//rec2的x坐标较大
                                for(int k = j; k <= j + dx; ++k){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == j + dx){
                                        if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                            for(int m = k; m < i + dx + dy*10; m += 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 - 10){
                                                    //  cout << "test16" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                            for(int m = k; m > i + dx + dy*10; m -= 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 + 10){
                                                    //cout << "test17" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }else if(vec[j]->x() > rec2->x()){//rec2的x坐标较小

                                for(int k = j; k >= j + dx; --k){
                                    if(!paintOrNot(k))
                                        break;
                                    if(k == j + dx){
                                        if(vec[k]->y() < rec2->y()){//rec2的y坐标较大
                                            for(int m = k; m < i + dx + dy*10; m += 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 - 10){
                                                    // cout << "test18" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }else if(vec[k]->y() > rec2->y()){//rec2的y坐标较小
                                            for(int m = k; m > i + dx + dy*10; m -= 10){
                                                if(!paintOrNot(m))
                                                    break;
                                                if(m == i + dx + dy*10 + 10){
                                                    //cout << "test19" << endl;
                                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                                       vec[j]->x()+15, vec[j]->y()+15);
                                                    qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                                       vec[k]->x()+15, vec[k]->y()+15);
                                                    qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                                       rec2->x()+15, rec2->y()+15);
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    }
}

bool Look::specialCheck(QRect *rec1, QRect *rec2)//特殊消除算法
{
    // cout << "specialCheck" << endl;
    int dx = qAbs(rec2->x () - rec1->x ()) / LEN;
    int dy = qAbs(rec2->y () - rec1->y ()) / LEN;

    if(dy == 0){
        for(int i = 0; i != 100; ++i){
            //cout << "x" << endl;
            if(vec[i] == rec1 ){
                if(i/10 == 0 || i/10 == 9){
                    // cout << "special1" << endl;
                    if(i/10 == 0){
                        qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                           rec1->x()+15,  15);
                        qln[1] = new QLine(rec1->x()+15, 15,
                                           rec2->x()+15, 15);
                        qln[2] = new QLine(rec2->x()+15, 15,
                                           rec2->x()+15,rec2->y()+15);
                    }
                    if(i/10 == 9){
                        qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                           rec1->x()+15, rec1->y()+45);
                        qln[1] = new QLine(rec1->x()+15, rec1->y()+45,
                                           rec2->x()+15, rec2->y()+45);
                        qln[2] = new QLine(rec2->x()+15, rec2->y()+45,
                                           rec2->x()+15,rec2->y()+15);
                    }
                    return true;
                }
                else{
                    for(int j = i - 10; j >= i - i/10*10; j -= 10){//向上
                        if(!paintOrNot(j)){
                            break;
                        }else if(j/10 == 0){
                            for(int k = j + dx; k < i + dx; k += 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx - 10){
                                    // cout << "special2" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       rec1->x()+15, 15);
                                    qln[1] = new QLine(rec1->x()+15, 15,
                                                       rec2->x()+15, 15);
                                    qln[2] = new QLine(rec2->x()+15, 15,
                                                       rec2->x()+15,rec2->y()+15);
                                    return true;
                                }
                            }
                        }else{
                            for(int k = j; k <= j + dx; ++k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dx){
                                    for(int m = k; m < i + dx; m += 10){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dx - 10){
                                            // cout << "special3" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15,rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for(int j = i + 10; j <= i + (9 - i/10)*10; j += 10){//向下
                        if(!paintOrNot(j)){
                            break;
                        }else if(j/10 == 9){
                            for(int k = j + dx; k > i + dx; k -= 10){
                                if(!paintOrNot(k))
                                    break;
                                if(k == i + dx + 10){
                                    //  cout << "special4" << endl;
                                    qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                       rec1->x()+15, 345);
                                    qln[1] = new QLine(rec1->x()+15, 345,
                                                       rec2->x()+15, 345);
                                    qln[2] = new QLine(rec2->x()+15, 345,
                                                       rec2->x()+15,rec2->y()+15);
                                    return true;
                                }
                            }
                        }else{
                            for(int k = j; k <= j + dx; ++k){
                                if(!paintOrNot(k))
                                    break;
                                if(k == j + dx){
                                    for(int m = k; m > i + dx; m -= 10){
                                        if(!paintOrNot(m))
                                            break;
                                        if(m == i + dx + 10){
                                            // cout << "special5" << endl;
                                            qln[0] = new QLine(rec1->x()+15, rec1->y()+15,
                                                               vec[j]->x()+15, vec[j]->y()+15);
                                            qln[1] = new QLine(vec[j]->x()+15, vec[j]->y()+15,
                                                               vec[k]->x()+15, vec[k]->y()+15);
                                            qln[2] = new QLine(vec[k]->x()+15, vec[k]->y()+15,
                                                               rec2->x()+15,rec2->y()+15);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            }
        }
    }
    return false;
}

void Look::callBack()//初始化界面
{   paint.clear();
    clr.clear();
    ran.clear();
    use.clear();
    // cout << "CALL1" << endl;
    int temp = cth[catchNum] + 100%cth[catchNum];
    for(int i = 0; i != 100/temp; ++i){
        clr.push_back(new MyColor(qrand()%256, qrand()%256, qrand()%256));
        ran.push_back(new Integer(i));
    }
    int m = 0;
    //cout<< 'm = ' << m << endl;
    cout << "CALL2" << endl;
    for(int i = 0; i != 100; ++i){
        while(1){
            Integer* ite = ran[qrand()%(100/temp)];
            //cout<< 'm = ' << m++ << endl;
            if(ite->getNum() != temp){
                use.push_back(ite);
                ite->numAdd();
                break;
            }
        }
    }
    catchNum++;
}

void Look::surrender()//投降
{
    QMessageBox msg;
    QPushButton* pb1 = msg.addButton(tr("我要逆袭"), QMessageBox::ActionRole);
    QPushButton* pb2 = msg.addButton(tr("确认"), QMessageBox::ActionRole);
    QString str = QObject::tr("投降输一半，你很乖！");
    msg.setText(str);
    msg.exec();
    if(msg.clickedButton() == pb2){
        this->close();
    }
}

void Look::requestHelp()//提示最便捷的可消除路线
{
    if(score < 100){
        QMessageBox qMsg;
        QPushButton* qPbt = qMsg.addButton(tr("你这么黑，你家里人造吗?"), QMessageBox::ActionRole);
        QString qStr = tr("提示需要消耗100分！");
        qMsg.setText(qStr);
        qMsg.exec();
        if(qMsg.clickedButton() == qPbt){
            return;
        }
    }
    QMessageBox msg;
    QPushButton* pb1 = msg.addButton(tr("良心"), QMessageBox::ActionRole);
    QPushButton* pb2 = msg.addButton(tr("卧曹"), QMessageBox::ActionRole);
    QString str = QObject::tr("您将损失100分！继续 ?");
    msg.setText(str);
    msg.exec();
    if(msg.clickedButton() == pb2)
        return;
    score -= 100;
    char sc[30];
    sprintf(sc, "Level %d\n\n%d\nScore", catchNum, score);
    qpb->setText(sc);
    for(int i = 0; i != 100; ++i){
        if(!paintOrNot(i)){
            for(int j = 0; j != 100; ++j){
                if(!paintOrNot(j)){
                    if(checkSlotB(i, j)){
                        first = vec[i];
                        next = vec[j];
                        confirm = true;
                        isPaint = true;
                        emit(sig());
                        return;
                    }
                }
            }

        }
    }
    QMessageBox msg1;
    QPushButton* pb3 = msg1.addButton(tr("泥煤啊啊"), QMessageBox::ActionRole);
    QString str1 = QObject::tr("无路可走！");
    msg1.setText(str1);
    msg1.exec();
    if(msg1.clickedButton() == pb3)
        this->close();
}
bool Look::checkSlotB(int i, int j){//二次检查
    QColor firstColor, nextColor;

    firstColor = *(clr[use[i]->getIt()]->getPt());
    nextColor = *(clr[use[j]->getIt()]->getPt());

    if(firstColor == nextColor && vec[i] != vec[j]){
        if(vec[i]->y() < vec[j]->y()){
            if(allCheck(vec[i], vec[j])){
                return true;
            }
        }else if(vec[i]->y() > vec[j]->y()){
            if(allCheck(vec[j], vec[i])){
                return true;
            }
        }else{
            if(vec[i]->x() < vec[j]->x()){
                if(oneLineCheck(vec[i], vec[j]) || specialCheck(vec[i], vec[j])){
                    return true;
                }
            }else if (vec[i]->x() > vec[j]->x()){
                if(oneLineCheck(vec[j], vec[i]) || specialCheck(vec[j], vec[i])){
                    return true;
                }
            }
        }
    }
    return false;
}




