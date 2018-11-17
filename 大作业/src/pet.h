#ifndef PET_H
#define PET_H
#include"gameobject.h"
#include"global.h"
#define WAITING 0
#define IS_OPENING 1
#define OPEN 2
#define IS_CLOSING 3
#define TURNING_LEFT 2
#define NOT_TURING 0
#define TURNING_RIGHT 1
#define MOVING 1
#define STOPPING 2
class Pet :public GameObject
{
    Q_OBJECT
public:
    Pet(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    qreal pos_x_,pos_y_;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual void Act(int step);
    virtual void CollideDetect(){}
    ~Pet(){}
};



class Stinky:public Pet
{
    Q_OBJECT
public:
    Stinky(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect();
    int speed_x_=0;
    int direction_=0;
    int move_status_=MOVING;
};


class Clyde:public Pet
{
    Q_OBJECT
public:
    Clyde(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect();
    void FindTarget();
    int speed_x_=0;
    int speed_y_=0;
    int direction_=0;
    int speed_=0;
    bool has_target_=false;
    GameObject* target_;
public slots:
  void  slt_Target_Deleted();
};


class Meryl:public Pet
{
    Q_OBJECT
public:
    Meryl(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect(){}
    int speed_x_=0;
    int speed_y_=0;
    int direction_=0;
    int speed_=0;
};


class Niko:public Pet
{
    Q_OBJECT
public:
    Niko(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect(){}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    int status=WAITING;
    int step_=0;
    int count_num_=10;
};


class Prego:public Pet
{
    Q_OBJECT
public:
    Prego(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect(){}
    int speed_x_=0;
    int speed_y_=0;
    int direction_=0;
    int speed_=6;
};


class Vert:public Pet
{
    Q_OBJECT
public:
    Vert(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);
    virtual void Act(int step);
    virtual void CollideDetect(){}
    int speed_x_=0;
    int speed_y_=0;
    int direction_=0;
    int speed_=6;
};

#endif // PET_H
