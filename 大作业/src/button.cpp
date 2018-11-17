#include "button.h"
#include "global.h"
Button::Button(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent)
{
    kind_="button";
    price_=BTNS_COST[name_];
    img_state_index_=0;
    setPos(pos_x,pos_y);

    if(name_=="egg")
    {
        img_x=3;
        img_y=3;
    }else if(name_=="moreFood")
    {
        img_x=6;
        img_y=3;
    }else
    {
        img_x=1;
        img_y=3;
    }
    img_= QPixmap(BTN_PATH[name_]);
    img_matrix_=CreatePixMat(img_,img_y,img_x,width_,height_);


}
QRectF Button::boundingRect() const
{
    return img_matrix_.at(0).at(0).rect();
}
QPainterPath Button::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,img_matrix_.at(img_state_index_).at(img_index_));
}
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    if(name_=="foodUpgrade"&&g_food_state==4)
    {
        img_index_=2;
    }else{img_index_ = 1;}
    update();
}


void Button:: hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    if(name_=="foodUpgrade"&&g_food_state==4)
    {
        img_index_=2;
    }else
    {img_index_=0;}
    update();
}
void Button:: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&g_current_money>=price_)
    {
        event->accept();
        g_current_money-=price_;
        qDebug()<<"current money:"<<g_current_money;
        img_index_ = 2;
        if (name_ == "moreFood")
        {
            if (img_state_index_ < 5)
            {
                img_state_index_++;
                g_max_food++;
            }
        }
        else if (name_ == "egg")
        {
            if (img_state_index_ < 2)
            {
                img_state_index_++;
            }
        }
        update();
        emit sgn_ReleaseButton(name_);

    } else
    {
        event->ignore();
    }
}

void Button:: mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    if(name_=="foodUpgrade"&&g_food_state==4)
    {
        img_index_=2;
    }else
    {img_index_ = 1;}

    update();

}

void Button::Act(int step)
{
    //qDebug()<<"Button act";
}
