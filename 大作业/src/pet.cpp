#include "pet.h"
#include"bonus.h"
#include"fish.h"
#include"bonus.h"
#include<QMediaPlayer>
#include<QImage>

#define WAITING 0
#define IS_OPENING 1
#define OPEN 2
#define IS_CLOSING 3

Pet::Pet(qreal l,qreal w,
         qreal pos_x,qreal pos_y,
         QString name,QGraphicsScene *scene,
         QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent),pos_x_(pos_x),pos_y_(pos_y)
{
    img_state_index_=0;
    setPos(pos_x_,pos_y_);
    img_= QPixmap(PETS_PATH[name]);

    real_width_=PETS_REAL_WIDTH[name_];
    real_height_=PETS_REAL_HEIGHT[name_];
}

QRectF Pet::boundingRect() const
{
    QRectF outerRect = img_matrix_.at(0).at(0).rect();
    return QRectF((outerRect.width()-real_width_)/2, (outerRect.height()-real_height_)/2, real_width_, real_height_);
}
QPainterPath Pet::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Pet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,img_matrix_.at(img_state_index_).at(img_index_));
}

void Pet::Act(int step)
{

}


Clyde::Clyde(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    img_matrix_=CreatePixMat(img_,10,1,80,80);
    img_state_index_=0;

    speed_=7;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}

void Clyde::Act(int step)
{
    if(step%3==0)
    {
        img_index_++;
        img_index_=img_index_%10;
    }

    if(has_target_)
    {
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
    else
    {
        if(step%120==0)
        {
            direction_=random(360);
            speed_x_=speed_*cos(direction_*3.1416/180);
            speed_y_=speed_*sin(direction_*3.1416/180);
        }
    }


    if(pos_x_<=width_/2+width_/2&&speed_x_<0)
    {
        speed_x_=-speed_x_;
    }
    if(pos_x_>SCREEN_WIDTH-width_/2&&speed_x_>0)
    {
        speed_x_=-speed_x_;
    }
    if(pos_y_<+height_/2&&speed_y_<0)
    {
        speed_y_=-speed_y_;
    }
    if(pos_y_>660-height_/2&&speed_y_>0)
    {
        speed_y_=-speed_y_;
    }

    if(step%3==0)
    {
        pos_x_+=speed_x_;
        pos_y_+=speed_y_;
        setPos(pos_x_,pos_y_);
    }


    if(has_target_&&!target_->isVisible())
    {
        target_=nullptr;
        has_target_=false;
        // qDebug()<<"lose target";
    }
    if(!has_target_)
    {
        FindTarget();
    }
    CollideDetect();
    update();
}

void Clyde::FindTarget()
{
    QVector<GameObject*> edible_items;
    foreach (QGraphicsItem *item, scene()->items())
    {
        GameObject*gm=dynamic_cast<GameObject*>(item);
        if(gm->kind_=="bonus"&&gm->isVisible())
        {
            edible_items.append(gm);
        }
    }
    if(!edible_items.empty())
    {
        target_=edible_items[0];
        has_target_=true;
        //  qDebug()<<"find target";
        //增加信号槽  表示失去目标
        connect(target_,SIGNAL(sgn_Deleted()),this,SLOT(slt_Target_Deleted()));
    }
}

void Clyde::slt_Target_Deleted()
{
    qDebug()<<"slot调用";
    target_=nullptr;
    has_target_=false;
}

void Clyde::CollideDetect()
{

    if(has_target_)
    {
        foreach (QGraphicsItem *item, collidingItems())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->kind_=="bonus"&&gm->isVisible())
            {
                Bonus * bonus=dynamic_cast<Bonus*>(item);
              //  bonus->enabled_=false;
                bonus->need_deleted_=true;
                bonus->setVisible(false);
                g_current_money+=bonus->value_;
                qDebug()<<g_current_money;
                emit bonus->sgn_Deleted();
            }
        }
    }
}

Meryl::Meryl(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    pixmap_matrix pix_mat1=CreatePixMat(img_,10,2,80,80);
    pixmap_array to_left;
    pixmap_array to_right;
    pixmap_array turn_left;
    pixmap_array turn_right;
    for(int i=0;i<10;i++)
    {
        to_left.append(pix_mat1[0][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        QImage mirror_img=pix_mat1.at(0).at(i).toImage().mirrored(true,false);
        QPixmap temp=QPixmap::fromImage(mirror_img).scaled(80,80,Qt::KeepAspectRatioByExpanding);
        to_right.append(temp);

        turn_right.append(pix_mat1[1][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        turn_left.append(pix_mat1[1][9-i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
    }
    img_matrix_.append(to_left);
    img_matrix_.append(to_right);
    img_matrix_.append(turn_left);
    img_matrix_.append(turn_right);

    img_state_index_=0;

    speed_=6;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}

void Meryl::Act(int step)
{
    if(step%120==0)
    {
        direction_=random(360);
        speed_x_ = speed_*cos(direction_*3.1416/180);
        speed_y_ = speed_*sin(direction_*3.1416/180);
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
    if(speed_x_>0){img_state_index_=1;}
    else{img_state_index_=0;}
    if(step%2==0)
    {
        img_index_++;
        img_index_=img_index_%10;
    }
    if(step%100==0)
    {
        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->kind_=="fish"&&gm->isVisible())
            {
                dynamic_cast<Fish*>(item)->ProduceBonus(FISHES_TO_BONUS[gm->GetName()]);
                dynamic_cast<Fish*>(item)->ProduceBonus(FISHES_TO_BONUS[gm->GetName()]);

            }
        }
    }
    update();

}


Niko::Niko(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    img_matrix_=CreatePixMat(img_,10,2,80,80);
}




void Niko::Act(int step)
{
    step_++;
    if(step_%150==0&&status==WAITING)
    {
        status=IS_OPENING;
        count_num_=0;
    }
    if(status==IS_OPENING&&img_index_<9)
    {
        img_state_index_=0;
        count_num_++;
        if(count_num_%3==0)
        {
            img_index_++;
        }
        if(img_index_==9)
        {
            status=OPEN;
        }

    }
    if(status==IS_CLOSING&&img_index_>0)
    {
        img_state_index_=1;
        count_num_++;
        if(count_num_%3==0)
        {
            img_index_--;
        }
        if(img_index_==0)
        {
            status=WAITING;
            step_=0;
        }
    }
    update();

}

void Niko:: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&status==OPEN)
    {
        event->accept();
        g_current_money+=BONUS_VALUE["pearl"];
        qDebug()<<"current money:"<<g_current_money;
        status=IS_CLOSING;
        update();
    } else
    {
        event->ignore();
    }
}

Prego::Prego(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    pixmap_matrix pix_mat1=CreatePixMat(img_,10,2,80,80);
    pixmap_array to_left;
    pixmap_array to_right;
    pixmap_array turn_left;
    pixmap_array turn_right;
    for(int i=0;i<10;i++)
    {
        to_left.append(pix_mat1[0][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        QImage mirror_img=pix_mat1.at(0).at(i).toImage().mirrored(true,false);
        QPixmap temp=QPixmap::fromImage(mirror_img).scaled(80,80,Qt::KeepAspectRatioByExpanding);
        to_right.append(temp);

        turn_right.append(pix_mat1[1][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        turn_left.append(pix_mat1[1][9-i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
    }
    img_matrix_.append(to_left);
    img_matrix_.append(to_right);
    img_matrix_.append(turn_left);
    img_matrix_.append(turn_right);

    img_state_index_=0;

    speed_=6;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);

}

void Prego::Act(int step)
{
    if(step%140==0)
    {
        direction_=random(360);
        speed_x_ = speed_*cos(direction_*3.1416/180);
        speed_y_ = speed_*sin(direction_*3.1416/180);
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
    if(speed_x_>0){img_state_index_=1;}
    else{img_state_index_=0;}
    if(step%2==0)
    {
        img_index_++;
        img_index_=img_index_%10;
    }

    if(step%220==0)
    {
        SmallGuppy *sm=new SmallGuppy(80,80,pos_x_,pos_y_+real_height_/2,"smallGuppy",scene());
        // Bonus*bonus=new Bonus(72,72,pos_x_,pos_y_-width_/2,"gold",scene());
    }
    update();
}


Stinky::Stinky(qreal l,qreal w,
               qreal pos_x,qreal pos_y,
               QString name,QGraphicsScene *scene,
               QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    pixmap_matrix pix_mat1=CreatePixMat(img_,10,3,80,80);
    pixmap_array to_left;
    pixmap_array to_right;
    pixmap_array stop_left;
    pixmap_array stop_right;
    for(int i=0;i<10;i++)
    {
        to_left.append(pix_mat1[0][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        QImage mirror_img=pix_mat1.at(0).at(i).toImage().mirrored(true,false);
        QPixmap temp=QPixmap::fromImage(mirror_img).scaled(80,80,Qt::KeepAspectRatioByExpanding);
        to_right.append(temp);

        stop_left.append(pix_mat1[2][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        QImage mirror_img1=pix_mat1.at(2).at(i).toImage().mirrored(true,false);
        QPixmap temp1=QPixmap::fromImage(mirror_img1).scaled(80,80,Qt::KeepAspectRatioByExpanding);
        stop_right.append(temp1);
    }
    img_matrix_.append(to_left);
    img_matrix_.append(to_right);
    img_matrix_.append(stop_left);
    img_matrix_.append(stop_right);

    direction_=random(360);
    if(direction_>180){speed_x_=7;}
    else {speed_x_=-7;}
}
void Stinky::Act(int step)
{
    CollideDetect();
    if(g_alien_amount>0&&move_status_==MOVING)
    {
        if(speed_x_>0)
        {
            img_state_index_=3;
            img_index_=0;
            //  speed_x_=0;
            move_status_=STOPPING;
        }else if(speed_x_<0)
        {
            img_state_index_=2;
            img_index_=0;
            // speed_x_=0;
            move_status_=STOPPING;
        }
    }
    if(g_alien_amount>0&&move_status_==STOPPING)
    {
        if(img_index_<9)
        {
            if(step%3==0)
            {
                img_index_++;
            }
        }
    }
    if(g_alien_amount==0&&move_status_==STOPPING)
    {
        if(img_index_>0)
        {
            if(step%3==0)
            {
                img_index_--;
            }
        }
        if(img_index_==0)
        {
            move_status_=MOVING;
            if(img_state_index_==2)
            {
                img_state_index_=0;
            }else if(img_state_index_==3)
            {
                img_state_index_=1;
            }
        }
    }
    if(g_alien_amount==0&&move_status_==MOVING)
    {
        if(speed_x_>0)
        {
            img_state_index_=1;
        }else  if(speed_x_<0)
        {
            img_state_index_=0;
        }
        if(step%120==0)
        {
            direction_=random(360);
            if(direction_>180){speed_x_=7;}
            else {speed_x_=-7;}
        }

        if(pos_x_<=5 && speed_x_<0)
        {
            speed_x_= -speed_x_;
        }
        if(pos_x_> (SCREEN_WIDTH-real_width_) && speed_x_>=0)
        {
            speed_x_= -speed_x_;
        }
        if(step%5==0)
        {
            pos_x_+=speed_x_;
            setPos(pos_x_,pos_y_);
        }
        if(step%3==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
    }

    update();

}

void Stinky::CollideDetect()
{

    foreach (QGraphicsItem *item, collidingItems())
    {
        GameObject*gm=dynamic_cast<GameObject*>(item);
        if(gm->kind_=="bonus"&&gm->isVisible())
        {
            Bonus * bonus=dynamic_cast<Bonus*>(item);
           // bonus->enabled_=false;
            bonus->need_deleted_=true;
            bonus->setVisible(false);
            g_current_money+=bonus->value_;
            qDebug()<<g_current_money;
            emit bonus->sgn_Deleted();
        }
    }


}
Vert::Vert(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent)
    :Pet(l,w,pos_x,pos_y,name,scene,parent)
{
    pixmap_matrix pix_mat1=CreatePixMat(img_,10,2,80,80);
    pixmap_array to_left;
    pixmap_array to_right;
    pixmap_array turn_left;
    pixmap_array turn_right;
    for(int i=0;i<10;i++)
    {
        to_left.append(pix_mat1[0][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        QImage mirror_img=pix_mat1.at(0).at(i).toImage().mirrored(true,false);
        QPixmap temp=QPixmap::fromImage(mirror_img).scaled(80,80,Qt::KeepAspectRatioByExpanding);
        to_right.append(temp);

        turn_right.append(pix_mat1[1][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
        turn_left.append(pix_mat1[1][9-i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
    }
    img_matrix_.append(to_left);
    img_matrix_.append(to_right);
    img_matrix_.append(turn_left);
    img_matrix_.append(turn_right);

    img_state_index_=0;

    speed_=6;
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}

void Vert::Act(int step)
{
    if(step%120==0)
    {
        direction_=random(360);
        speed_x_ = speed_*cos(direction_*3.1416/180);
        speed_y_ = speed_*sin(direction_*3.1416/180);
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
    if(speed_x_>0){img_state_index_=1;}
    else{img_state_index_=0;}
    if(step%2==0)
    {
        img_index_++;
        img_index_=img_index_%10;
    }

    if(step%200==0)
    {
        Bonus*bonus=new Bonus(72,72,pos_x_,pos_y_-height_/2,"gold",scene());
    }
    update();
}

