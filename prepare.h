#ifndef PREPARE_H
#define PREPARE_H

#include <QWidget>

namespace Ui {
class prepare;
}

class prepare : public QWidget
{
    Q_OBJECT

public:
    explicit prepare(QWidget *parent = nullptr);
    ~prepare();

private slots:
    void on_btn_start_clicked();

    void on_btn_test_add_money_clicked();

private:
    Ui::prepare *ui;
    int money = 0;
    int count = 0;
};

#endif // PREPARE_H
