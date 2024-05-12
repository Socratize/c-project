#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simple.h"
#include "integral.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tiltle
    this ->setWindowTitle("多功能计算器");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    Simple *s = new Simple;
    s->show();
//    connect(s,&Simple::subClose,this,&QMainWindow::show);
//    s->setAttribute(Qt::WA_DeleteOnClose);
//    s->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    Integral *i=new Integral;
    i->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->hide();
    Matrix *m=new Matrix;
    m->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->hide();
    Form *f=new Form;
    f->show();
}
