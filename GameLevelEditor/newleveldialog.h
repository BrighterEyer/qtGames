#ifndef NEWLEVELDIALOG_H
#define NEWLEVELDIALOG_H

#include <QDialog>
#include "LevelTreeItem.h"


#include "graphicsblockscene.h"

namespace Ui {
class NewLevelDialog;
}

class NewLevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLevelDialog(QWidget *parent = 0);
    ~NewLevelDialog();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_12_clicked();

private:
    Ui::NewLevelDialog *ui;

    QTreeWidget *treeWidget;


    GraphicsBlockScene* scene;

   // LevelTreeItem* duplicateItem;

   // QVector<LevelTreeItem*> treeItemsArray;



public:

    //编辑关卡标签
    bool isEditLevel;

    bool isDuplicateLevel;

public:

    void setTreeWidget(QTreeWidget *treeWidget);

    int getTreeItemsCount() const;

    QString getDefaultLevelName() const;

    void createNewLevel();

    //编辑关卡
    void editLevel();

    void duplicateLevel(LevelTreeItem* _levelItem);

    void setSceneDelegate(GraphicsBlockScene* _scene);

    void initCondition();

    void updateCondition(LevelTreeItem* levelTreeItem);

    //更新指定类型
    void updateSpecialBlockType(LevelTreeItem* _levelTreeItem);

    void debug();
   //void setTreeItemsArray(QVector<LevelTreeItem*> _treeItemsArray);

};

#endif // NEWLEVELDIALOG_H
