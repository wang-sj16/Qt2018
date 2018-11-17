#ifndef MONEYDIGIT_H
#define MONEYDIGIT_H
#include"gameobject.h"
#include<QPixmap>
class MoneyDigit : public GameObject
{
    Q_OBJECT
public:
    MoneyDigit(int digit,qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent=nullptr);
    ~MoneyDigit(){}
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);
    void SetDigit(int digit);
    virtual void Act(int step){}
    virtual void CollideDetect(){}
private:
      int digit_;
      QPixmap* pix;
};

#endif // MONEYDIGIT_H
