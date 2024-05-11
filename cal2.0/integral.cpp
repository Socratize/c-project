#include "integral.h"
#include "ui_integral.h"
#include "mainwindow.h"
#include <math.h>

Integral::Integral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Integral)
{
    ui->setupUi(this);
}

Integral::~Integral()
{
    delete ui;
}

void Integral::on_pushButton_back_clicked()
{
    this->close();
    MainWindow *m=new MainWindow;
    m->show();
}

void Integral::calculate(QStack<QPair<char,int> > &s_opt,QStack<double> &s_num)
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

int Integral::priority(char opt)
{
    if(opt=='(') return 0;
    else if(opt=='+'||opt=='-') return 1;
    else if(opt=='*'||opt=='/') return 2;
    else if(opt=='^') return 3;
}

double Integral::calc(double x)
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
        else if(expression[i]=='x')
        {
            s_num.push(x);
        }
        else
        {
            opt=expression[i].toLatin1();
            if(opt>='a'&&opt<='z')
            {
                if(opt=='q') op=1;
                if(opt=='i') op=2;
                if(opt=='o') op=3;
                if(opt=='a') op=4;
                continue;
            }
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

    while (!s_opt.empty()) calculate(s_opt,s_num);
    return s_num.top();
}

void Integral::on_pushButton_poi_clicked()
{
    QString a,b;
    a=ui->lineEdit_up->text();
    b=ui->lineEdit_down->text();
    int cnt=0;
    double up=0,down=0;
    while(a[cnt]>='0'&&a[cnt]<='9')
    {
        up=up*10+(double)(a[cnt].toLatin1()-'0');
        cnt++;
    }
    if(a[cnt]=='.')
    {
        cnt++;
        double up_pt=0,k=10;
        while(a[cnt]>='0'&&a[cnt]<='9')
        {
            up_pt=up_pt+double(a[cnt].toLatin1()-'0')/k;
            k*=10;
            cnt++;
        }
        up+=up_pt;
    }
    cnt=0;
    while(b[cnt]>='0'&&b[cnt]<='9')
    {
        down=down*10+(double)(b[cnt].toLatin1()-'0');
        cnt++;
    }
    if(b[cnt]=='.')
    {
        cnt++;
        double down_pt=0,k=10;
        while(b[cnt]>='0'&&b[cnt]<='9')
        {
            down_pt=down_pt+double(b[cnt].toLatin1()-'0')/k;
            k*=10;
            cnt++;
        }
        down+=down_pt;
    }
    const int N=100000;
    double dx=(down-up)/N,sum=0,x=up;
    for(int i=1;i<=N;i++)
    {
        sum+=calc((x+x+dx)/2);
        x+=dx;
    }
    sum*=dx;
    ui->lineEdit_ans->setText(QString::number(sum));
}

