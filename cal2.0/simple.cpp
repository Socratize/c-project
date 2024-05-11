#include "simple.h"
#include "ui_simple.h"
#include <math.h>
#include <cmath>
#include <QDebug>
#include "mainwindow.h"

Simple::Simple(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simple)
{
    ui->setupUi(this);
//    connect(ui->backButton,&QPushButton::clicked,this,&Simple::close);
}

Simple::~Simple()
{
    delete ui;
}

void Simple::on_DELButton_clicked()
{
    expression = ui->lineEdit->text();
    expression.chop(1);
    ui->lineEdit->setText(expression);
}

void Simple::on_ACButton_clicked()
{
    expression.clear();
    ui->lineEdit->clear();
}

void Simple::calculate(QStack<QPair<char,int> > &s_opt,QStack<double> &s_num)
{
    double a,b;
    if(s_opt.top().first == '-')
    {
        a=s_num.top();s_num.pop();
        s_opt.pop();
        if(!s_num.empty())
        {
            if(s_opt.empty()||s_num.size()==s_opt.size())
                s_opt.push(qMakePair('+',0));
        }
        s_num.push(-a);
    }
    else
    {
        a=s_num.top();s_num.pop();
        b=s_num.top();s_num.pop();
        if(s_opt.top().first=='+') s_num.push(b+a);
        else if(s_opt.top().first=='*') s_num.push(b*a);
        else if(s_opt.top().first=='/') s_num.push(b/a);
        else if(s_opt.top().first=='^') s_num.push(pow(b,a));
        s_opt.pop();
    }
}

int Simple::priority(char opt)
{
    if(opt=='(') return 0;
    else if(opt=='+'||opt=='-') return 1;
    else if(opt=='*'||opt=='/') return 2;
    else if(opt=='^') return 3;
}

void Simple::on_equalButton_clicked()
{
    expression = ui->lineEdit->text();
    QStack<double> s_num;
    QStack<QPair<char,int> > s_opt;
    int len=expression.length();
    double num;char opt;int op=0;
    for(int i=0;i<len;i++)
    {
        if(expression[i]>='0'&&expression[i]<='9')
        {
            num=0;
            while(expression[i]>='0'&&expression[i]<='9')
            {
                num=num*10+double(expression[i].toLatin1()-'0');
                i++;
            }
            if(expression[i]=='.')
            {
                i++;
                double num_pt=0,k=10;
                while(expression[i]>='0'&&expression[i]<='9')
                {
                    num_pt=num_pt+double(expression[i].toLatin1()-'0')/k;
                    k*=10;
                    i++;
                }
                num+=num_pt;
            }
            s_num.push(num);
            i--;
        }
        else
        {
            opt=expression[i].toLatin1();
//            qDebug() << opt;
            if(opt>='a'&&opt<='z')
            {
                if(opt=='q') op=1;
                if(opt=='i') op=2;
                if(opt=='o') op=3;
                if(opt=='a') op=4;
                continue;
            }
//            if(opt=='i') op=2;
            if(opt=='('||s_opt.empty())
            {
                s_opt.push(qMakePair(opt,op));//左括号
                op=0;
            }
            else if(opt==')')
            {
                while(s_opt.top().first!='(')
                    calculate(s_opt,s_num);
                if(s_opt.top().second==1)
                {
                    double a=sqrt(s_num.top());
                    s_num.pop();
                    s_num.push(a);
                }
                else if(s_opt.top().second==2)
                {
                    double a=sin(s_num.top()*M_PI/180.0);
                    s_num.pop();
                    s_num.push(a);
                }
                else if(s_opt.top().second==3)
                {
                    double a=cos(s_num.top()*M_PI/180.0);
                    s_num.pop();
                    s_num.push(a);
                }
                else if(s_opt.top().second==4)
                {
                    double a=tan(s_num.top()*M_PI/180.0);
                    s_num.pop();
                    s_num.push(a);
                }
                s_opt.pop();
            }
            else if(priority(s_opt.top().first)>=priority(opt))
            {
                while(s_opt.top().first!='(')
                {
                    calculate(s_opt,s_num);
                    if(s_opt.empty()||priority(s_opt.top().first)<priority(opt)) break;
                }
                s_opt.push(qMakePair(opt,op));
            }
            else s_opt.push(qMakePair(opt,op));
        }
    }
//    char ch=s_opt.top();

    while (!s_opt.empty()) calculate(s_opt,s_num);

    ui->lineEdit->setText(QString::number(s_num.top()));
}

void Simple::on_backButton_clicked()
{
    this->close();
    MainWindow *m=new MainWindow;
    m->show();
}
