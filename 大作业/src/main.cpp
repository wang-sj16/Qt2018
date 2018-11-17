#include "insaniquarium.h"
#include"global.h"
#include <QApplication>
#include<QMovie>
#include<QDesktopWidget>
#include<QTime>
#include<QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget w;
    QMovie *movie;
    movie = new QMovie(LOADING_PATH);
    QLabel *label = new QLabel;
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->setStyleSheet("background:transparent");
    label->setMovie(movie);
    label->setScaledContents(true);
    label->setGeometry((w.width() - 256) / 2 ,
                       (w.height() - 256) / 2 ,
                       256, 256);
    movie->start();
    label->show();
    QTime t;
    t.start();
    while (t.elapsed() < 2000){
        QApplication::processEvents();
    }
    label->close();
    delete movie;
    delete label;

    Insaniquarium app;
    app.show();
    return a.exec();
}
