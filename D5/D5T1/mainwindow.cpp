#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    ui->textEdit_2->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{

    if(obj==ui->textEdit)
    {
        if(event->type()==QEvent::KeyPress)             //判定事件种类
        {
            QKeyEvent *keyEvent =(QKeyEvent*)event;
            if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            {
                ui->textEdit_2->append(ui->textEdit->toPlainText());
                ui->textEdit->setText("");
                return true;
            }
            else {return false;}
        }
        else {return false;}
    }else
    {
        return QMainWindow::eventFilter(obj,event);       //返回主程序
    }
}

