#ifndef REVIEW_H
#define REVIEW_H

#include <QWidget>

namespace Ui {
class review;
}

class review : public QWidget
{
    Q_OBJECT

public:
    explicit review(QWidget *parent = nullptr);
    ~review();

private:
    Ui::review *ui;
};

#endif // REVIEW_H
