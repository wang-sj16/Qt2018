#ifndef BONUS_H
#define BONUS_H
#include"gameobject.h"

class Bonus:public GameObject

{
    Q_OBJECT
public:
    Bonus(qreal l,qreal w,
          qreal pos_x,qreal pos_y,
          QString name,QGraphicsScene *scene,
          QGraphicsItem *parent=nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    ~Bonus(){}

    virtual void Act(int step);
    virtual void CollideDetect(){}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
  //  bool enabled_=true;
    int value_=0;
private:
    qreal pos_x_,pos_y_;
    int countdown_=0;
};


#endif // BONUS_H
