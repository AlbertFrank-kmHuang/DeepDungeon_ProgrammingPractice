#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "prepare.h"
#include <QStyle>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(2556, 1179);
this->setStyleSheet("QWidget { "
                         "background-image: url(:/backgrounds/main_background.jpg); "
                         "background-repeat: no-repeat; "
                         "background-position: center; "
                         "}");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_newgamebutton_clicked()
{
    static prepare *p = new prepare();
    p->show();
    this->hide();
}

