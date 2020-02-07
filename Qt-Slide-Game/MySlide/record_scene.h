#ifndef RECORD_SCENE_H
#define RECORD_SCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <mypushbutton.h>


namespace Ui {
class Record_Scene;
}

class Record_Scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit Record_Scene(QWidget *parent = 0);
    ~Record_Scene();

    void paintEvent(QPaintEvent *);

private:
    Ui::Record_Scene *ui;

signals:
    void back_mainscene();

};

#endif // RECORD_SCENE_H
