#ifndef SIMPLE_H
#define SIMPLE_H

#include <QWidget>
#include <QStack>
#include <QPair>
#include "mainwindow.h"

namespace Ui {
class Simple;
}

class Simple : public QWidget
{
    Q_OBJECT

public:
    explicit Simple(QWidget *parent = 0);
    ~Simple();

private slots:

    void on_DELButton_clicked();

    void on_ACButton_clicked();

    void on_equalButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Simple *ui;
    QString expression;
    void calculate(QStack<QPair<char,int> > &s_opt,QStack<double> &s_num);
    int priority(char opt);

};

#endif // SIMPLE_H
