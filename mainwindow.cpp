#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simple.h"

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
    this->close();
    s = new Simple();
    s->show();
}
