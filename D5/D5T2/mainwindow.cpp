#include "mainwindow.h"
#include"dialog.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *pMenuA=new QMenu("Settings");
    QAction* pActionA = new QAction("Set Time");
    pMenuA->addAction(pActionA);
    ui->menuBar->addMenu(pMenuA);
    connect(pActionA,SIGNAL(triggered(bool)),this,SLOT(showDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDialog()
{
    Dialog dlg;
    dlg.exec();
}
