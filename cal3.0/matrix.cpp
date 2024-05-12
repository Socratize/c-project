#include "matrix.h"
#include "ui_matrix.h"
#include <QDebug>

Matrix::Matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
}

Matrix::~Matrix()
{
    delete ui;
}

void Matrix::on_backButton_clicked()
{
    this->close();
    MainWindow *m=new MainWindow;
    m->show();
}

int Matrix::calcm(int n,QVector<QVector<int> >a)
{
    if(n==2) return a[0][0]*a[1][1]-a[0][1]*a[1][0];
    else
    {
        int sum=0;
        for(int k=0;k<n;k++)
        {
            QVector<QVector<int> >b;
            for(int i=1;i<n;i++)
            {
                QVector<int>c;
                for(int j=0;j<n;j++)
                {
                    if(j==k) continue;
                    c.push_back(a[i][j]);
                }
                b.push_back(c);
            }
            sum=k%2==0?sum+a[0][k]*calcm(n-1,b):sum-a[0][k]*calcm(n-1,b);
        }
        return sum;
    }
}

void Matrix::on_equalButton_clicked()
{
    QString n1,m;int n=0;
    QVector<QVector<int> >a;
    QVector<int> b;
    n1=ui->lineEdit_n->text();
    int len=n1.length();
    for(int i=0;i<len;i++)
    {
        n=n*10+(int)(n1[i].toLatin1()-'0');
    }
    m=ui->textEdit->toPlainText();
    len=m.length();
    for(int i=0;i<len;i++)
    {
        if(m[i]>='0'&&m[i]<='9')
        {
            int num=0,flag=1;
            if(i-1>=0)
                if(m[i-1]=='-') flag=-1;
            while(m[i]>='0'&&m[i]<='9')
            {
                num=num*10+(int)(m[i].toLatin1()-'0');
                i++;
            }
            num*=flag;
            b.push_back(num);
            //qDebug()<<num<<endl;
            if(b.size()==n)
            {
                a.push_back(b);
                b.clear();
            }
        }
    }
    ui->lineEdit_ans->setText(QString::number(calcm(n,a)));
//      ui->lineEdit_ans->setText(QString::number(n));
      //qDebug()<<len;


}
