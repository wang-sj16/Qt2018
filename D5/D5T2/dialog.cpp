#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QString>
#include<QByteArray>
#include<QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(setDate()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setDate()
{
    //从输入获取日期
    year=ui->lineEdit->text().toInt();
    month=ui->lineEdit_2->text().toInt();
    day=ui->lineEdit_3->text().toInt();

    //如果输入合法设置QMessageBox输出格式
    if(isReg(year,month,day))
    {
        QString str="Date: "+QString::number(year)+" ."+QString::number(month)+" ."+QString::number(day);
        char*  date;
        QByteArray ba = str.toLatin1();
        date=ba.data();
        QMessageBox msgBox(QMessageBox::NoIcon,"Date", date);
        msgBox.exec();
    }else    //如果输出不合法 弹出警告
    {
        QMessageBox msgBox(QMessageBox::NoIcon,"Warning", "Input is Invalid!");
        msgBox.exec();
    }
}

bool Dialog::isReg(int year, int month, int day)
{
    if(year>=0&&month>=1&&month<=12&&day>=1&&day<=31)     //判断输入日期格式是否合法
    {
        if((year%4==0&&year%100!=0)||(year%400==0))           //判断闰年
        {
            qDebug()<<"闰年"<<endl;
            if(month==2&&day>=30){return false;}             //闰年2月有29天
            else{return true;}
        }
        else
        {
            qDebug()<<"不是闰年"<<endl;
            if(month==2&&day>=28){return false;}             //非闰年2月有28天
        }

        if((month==4||month==6||month==9||month==11)&&day==31){return false;}     //判断大小月
        return true;
    }else {return false;}
}
