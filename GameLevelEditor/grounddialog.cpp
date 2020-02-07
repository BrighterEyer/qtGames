#include "grounddialog.h"
#include "ui_grounddialog.h"

#include <QDebug>

int GroundDialog::groundType = -1;

GroundDialog::GroundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroundDialog)
{
    ui->setupUi(this);


    groundButtonArray.push_back(ui->toolButton_1);
    groundButtonArray.push_back(ui->toolButton_2);
    groundButtonArray.push_back(ui->toolButton_3);
    groundButtonArray.push_back(ui->toolButton_4);
    groundButtonArray.push_back(ui->toolButton_5);
    groundButtonArray.push_back(ui->toolButton_6);
    groundButtonArray.push_back(ui->toolButton_7);
    groundButtonArray.push_back(ui->toolButton_8);
    groundButtonArray.push_back(ui->toolButton_9);
    groundButtonArray.push_back(ui->toolButton_10);
    groundButtonArray.push_back(ui->toolButton_11);
    groundButtonArray.push_back(ui->toolButton_12);
    groundButtonArray.push_back(ui->toolButton_13);

}

GroundDialog::~GroundDialog()
{
    delete ui;
    for(int i=0;i<groundButtonArray.count();++i)
    {
        QToolButton* button = (QToolButton*)groundButtonArray[i];
        delete button;
    }
    groundButtonArray.clear();
}

int GroundDialog::getGroundType()
{
    return groundType;
}

void GroundDialog::hideAllToolButtons()
{
    for(int i=0;i<groundButtonArray.count();++i)
    {
        QToolButton* button = (QToolButton*)groundButtonArray[i];
        button->setChecked(false);
    }
}

void GroundDialog::setGroundType(int _type)
{
    hideAllToolButtons();
    groundType = _type;

    qDebug()<<"groundType:"<<groundType;
}

void GroundDialog::on_toolButton_1_clicked()
{
    setGroundType(1);
    ui->toolButton_1->setChecked(true);
}

void GroundDialog::on_toolButton_2_clicked()
{
    setGroundType(2);
    ui->toolButton_2->setChecked(true);
}

void GroundDialog::on_toolButton_3_clicked()
{
    setGroundType(3);
    ui->toolButton_3->setChecked(true);
}

void GroundDialog::on_toolButton_4_clicked()
{
    setGroundType(4);
    ui->toolButton_4->setChecked(true);
}

void GroundDialog::on_toolButton_5_clicked()
{
    setGroundType(5);
    ui->toolButton_5->setChecked(true);
}

void GroundDialog::on_toolButton_6_clicked()
{
    setGroundType(6);
    ui->toolButton_6->setChecked(true);
}

void GroundDialog::on_toolButton_7_clicked()
{
    setGroundType(7);
    ui->toolButton_7->setChecked(true);
}

void GroundDialog::on_toolButton_8_clicked()
{
    setGroundType(8);
    ui->toolButton_8->setChecked(true);
}

void GroundDialog::on_toolButton_9_clicked()
{
    setGroundType(-1);
    ui->toolButton_9->setChecked(true);
}

void GroundDialog::on_toolButton_10_clicked()
{
    setGroundType(-3);
    ui->toolButton_10->setChecked(true);
}

void GroundDialog::on_toolButton_11_clicked()
{
    setGroundType(-6);
    ui->toolButton_11->setChecked(true);
}

void GroundDialog::on_toolButton_12_clicked()
{
    setGroundType(-7);
    ui->toolButton_12->setChecked(true);
}

void GroundDialog::on_toolButton_13_clicked()
{
    setGroundType(-5);
    ui->toolButton_13->setChecked(true);
}

void GroundDialog::on_toolButton_1_clicked(bool checked)
{

}
