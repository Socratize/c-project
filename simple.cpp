#include "simple.h"
#include "ui_simple.h"
#include <math.h>
#include <QDebug>
Simple::Simple(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simple)
{
    ui->setupUi(this);
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

void Simple::calculate(QStack<char> &s_opt,QStack<double> &s_num)
{
    double a,b;
    if(s_opt.top() == '-')
    {
        a=s_num.top();s_num.pop();
        s_opt.pop();
        if(!s_num.empty())
        {
            if(s_opt.empty()||s_num.size()==s_opt.size())
                s_opt.push('+');
        }
        s_num.push(-a);
    }
    else
    {
        a=s_num.top();s_num.pop();
        b=s_num.top();s_num.pop();
        if(s_opt.top()=='+') s_num.push(b+a);
        else if(s_opt.top()=='*') s_num.push(b*a);
        else if(s_opt.top()=='/') s_num.push(b/a);
        else if(s_opt.top()=='^') s_num.push(pow(b,a));
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
    //ui->lineEdit->clear();
    expression = ui->lineEdit->text();
    QStack<double> s_num;
    QStack<char> s_opt;
    int len=expression.length();
    double num;char opt;
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
            s_num.push(num);
            i--;

        }
        else
        {
            opt=expression[i].toLatin1();
//            qDebug() << opt;
            if(opt=='('||s_opt.empty()) s_opt.push(opt);//左括号
            else if(opt==')')
            {
                while(s_opt.top()!='(')
                    calculate(s_opt,s_num);
                s_opt.pop();
            }
            else if(priority(s_opt.top())>=priority(opt))
            {
                while(s_opt.top()!='(')
                {
                    calculate(s_opt,s_num);
                    if(s_opt.empty()||priority(s_opt.top())<priority(opt)) break;
                }
                s_opt.push(opt);
            }
            else s_opt.push(opt);
        }
    }
//    char ch=s_opt.top();

    while (!s_opt.empty()) calculate(s_opt,s_num);

    ui->lineEdit->setText(QString::number(s_num.top(),'f',3));
}
