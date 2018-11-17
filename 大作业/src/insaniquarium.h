#ifndef INSANIQUARIUM_H
#define INSANIQUARIUM_H
#include"moneydigit.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include<QTimer>
#include<QEvent>
#include<QSet>
#include<QGraphicsSimpleTextItem>
#include<QMediaPlayer>
#include<QList>
class Insaniquarium : public QGraphicsView
{
    Q_OBJECT

public:
    Insaniquarium(QWidget *parent = nullptr);
    ~Insaniquarium();
private:

    QGraphicsScene *scene_;
    QTimer *timer_;
    QSet<QString> chosen_pets_;
    QMediaPlayer* player_;
    QList <MoneyDigit*> money_list_;
    void StartScene();
    void ChoosePetScene();
    void MainGameScene();
    void RestartScene();
    void NextLevelScene();
    void SetMainUI();
    void Act(int step);
    void mousePressEvent(QMouseEvent *event);
    void ProduceFish(QString name,int x,int y);
  //  void SetMoneyBoard();

    bool during_game_=false;
    bool feedable_=true;
    int step_=0;

signals:
    void sgn_GameOver();
public slots:
    void slt_onClickButton(QString btn_name);
    void slt_onTimeOut();
    void slt_onGameOver();
};

#endif // INSANIQUARIUM_H
