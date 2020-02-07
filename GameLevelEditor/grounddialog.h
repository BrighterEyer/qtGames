#ifndef GROUNDDIALOG_H
#define GROUNDDIALOG_H

#include <QDialog>

#include <QVector>

#include <QToolButton>

namespace Ui {
class GroundDialog;
}

class GroundDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GroundDialog(QWidget *parent = 0);
    ~GroundDialog();

private:
    Ui::GroundDialog *ui;

public:
    static int groundType;

    QVector<QToolButton*> groundButtonArray;

public:
    static int getGroundType();

    void hideAllToolButtons();

    void setGroundType(int _type);

private slots:
    void on_toolButton_1_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();
    void on_toolButton_10_clicked();
    void on_toolButton_11_clicked();
    void on_toolButton_12_clicked();
    void on_toolButton_13_clicked();
    void on_toolButton_1_clicked(bool checked);
};

#endif // GROUNDDIALOG_H
