#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <choosescene.h>
#include <record_scene.h>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>


namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //绘图事件
    void paintEvent(QPaintEvent *);
    //场景指针
    ChooseScene *choosescene;
    Record_Scene *recordscene;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
