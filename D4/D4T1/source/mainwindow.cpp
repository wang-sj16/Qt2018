#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSignalMapper *m=new QSignalMapper(this);
    connect(ui->pushButton1,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton2,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton3,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton4,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton5,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton6,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton7,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton8,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton9,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->pushButton0,SIGNAL(clicked()),m,SLOT(map()));
    m->setMapping(ui->pushButton1,1);
    m->setMapping(ui->pushButton2,2);
    m->setMapping(ui->pushButton3,3);
    m->setMapping(ui->pushButton4,4);
    m->setMapping(ui->pushButton5,5);
    m->setMapping(ui->pushButton6,6);
    m->setMapping(ui->pushButton7,7);
    m->setMapping(ui->pushButton8,8);
    m->setMapping(ui->pushButton9,9);
    m->setMapping(ui->pushButton0,0);
    connect(m, SIGNAL(mapped(int)), this, SLOT(writeText(int)));
    connect(ui->pushButton,SIGNAL(clicked()),ui->textBrowser,SLOT(clear()));
}
void MainWindow::writeText(int a)
{
    ui->textBrowser->insertPlainText(QString::number(a));
}

MainWindow::~MainWindow()
{
    delete ui;
}
