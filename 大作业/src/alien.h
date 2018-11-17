#ifndef ALIEN_H
#define ALIEN_H
#include"gameobject.h"
#include"fish.h"
#include"food.h"
class Alien:public GameObject
{
    Q_OBJECT
public:
    Alien(qreal w,qreal h,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    ~Alien(){g_alien_amount--;}
    virtual void Act(int step);
    virtual void CollideDetect();
    void FindTarget();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void AlienDie();

    qreal pos_x_,pos_y_;
    int speed_=0;
    int cost_;
    int countdown_;
    int direction_=0;
    int speed_x_=0;
    int speed_y_=0;
   // bool enabled_=true;
    bool has_target_=false;
    int health_=ALIENS_MAX_HEALTH[name_];
    GameObject* target_;

public slots:
    void slt_Target_Deleted();
};


//——————————————————Balrog————————  —————————//


class Balrog:public Alien
{
    Q_OBJECT

public:
    Balrog(qreal w,qreal h,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent=nullptr);
};


//————————————————————Gus——————————————————//


class Gus:public Alien
{
    Q_OBJECT

public:
    Gus(qreal w,qreal h,
        qreal pos_x,qreal pos_y,
        QString name,QGraphicsScene *scene,
        QGraphicsItem *parent=nullptr);
};


//——————————————————Psychosquid——————————————//


class Psychosquid:public Alien
{
    Q_OBJECT
public:
    Psychosquid(qreal w,qreal h,
                qreal pos_x,qreal pos_y,
                QString name,QGraphicsScene *scene,
                QGraphicsItem *parent=nullptr);
};


//————————————————Sylv————————————————————————//


class Sylv:public Alien
{
    Q_OBJECT

public:
    Sylv(qreal w,qreal h,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);
    //  virtual void Act(int step);
};



#endif // ALIEN_H
