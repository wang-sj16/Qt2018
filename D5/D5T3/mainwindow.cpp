#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIcon>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QIcon button_icon1(":/rc/1.png");
    ui->setupUi(this);
    ui->pushButton->setIcon(button_icon1);
    ui->pushButton->setIconSize(QSize(200,200));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Icon_Change()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Icon_Change()
{
    index++;
    QIcon button_icon1(":/rc/1.png");
    QIcon button_icon2(":/rc/2.png");
    QIcon button_icon3(":/rc/3.png");
    QIcon button_icon4(":/rc/4.png");
    QIcon button_icon5(":/rc/5.png");
    QIcon button_icon6(":/rc/6.png");
    QIcon button_icon7(":/rc/7.png");
    QIcon button_icon8(":/rc/8.png");
    QIcon button_icon9(":/rc/9.png");
    QIcon button_icon10(":/rc/10.png");
    QIcon button_icon11(":/rc/11.png");
    QIcon button_icon12(":/rc/12.png");
    QIcon Array[]={button_icon1,button_icon2,button_icon3,button_icon4,
                   button_icon5,button_icon6,button_icon7,button_icon8,
                   button_icon9,button_icon10,button_icon11,button_icon12};
    ui->pushButton->setIcon(Array[index%12]);
    ui->pushButton->setIconSize(QSize(200,200));
}
