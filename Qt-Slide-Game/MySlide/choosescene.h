#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include <QPainter>
#include <mypushbutton.h>
#include <gamecore.h>
#include <QTimer>




class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);


signals:
    void back_mainscene();
    void Create();

public slots:
};

#endif // CHOOSESCENE_H
