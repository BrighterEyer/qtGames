#ifndef EXCHANGELEVELDIALOG_H
#define EXCHANGELEVELDIALOG_H

#include <QDialog>

#include "graphicsblockitem.h"

namespace Ui {
class ExchangeLevelDialog;
}

class ExchangeLevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeLevelDialog(QWidget *parent = 0);
    ~ExchangeLevelDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ExchangeLevelDialog *ui;

    QVector<GraphicsBlockItem*> levelTreeItemsArray;

public:

    void exchangeLevel();

};



#endif // EXCHANGELEVELDIALOG_H
