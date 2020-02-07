#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "newleveldialog.h"

#include "leveltreeitem.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QGraphicsPixmapItem>

#include "graphicsblockscene.h"

#include "graphicsblockitem.h"

#include "grounddialog.h"

#include "leveltreewidget.h"

#include "exchangeleveldialog.h"

#include <QToolButton>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow* instance;

private slots:
    void on_actionNewFile_triggered();


    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionDebug_triggered();

    void on_toolButton_1_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_10_clicked();

    void on_toolButton_11_clicked();

    void on_action_Delete_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_Project_triggered();

    void on_action_Export_Bin_triggered();

    void on_toolButton_12_clicked();

    void on_action_About_triggered();

    void on_toolButton_13_clicked();

    void on_toolButton_16_clicked();

    void on_toolButton_14_clicked();

    void on_toolButton_15_clicked();

    void on_toolButton_17_clicked();

    void on_toolButton_18_clicked();

    void on_toolButton_19_clicked();

    void on_toolButton_21_clicked();

    void on_toolButton_20_clicked();

    void on_toolButton_22_clicked();

    void on_toolButton_23_clicked();

    void on_action_2_triggered();

    void on_action_Paste_triggered();

    void on_action111_triggered();

    void on_toolButton_24_clicked();

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;

    NewLevelDialog* newLevelDialog;


    GroundDialog* groundDialog;

    ExchangeLevelDialog* exchangeDialog;

    //QGraphicsEffect* effect;

    QGraphicsView *view;

    GraphicsBlockScene* scene;

    QGraphicsRectItem *rectItem;

    QGraphicsPixmapItem* pixmapItem;

    int mapRows;
    int mapColumns;


    //缩放因子
    static float scaleRadio;

    QVector<GraphicsBlockItem*> blockItemArray;

    QVector<QToolButton*> toolButtonArray;

public:


    LevelTreeWidget* treeWidget;


    static int toolButtonTypes;

    //树列表
    QVector<LevelTreeItem*> treeItemsArray;


public:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
     void zoom();
    // void zoomOut();

    static float getScaleRadio();

    void hideAllToolButtons();

    void setToolButtonType(int _type);


    //是否按下ctrl
   static bool isPressCtrl;

   static MainWindow* sharedInstance();


   void writeLevels();

   void exportLevels();

   void loadLevels(QString _strName);


   int getSpecialBlockTypeCount(LevelTreeItem* levelItem,int _type);

};

#endif // MAINWINDOW_H
