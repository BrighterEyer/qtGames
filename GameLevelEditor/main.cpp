#include "mainwindow.h"
#include <QApplication>


#include <QFile>

#include "LevelGlobal.h"

#include <QDebug>

#include <QTextCodec>

#include "LevelGlobal.h"

void writeLevel();

void readLevel();

void readLevel()
{
    QFile file("C:/level.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"couldn't read files!";
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_7);

    int aaa = 0;
    in>>aaa;

    int row;
    int column;

    in>>row;
    in>>column;

    qDebug()<<"aaa:"<<aaa<<"row:"<<row<<"column:"<<column;

    file.flush();
    file.close();
}

void writeLevel()
{
    QFile file("C:/level.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"couldn't write files!";
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_7);


    out<<0x89504E47;


    file.flush();
    file.close();
}

void readImage()
{
    QFile file("C:/buy_item.png");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"HELLO";
        return;
    }

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *w = MainWindow::sharedInstance();


    //编码设置
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);


    w->setWindowTitle(strAppName+strAppVersion);
    w->resize(SCREEN_WIDTH,SCREEN_HEIGHT);

    //QIcon appIcon("/res/icon.png");
    w->setWindowIcon(QIcon(strIconPath));
    w->show();


//    int aa = 9000000;

//    int bb = aa<<255;

//    qDebug()<<"result"<<((0<<32)|(0<<16)|(19<<8)|136);

    writeLevel();


    //qDebug()<<"resut1:"<<(bb|255);


    //qDebug()<<"value:"<<FILE_CHECK_HEADER_CODE;


//    writeLevel();
//    readLevel();







    return a.exec();
}
