#include "alien.h"
#include "bonus.h"
Alien::Alien(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent),pos_x_(pos_x),pos_y_(pos_y)
{
    g_alien_amount++;
    img_state_index_=0;
    setPos(pos_x_,pos_y_);
    img_= QPixmap(ALIENS_PATH[name]);
    real_width_=ALIENS_REAL_WIDTH[name_];
    real_height_=ALIENS_REAL_HEIGHT[name_];
    if(name_=="psychosquid")
    {
        pixmap_matrix pix_mat1=CreatePixMat(img_,10,4,160,160);
        pixmap_array red_to_left;
        pixmap_array red_to_right;
        pixmap_array red_turn_left;
        pixmap_array red_turn_right;
        pixmap_array blue_to_left;
        pixmap_array blue_to_right;
        pixmap_array blue_turn_left;
        pixmap_array blue_turn_right;
        for(int i=0;i<10;i++)
        {
            red_to_left.append(pix_mat1[0][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            QImage mirror_img=pix_mat1[0][i].toImage().mirrored(true,false);
            QPixmap temp=QPixmap::fromImage(mirror_img).scaled(160,160,Qt::KeepAspectRatioByExpanding);
            red_to_right.append(temp);

            red_turn_right.append(pix_mat1[1][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            red_turn_left.append(pix_mat1[1][9-i].scaled(160,160,Qt::KeepAspectRatioByExpanding));

            blue_to_left.append(pix_mat1[2][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            QImage mirror_img1=pix_mat1[2][i].toImage().mirrored(true,false);
            QPixmap temp1=QPixmap::fromImage(mirror_img1).scaled(160,160,Qt::KeepAspectRatioByExpanding);
            blue_to_right.append(temp1);

            blue_turn_right.append(pix_mat1[3][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            blue_turn_left.append(pix_mat1[3][9-i].scaled(160,160,Qt::KeepAspectRatioByExpanding));

        }
        img_matrix_.append(red_to_left);
        img_matrix_.append(red_to_right);
        img_matrix_.append(red_turn_left);
        img_matrix_.append(red_turn_right);
        img_matrix_.append(blue_to_left);
        img_matrix_.append(blue_to_right);
        img_matrix_.append(blue_turn_left);
        img_matrix_.append(blue_turn_right);
    }
    else
    {
        pixmap_matrix pix_mat1=CreatePixMat(img_,10,2,160,160);
        pixmap_array to_left;
        pixmap_array to_right;
        pixmap_array turn_left;
        pixmap_array turn_right;
        for(int i=0;i<10;i++)
        {
            to_left.append(pix_mat1[0][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            QImage mirror_img=pix_mat1.at(0).at(i).toImage().mirrored(true,false);
            QPixmap temp=QPixmap::fromImage(mirror_img).scaled(160,160,Qt::KeepAspectRatioByExpanding);
            to_right.append(temp);

            turn_right.append(pix_mat1[1][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
            turn_left.append(pix_mat1[1][9-i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
        }
        img_matrix_.append(to_left);
        img_matrix_.append(to_right);
        img_matrix_.append(turn_left);
        img_matrix_.append(turn_right);
    }
}
QRectF Alien::boundingRect() const
{
    QRectF outerRect = img_matrix_.at(0).at(0).rect();
    return QRectF((outerRect.width()-real_width_)/2, (outerRect.height()-real_height_)/2, real_width_, real_height_);
}
QPainterPath Alien::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Alien::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,img_matrix_.at(img_state_index_).at(img_index_));
}

void Alien::FindTarget()
{
    QList<GameObject*> target_items;
    foreach (QGraphicsItem *item, scene()->items())
    {
        GameObject*gm=dynamic_cast<GameObject*>(item);
        if(name_=="gus")
        {
            if((gm->kind_=="food"||gm->kind_=="fish")&&gm->isVisible())
            {
                target_items.push_back(gm);
            }
        }else
        {
            if(gm->kind_=="fish"&&gm->isVisible())
            {
                target_items.push_back(gm);
            }
        }

    }
    if(!target_items.empty())
    {
        target_=target_items[0];
        has_target_=true;
        connect(target_,SIGNAL(sgn_Deleted()),this,SLOT(slt_Target_Deleted()));
        //增加信号槽  表示失去目标
    }
}

void Alien::CollideDetect()
{
    if(has_target_)
    {
        foreach (QGraphicsItem *item, collidingItems())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(name_=="gus")
            {
                if(gm->kind_=="food"&&gm->isVisible())
                {
                    Food * food=dynamic_cast<Food*>(item);
                   // food->enabled_=false;
                    food->need_deleted_=true;
                    food->setVisible(false);
                    health_-=10;

                    emit food->sgn_Deleted();
                }else if(gm->kind_=="fish"&&gm->isVisible())
                {
                    Fish * fish=dynamic_cast<Fish*>(item);
                  //  fish->enabled_=false;
                    fish->need_deleted_=true;
                    fish->setVisible(false);
                    health_-=20;
                    emit fish->sgn_Deleted();
                }
            }
            else
            {
                if(gm->kind_=="fish"&&gm->isVisible())
                {
                    Fish * fish=dynamic_cast<Fish*>(item);
                  //  fish->enabled_=false;
                    fish->need_deleted_=true;
                    fish->setVisible(false);
                    emit fish->sgn_Deleted();
                }
            }
        }
    }
}

void Alien::slt_Target_Deleted()
{
   // qDebug()<<"slot调用";
    target_=nullptr;
    has_target_=false;
}

void Alien::Act(int step)
{
    if(health_<=0)
    {
        AlienDie();
    }
    CollideDetect();

    if(has_target_)
    {

        //  qDebug()<<name_<<"has target"<<target_->x()<<target_->y();
        if(step%10==0)
        {
            qreal delta_x=(pos_x_-target_->pos().x());
            qreal delta_y=(pos_y_-target_->pos().y());
            qreal cos_theta=-delta_x/sqrt(delta_x*delta_x+delta_y*delta_y);
            qreal sin_theta=-delta_y/sqrt(delta_x*delta_x+delta_y*delta_y);
            speed_x_=speed_*cos_theta;
            speed_y_=speed_*sin_theta;
        }
    }
    else{
        if(step%120==0)
        {
            direction_=random(360);
            speed_x_ = speed_*cos(direction_*3.1416/180);
            speed_y_ = speed_*sin(direction_*3.1416/180);
        }
    }
    if(pos_x_<=5 && speed_x_<0)
    {
        speed_x_= -speed_x_;
    }
    if(pos_x_> (SCREEN_WIDTH-real_width_) && speed_x_>=0)
    {
        speed_x_= -speed_x_;
    }
    if(pos_y_<80 && speed_y_<0)
    {
        speed_y_= -speed_y_;
    }
    if(pos_y_> 660-real_height_ && speed_y_>=0)
    {
        speed_y_= -speed_y_;
    }

    if(step%3==0)
    {
        pos_x_+=speed_x_;
        pos_y_+=speed_y_;
        setPos(pos_x_,pos_y_);
    }
    if(!has_target_)
    {
        FindTarget();
    }
    if(name_!="psychosquid")
    {
        if(speed_x_>=0){img_state_index_=1;}
        else{img_state_index_=0;}
    }else
    {
        if(step%500>=300&&speed_x_>=0)
        {
            img_state_index_=5;
        }else if(step%500>=300&&speed_x_<0)
        {
            img_state_index_=4;
        }
        else if(step%500<300&&speed_x_>=0)
        {
            img_state_index_=1;
        }
        else if(step%500<300&&speed_x_<0)
        {
            img_state_index_=0;
        }
    }
    if(step%3==0)
    {
        img_index_++;
        img_index_=img_index_%10;
    }
    update();

}

void Alien::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&name_!="gus")
    {
        event->accept();
        if(name_=="psychosquid")
        {
            if(img_state_index_>=4)
            {
                health_+=20;
            }else
            {
                health_-=10;
            }
        }
        else
        {
            health_-=10;
        }
        update();

    } else
    {
        event->ignore();
    }
}

void Alien::AlienDie()
{
    if(isVisible())
    {Bonus*bonus=new Bonus(72,72,pos_x_,pos_y_+height_/2,"diamond",scene());}
    setVisible(false);
    need_deleted_=true;

    setPos(-1,-1);
}

Balrog::Balrog(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent)
    :Alien(l,w,pos_x,pos_y,name,scene,parent)
{
    speed_=7;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}



Gus::Gus(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent)
    :Alien(l,w,pos_x,pos_y,name,scene,parent)
{
    speed_=6;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}



Psychosquid::Psychosquid(qreal l,qreal w,
                         qreal pos_x,qreal pos_y,
                         QString name,QGraphicsScene *scene,
                         QGraphicsItem *parent)
    :Alien(l,w,pos_x,pos_y,name,scene,parent)
{
    speed_=7;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}



Sylv::Sylv(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent)
    :Alien(l,w,pos_x,pos_y,name,scene,parent)
{
    speed_=7;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}




