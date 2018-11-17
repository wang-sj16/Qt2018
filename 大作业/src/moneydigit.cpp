#include "moneydigit.h"

MoneyDigit::MoneyDigit(int digit,qreal l,qreal w,
       qreal pos_x,qreal pos_y,
       QString name,QGraphicsScene *scene,
       QGraphicsItem *parent) :GameObject(l,w,name,scene,parent)
{
    digit_=digit;
    pix=new QPixmap(DIGIT_PATH[digit]);
    setPos(pos_x,pos_y);
}
QRectF MoneyDigit::boundingRect() const
{
    return pix->rect();
}
QPainterPath MoneyDigit::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
void MoneyDigit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,pix->scaled(width_, height_, Qt::KeepAspectRatioByExpanding));
}
void MoneyDigit::SetDigit(int digit)
{
    digit_=digit;
}
