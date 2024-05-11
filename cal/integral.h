#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <QWidget>
#include "mainwindow.h"
#include <QStack>
#include <QPair>

namespace Ui {
class Integral;
}

class Integral : public QWidget
{
    Q_OBJECT

public:
    explicit Integral(QWidget *parent = 0);
    ~Integral();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_poi_clicked();

private:
    Ui::Integral *ui;
    QString expression;
    void calculate(QStack<QPair<char,int> > &s_opt,QStack<double> &s_num);
    int priority(char opt);
    double calc(double x);
};

#endif // INTEGRAL_H
