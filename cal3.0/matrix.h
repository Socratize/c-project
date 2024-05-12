#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include "mainwindow.h"
#include <QVector>
#include <QString>

namespace Ui {
class Matrix;
}

class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = 0);
    ~Matrix();

private slots:
    void on_backButton_clicked();

    void on_equalButton_clicked();

private:
    Ui::Matrix *ui;
    int calcm(int n,QVector<QVector<int> >a);
    QString expression;
};

#endif // MATRIX_H
