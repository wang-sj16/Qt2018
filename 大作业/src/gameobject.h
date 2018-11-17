#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"global.h"
#include <QVector>
#include <QWidget>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QTimer>

class GameObject :public QObject,public  QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    GameObject(qreal l,qreal w,QString name,QGraphicsScene *scene,QGraphicsItem *parent=nullptr);
    virtual ~GameObject(){}

    QString GetName() const;
    qreal GetWidth();
    qreal GetHeight();
    virtual void Act(int step)=0;
    virtual void CollideDetect()=0;

    bool need_deleted_=false;
    QString kind_="";
  //  bool enabled_=true;


protected:
    QString name_;
    qreal height_=0;
    qreal width_=0;
    int img_index_=0;
    int img_state_index_=0;
    QPixmap img_;
    pixmap_matrix img_matrix_;
    int img_x=0;    //图片行数
    int img_y=0;    //图片列数
    int real_width_=0;
    int real_height_=0;
   // void Vanish();
signals:
    void sgn_Deleted();

};

#endif // GAMEOBJECT_H
