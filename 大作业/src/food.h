#ifndef FOOD_H
#define FOOD_H
#include"gameobject.h"

class Food:public GameObject
{
    Q_OBJECT
public:
    Food(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual void Act(int step);
    virtual void CollideDetect(){}
    ~Food(){g_food_number--;}
private:
    qreal pos_x_,pos_y_;
    //bool enabled_=true;
    int countdown_=0;
};

#endif // FOOD_H
