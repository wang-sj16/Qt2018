#include "gameobject.h"

GameObject::GameObject(qreal w,qreal h,QString name,QGraphicsScene *scene,QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    width_=w;
    height_=h;
    name_=name;
    scene->addItem(this);
    setAcceptHoverEvents(true);
}

qreal GameObject::GetHeight()
{
    return height_;
}

qreal GameObject::GetWidth()
{
    return width_;
}

QString GameObject::GetName() const
{
    return name_;
}

