#ifndef BUTTON_H
#define BUTTON_H


#include"gameobject.h"
class Button :public GameObject
{
    Q_OBJECT
public:
    Button(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent=nullptr);
    ~Button(){}
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    virtual void Act(int step);
    virtual void CollideDetect(){}
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int price_=0;
signals:
    void sgn_ReleaseButton(QString);
private:
    //QString name_;
    //pixmap_array img_array_;
    // QPixmap img_;
    // pixmap_matrix img_matrix_;

    // int img_x;   //图片行数
    //  int img_y;   //图片列数

    //  int img_index_;
};

#endif // BUTTON_H
