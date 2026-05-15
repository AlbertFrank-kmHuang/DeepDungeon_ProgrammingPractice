#include "prepare.h"
#include "ui_prepare.h"
#include <QMessageBox>         // 弹窗工具
#include <QDebug>              // 打印工具

prepare::prepare(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::prepare)
{
    ui->setupUi(this);

    ui->money_show->setText("Money:" + QString::number(money));

    ui->count_show->setText("Count:" + QString::number(count));
}

prepare::~prepare()
{
    delete ui;
}

void prepare::on_btn_start_clicked()
{
    qDebug() << "Start Game!";
}



