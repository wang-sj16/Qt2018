#ifndef FISH_H
#define FISH_H
#include"gameobject.h"
#include"global.h"


class Fish : public GameObject
{
    Q_OBJECT
public:
    Fish(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    ~Fish();
    virtual void Act(int step);
    virtual void CollideDetect();
    virtual void FindTarget();
    void ProduceBonus(QString bonus_name);

    int GetCost();
    void SetSpeed(){}
    void Move();
    virtual void upgrade(){}
    qreal pos_x_,pos_y_;
    int speed_;
    int cost_;
    int countdown_=3;
    int direction_;
    int speed_x_;
    int speed_y_;
    int step_=0;
//    bool enabled_=true;
    bool isHungry=false;
    bool isDying=false;
    bool has_target_=false;
    GameObject* target_;
    int hungury_value_;
    int exp_value_=0;
private:

public slots:
    void slt_Target_Deleted();
};

class Guppy:public Fish
{
    Q_OBJECT
public:
    Guppy(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);

    void SetSpeed();

};

class SmallGuppy:public Guppy
{
    Q_OBJECT
public:
    SmallGuppy(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent=nullptr);
    virtual void upgrade();
    virtual void Act(int step);
};

class MiddleGuppy:public Guppy
{
    Q_OBJECT
public:
    MiddleGuppy(qreal l,qreal w,
                qreal pos_x,qreal pos_y,
                QString name,QGraphicsScene *scene,
                QGraphicsItem *parent=nullptr);
    virtual void upgrade();
    virtual void Act(int step);
};

class BigGuppy:public Guppy
{
public:
    BigGuppy(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent=nullptr);
    virtual void upgrade();
    virtual void Act(int step);
};



class KingGuppy:public Guppy
{
    Q_OBJECT
public:
    KingGuppy(qreal l,qreal w,
              qreal pos_x,qreal pos_y,
              QString name,QGraphicsScene *scene,
              QGraphicsItem *parent=nullptr);
};

class Breeder:public Fish
{
    Q_OBJECT
public:
    Breeder(qreal l,qreal w,
            qreal pos_x,qreal pos_y,
            QString name,QGraphicsScene *scene,
            QGraphicsItem *parent=nullptr);
    void SetSpeed();
    virtual void GiveBirth(int step);
    int birth_time_=0;
    void Act(int step);

};

class BigBreeder:public Breeder
{
    Q_OBJECT
public:
    BigBreeder(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent=nullptr);

};

class MiddleBreeder:public Breeder
{
    Q_OBJECT
public:
    MiddleBreeder(qreal l,qreal w,
                  qreal pos_x,qreal pos_y,
                  QString name,QGraphicsScene *scene,
                  QGraphicsItem *parent=nullptr);
    virtual void upgrade();
    virtual void Act(int step);

};

class Carnivore:public Fish
{
    Q_OBJECT
public:
    Carnivore(qreal l,qreal w,
              qreal pos_x,qreal pos_y,
              QString name,QGraphicsScene *scene,
              QGraphicsItem *parent=nullptr);
    void SetSpeed();
    //virtual  void FindTarget();
    //virtual void CollideDetect();
    //   virtual void Act(int step);


};

class Gekko:public Fish
{
    Q_OBJECT
public:
    Gekko(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);
    void SetSpeed();
    //    virtual void Act(int step);
    //virtual  void FindTarget();
    //virtual  void CollideDetect();
};

class Grubber:public Fish
{
    Q_OBJECT
public:
    Grubber(qreal l,qreal w,
            qreal pos_x,qreal pos_y,
            QString name,QGraphicsScene *scene,
            QGraphicsItem *parent=nullptr);
    void SetSpeed();
      virtual void Act(int step);
    //   virtual void Act(int step);
    //virtual  void FindTarget();
    //virtual  void CollideDetect();
};


class Ulturavore:public Fish
{
    Q_OBJECT
public:
    Ulturavore(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent=nullptr);
    void SetSpeed();
    // virtual void Act(int step);
    //virtual  void FindTarget();
    //virtual  void CollideDetect();
};

#endif // FISH_H
