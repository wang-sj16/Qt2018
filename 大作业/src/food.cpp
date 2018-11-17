#include "food.h"
#include<QDebug>


Food::Food(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent),pos_x_(pos_x),pos_y_(pos_y)
{
    g_food_number++;
    kind_="food";
    img_state_index_=g_food_state;
    setPos(pos_x_,pos_y_);
    img_x=5;
    img_y=10;
    img_= QPixmap(FOOD_PATH);
    img_matrix_=CreatePixMat(img_,img_y,img_x,width_,height_);
    real_width_=FOOD_REAL_WIDTH[g_food_state];
    real_height_=FOOD_REAL_HEIGHT[g_food_state];
}

QRectF Food::boundingRect() const
{
    QRectF outerRect = img_matrix_.at(0).at(0).rect();
    return QRectF((outerRect.width()-real_width_)/2, (outerRect.height()-real_height_)/2, real_width_, real_height_);
}
QPainterPath Food::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,img_matrix_.at(img_state_index_).at(img_index_));
}
void Food::Act(int step)
{
    if(pos_y_<660-height_/2)
    {
        if(step%3==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
        pos_y_++;
        setPos(pos_x_,pos_y_);
    }else
    {
 //       enabled_=false;
        countdown_++;
        if(countdown_>=15)
        {
            need_deleted_=true;
        }
    }
    update();
}


