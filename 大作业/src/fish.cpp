#include"fish.h"
#include"food.h"
#include"bonus.h"
#include<QTime>
#include<QtGlobal>
#include<QtMath>
#include<QDebug>


Fish::Fish(qreal l,qreal w,
           qreal pos_x,qreal pos_y,
           QString name,QGraphicsScene *scene,
           QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent),pos_x_(pos_x),pos_y_(pos_y)
{
    g_fish_amount++;
    kind_="fish";
    img_state_index_=0;
    setPos(pos_x_,pos_y_);
    img_x=5;
    img_y=10;
    img_= QPixmap(FISH_PATH[name_]);
    real_width_=FISH_REAL_WIDTH[name_];
    real_height_=FISH_REAL_HEIGHT[name_];
    hungury_value_=FISH_INIT_HUNGRY[name_];
    exp_value_=0;
//    enabled_=true;
    hungury_value_=FISH_INIT_HUNGRY[name_];

    if(name_=="grubber")
    {
        img_matrix_=CreatePixMat(img_,10,3,80,80);
    }
    else
    {
        if(name_=="ulturavore")

        {
            pixmap_matrix pix_mat1=CreatePixMat(img_,10,5,160,160);
            pixmap_array normal_to_left;
            pixmap_array normal_to_right;
            pixmap_array hungry_to_left;
            pixmap_array hungry_to_right;
            pixmap_array die_left;
            pixmap_array die_right;
            for(int i=0;i<10;i++)
            {
                normal_to_left.append(pix_mat1[0][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img=pix_mat1[0][i].toImage().mirrored(true,false);
                QPixmap temp=QPixmap::fromImage(mirror_img).scaled(160,160,Qt::KeepAspectRatioByExpanding);
                normal_to_right.append(temp);

                hungry_to_left.append(pix_mat1[2][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img1=pix_mat1[2][i].toImage().mirrored(true,false);
                QPixmap temp1=QPixmap::fromImage(mirror_img1).scaled(160,160,Qt::KeepAspectRatioByExpanding);
                hungry_to_right.append(temp1);

                die_left.append(pix_mat1[4][i].scaled(160,160,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img2=pix_mat1[4][i].toImage().mirrored(true,false);
                QPixmap temp2=QPixmap::fromImage(mirror_img2).scaled(160,160,Qt::KeepAspectRatioByExpanding);
                die_right.append(temp2);
            }

            img_matrix_.append(normal_to_left);
            img_matrix_.append(normal_to_right);
            img_matrix_.append(hungry_to_left);
            img_matrix_.append(hungry_to_right);
            img_matrix_.append(die_left);
            img_matrix_.append(die_right);
        }else
        {
            pixmap_matrix pix_mat1=CreatePixMat(img_,10,5,80,80);
            pixmap_array normal_to_left;
            pixmap_array normal_to_right;
            pixmap_array hungry_to_left;
            pixmap_array hungry_to_right;
            pixmap_array die_left;
            pixmap_array die_right;
            for(int i=0;i<10;i++)
            {
                normal_to_left.append(pix_mat1[0][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img=pix_mat1[0][i].toImage().mirrored(true,false);
                QPixmap temp=QPixmap::fromImage(mirror_img).scaled(80,80,Qt::KeepAspectRatioByExpanding);
                normal_to_right.append(temp);

                hungry_to_left.append(pix_mat1[2][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img1=pix_mat1[2][i].toImage().mirrored(true,false);
                QPixmap temp1=QPixmap::fromImage(mirror_img1).scaled(80,80,Qt::KeepAspectRatioByExpanding);
                hungry_to_right.append(temp1);

                die_left.append(pix_mat1[4][i].scaled(80,80,Qt::KeepAspectRatioByExpanding));
                QImage mirror_img2=pix_mat1[4][i].toImage().mirrored(true,false);
                QPixmap temp2=QPixmap::fromImage(mirror_img2).scaled(80,80,Qt::KeepAspectRatioByExpanding);
                die_right.append(temp2);
            }
            img_matrix_.append(normal_to_left);
            img_matrix_.append(normal_to_right);
            img_matrix_.append(hungry_to_left);
            img_matrix_.append(hungry_to_right);
            img_matrix_.append(die_left);
            img_matrix_.append(die_right);
        }

    }

}



QRectF Fish::boundingRect() const
{
    QRectF outerRect = img_matrix_[0][0].rect();
    return QRectF((outerRect.width()-real_width_)/2, (outerRect.height()-real_height_)/2, real_width_, real_height_);
}
QPainterPath Fish::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Fish::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //此处有bug!!!!
    painter->drawPixmap(0,0,img_matrix_[img_state_index_][img_index_]);
}

int Fish::GetCost()
{
    return cost_;
}

void Fish::ProduceBonus(QString bonus_name)
{
    if(bonus_name==""){}
    else if(bonus_name=="insect")
    {
        Bonus*bonus=new Bonus(72,72,pos_x_,pos_y_-height_/2,bonus_name,scene());
    }
    else
    {
        Bonus*bonus=new Bonus(72,72,pos_x_,pos_y_+height_/2,bonus_name,scene());
    }
}

void Fish::Move()
{
    {
        pos_x_+=speed_x_;
        pos_y_+=speed_y_;
    }
    setPos(pos_x_,pos_y_);
}

void Fish::Act(int step)
{
    step_++;
    step_=step_%1000;

    CollideDetect();
    if(step_%5==0)
    {
        hungury_value_--;
    }
    if(!isDying&&hungury_value_<=0)
    {
        isDying=true;
        if(speed_x_>=0)
            img_state_index_=5;
        if(speed_x_<0)
            img_state_index_=4;
        img_index_=0;
    }else if(hungury_value_<=FISH_HUNGRY_THRESHOLD[name_])
    {
        isHungry=true;
    }else if(hungury_value_>FISH_HUNGRY_THRESHOLD[name_])
    {
        isHungry=false;
    }
    if(isDying)
    {
        if(step_%4==0)
        {
            if(img_index_<9)
            {
                img_index_++;
            }
        }
        if (img_index_==9&&pos_y_<620-real_height_)
        {
            pos_y_+=3;
            setPos(pos_x_,pos_y_);
        }
        if(pos_y_>=619-real_height_)
        {
            setVisible(false);
         //   enabled_=false;
            need_deleted_=true;
        }


    }

    if(!isDying&&!isHungry)
    {
        if(speed_x_>=0)
            img_state_index_=1;
        if(speed_x_<0)
            img_state_index_=0;

        has_target_=false;
        target_=nullptr;
        if(step_%120==0)
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

        if(step_%3==0){Move();}


        if(step_%300==0)
        {
            ProduceBonus(FISHES_TO_BONUS[name_]);
        }
        if(step_%2==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
    }
    else if(!isDying&&isHungry)
    {
        if(speed_x_>=0)
            img_state_index_=3;
        if(speed_x_<0)
            img_state_index_=2;
        if(has_target_)
        {
            //  qDebug()<<name_<<"has target"<<target_->x()<<target_->y();
            if(step_%10==0)
            {
                qreal delta_x=(pos_x_-target_->pos().x());
                qreal delta_y=(pos_y_-target_->pos().y());
                qreal cos_theta=-delta_x/sqrt(delta_x*delta_x+delta_y*delta_y+0.2);
                qreal sin_theta=-delta_y/sqrt(delta_x*delta_x+delta_y*delta_y+0.2);
                speed_x_=speed_*cos_theta*1.5;
                speed_y_=speed_*sin_theta*1.5;
            }
        }
        else
        {
            if(step_%120==0)
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

        if(step_%3==0){Move();}


        if(!has_target_)
        {
            FindTarget();
        }


        if(step_%300==0)
        {
            ProduceBonus(FISHES_TO_BONUS[name_]);
        }
        if(step_%2==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
    }

    update();

}
Fish::~Fish()
{
    g_fish_amount--;
    qDebug()<<g_fish_amount;
}
void Fish::slt_Target_Deleted()
{
    qDebug()<<"slot调用";
    target_=nullptr;
    has_target_=false;
}

void Fish::FindTarget()
{
    QList<GameObject*> edibleItems;
    if(name_=="gekko")
    {
        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->GetName()=="insect"&&gm->isVisible())
            {
                edibleItems.append(dynamic_cast<Bonus *>(gm));
            }
        }
    }else if(name_=="carnivore"&&kind_=="fish")
    {
        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->GetName()=="smallGuppy"&&gm->kind_=="fish"&&gm->isVisible())
            {
                edibleItems.append(dynamic_cast<Fish *>(gm));
            }
        }
    }else if(name_=="ulturavore"&&kind_=="fish")
    {
        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->GetName()=="carnivore"&&gm->kind_=="fish"&&gm->isVisible())
            {
                edibleItems.append(dynamic_cast<Fish *>(gm));
            }
        }
    }else if(name_=="grubber"&&kind_=="fish")
    {
        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->GetName()=="smallGuppy"&&gm->kind_=="fish"&&gm->isVisible())
            {
                edibleItems.append(dynamic_cast<Fish *>(gm));
            }
        }
    }else if(kind_=="fish")
    {

        foreach (QGraphicsItem *item, scene()->items())
        {
            GameObject*gm=dynamic_cast<GameObject*>(item);
            if(gm->kind_=="food"&&gm->isVisible())
            {
                edibleItems.append(dynamic_cast<Food *>(gm));
            }
        }

    }

    if(edibleItems.size()>0)
    {
        target_=edibleItems[0];   //random(edible_items.size())
        has_target_=true;
        //增加信号槽  表示失去目标
        connect(target_,SIGNAL(sgn_Deleted()),this,SLOT(slt_Target_Deleted()));
    }
}

void Fish::CollideDetect()
{
    if(has_target_)
    {
        if(name_=="gekko"&&kind_=="fish")
        {
            foreach (QGraphicsItem *item, collidingItems())
            {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                if(gm->GetName()=="insect"&&gm->isVisible())
                {
                    Bonus * b=dynamic_cast<Bonus*>(item);
                //    b->enabled_=false;
                    b->setVisible(false);
                    b->need_deleted_=true;
                    has_target_=false;
                    target_=nullptr;
                    hungury_value_+=30;
                    emit b->sgn_Deleted();
                }
            }
        }
        else if(name_=="carnivore"&&kind_=="fish")
        {
            foreach (QGraphicsItem *item, collidingItems())
            {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                if(gm->GetName()=="smallGuppy"&&gm->kind_=="fish"&&gm->isVisible())
                {
                    Fish * f=dynamic_cast<Fish *>(item);
                 //   f->enabled_=false;
                    f->setVisible(false);

                    f->need_deleted_=true;
                    has_target_=false;
                    target_=nullptr;
                    hungury_value_+=FISH_EATEN_EXP["smallGuppy"];
                    emit f->sgn_Deleted();
                }

            }
        }

        else if(name_=="ulturavore"&&kind_=="fish")
        {
            foreach (QGraphicsItem *item, collidingItems())
            {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                if(gm->GetName()=="carnivore"&&gm->kind_=="fish"&&gm->isVisible())
                {
                    Fish * f=dynamic_cast<Fish*>(item);
                 //   f->enabled_=false;
                    f->setVisible(false);
                    f->need_deleted_=true;
                    has_target_=false;
                    target_=nullptr;
                    hungury_value_+=FISH_EATEN_EXP[gm->GetName()];
                    emit f->sgn_Deleted();

                }
            }
        }else if(name_=="grubber"&&kind_=="fish")
        {
            foreach (QGraphicsItem *item, collidingItems())
            {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                if(gm->GetName()=="smallGuppy"&&gm->kind_=="fish"&&gm->isVisible())
                {
                    Fish * f=dynamic_cast<Fish*>(item);
                  //  f->enabled_=false;
                    f->setVisible(false);
                    f->need_deleted_=true;
                    has_target_=false;
                    target_=nullptr;
                    hungury_value_+=FISH_EATEN_EXP[gm->GetName()];
                    emit f->sgn_Deleted();

                }
            }
        }else
        {
            foreach (QGraphicsItem *item, collidingItems())
            {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                if(gm->kind_=="food"&&gm->isVisible())
                {
                    Food * food=dynamic_cast<Food*>(item);
                  //  food->enabled_=false;
                    food->setVisible(false);
                    food->need_deleted_=true;
                    has_target_=false;
                    target_=nullptr;
                    emit food->sgn_Deleted();
                    hungury_value_+=FOODS_EXP[g_food_state];
                    exp_value_+=FOODS_EXP[g_food_state];

                }
            }
        }
    }

}
Guppy::Guppy(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent )
    :Fish(l,w,pos_x,pos_y,name,scene,parent)
{
    SetSpeed();
}

void Guppy::SetSpeed()
{
    speed_=5;
    // srand((int)time(0));
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);

}
SmallGuppy::SmallGuppy(qreal l,qreal w,
                       qreal pos_x,qreal pos_y,
                       QString name,QGraphicsScene *scene,
                       QGraphicsItem *parent )
    :Guppy(l,w,pos_x,pos_y,name,scene,parent)
{
    //  qDebug()<<"生成guppy";
}
void SmallGuppy::Act(int step)
{
    Fish::Act(step_);
    if(exp_value_>=FISH_UPGRADE_EXP[name_]&&isVisible())
    {
        upgrade();
    }
    update();
}
void SmallGuppy::upgrade()
{
    setVisible(false);
  //  enabled_=false;
    need_deleted_=true;
    emit sgn_Deleted();
    MiddleGuppy *mg=new MiddleGuppy(80,80,pos_x_+10,pos_y_+10,"middleGuppy",scene());
}

MiddleGuppy::MiddleGuppy(qreal l,qreal w,
                         qreal pos_x,qreal pos_y,
                         QString name,QGraphicsScene *scene,
                         QGraphicsItem *parent )
    :Guppy(l,w,pos_x,pos_y,name,scene,parent)
{

}

void MiddleGuppy::Act(int step)
{
    Fish::Act(step_);
    if(exp_value_>=FISH_UPGRADE_EXP[name_]&&isVisible())
    {
        upgrade();
    }
    update();
}
void MiddleGuppy::upgrade()
{
    setVisible(false);
 //   enabled_=false;
    need_deleted_=true;
    emit sgn_Deleted();
    BigGuppy *mg=new BigGuppy(80,80,pos_x_+10,pos_y_+10,"bigGuppy",scene());
}


BigGuppy::BigGuppy(qreal l,qreal w,
                   qreal pos_x,qreal pos_y,
                   QString name,QGraphicsScene *scene,
                   QGraphicsItem *parent )
    :Guppy(l,w,pos_x,pos_y,name,scene,parent)
{

}

void BigGuppy::Act(int step)
{
    Fish::Act(step_);
    if(exp_value_>=FISH_UPGRADE_EXP[name_]&&isVisible())
    {
        upgrade();
    }
    update();
}
void BigGuppy::upgrade()
{
    setVisible(false);
 //   enabled_=false;
    need_deleted_=true;
    emit sgn_Deleted();
    KingGuppy *mg=new KingGuppy(80,80,pos_x_+10,pos_y_+10,"kingGuppy",scene());
}

KingGuppy::KingGuppy(qreal l,qreal w,
                     qreal pos_x,qreal pos_y,
                     QString name,QGraphicsScene *scene,
                     QGraphicsItem *parent )
    :Guppy(l,w,pos_x,pos_y,name,scene,parent)
{
    speed_=5;
    // srand((int)time(0));
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}
Breeder::Breeder(qreal l,qreal w,
                 qreal pos_x,qreal pos_y,
                 QString name,QGraphicsScene *scene,
                 QGraphicsItem *parent )
    :Fish(l,w,pos_x,pos_y,name,scene,parent)
{
    SetSpeed();
}

void Breeder::SetSpeed()
{
    speed_=5;
    // srand((int)time(0));
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}

void Breeder::GiveBirth(int step)
{
    if(step% birth_time_==0)
    {
        SmallGuppy *sm=new SmallGuppy(80,80,pos_x_+10,pos_y_+10,"smallGuppy",scene());
    }
}

void Breeder::Act(int step)
{
    Fish::Act(step_);
    GiveBirth(step_);
    update();
}

MiddleBreeder::MiddleBreeder(qreal l,qreal w,
                             qreal pos_x,qreal pos_y,
                             QString name,QGraphicsScene *scene,
                             QGraphicsItem *parent )
    :Breeder(l,w,pos_x,pos_y,name,scene,parent)
{
    birth_time_=300;
}

void MiddleBreeder::Act(int step)
{
    Breeder::Act(step_);
    if(exp_value_>=FISH_UPGRADE_EXP[name_]&&isVisible())
    {
        upgrade();
    }
    update();
}
void MiddleBreeder::upgrade()
{
    setVisible(false);
//    enabled_=false;
    need_deleted_=true;
    emit sgn_Deleted();
    BigBreeder *mg=new BigBreeder(80,80,pos_x_+10,pos_y_+10,"bigBreeder",scene());
}


BigBreeder::BigBreeder(qreal l,qreal w,
                       qreal pos_x,qreal pos_y,
                       QString name,QGraphicsScene *scene,
                       QGraphicsItem *parent )
    :Breeder(l,w,pos_x,pos_y,name,scene,parent)
{
    birth_time_=150;
}


Carnivore::Carnivore(qreal l,qreal w,
                     qreal pos_x,qreal pos_y,
                     QString name,QGraphicsScene *scene,
                     QGraphicsItem *parent )
    :Fish(l,w,pos_x,pos_y,name,scene,parent)
{
    SetSpeed();
}





void Carnivore::SetSpeed()
{
    speed_=6;
    srand((int)time(0));
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}




Gekko::Gekko(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent )
    :Fish(l,w,pos_x,pos_y,name,scene,parent)
{
    SetSpeed();
}

void Gekko::SetSpeed()
{
    speed_=6;
    srand((int)time(0));
    direction_=random(360);
    speed_x_=speed_*cos(direction_*3.1416/180);
    speed_y_=speed_*sin(direction_*3.1416/180);
}



Grubber::Grubber(qreal l,qreal w,
                 qreal pos_x,qreal pos_y,
                 QString name,QGraphicsScene *scene,
                 QGraphicsItem *parent )
    :Fish(l,w,pos_x,pos_y,name,scene,parent)
{
    img_state_index_=0;
    setPos(pos_x_,pos_y_);
    img_x=3;
    img_y=10;
    img_= QPixmap(FISH_PATH[name_]);
    //img_matrix_=CreatePixMat(img_,img_y,img_x,length_,width_);
    SetSpeed();
}
void  Grubber::Act(int step)
{
    step_++;
    step_=step_%1000;

    CollideDetect();
    if(step_%5==0)
    {
        hungury_value_--;
    }
    if(!isDying&&hungury_value_<=0)
    {
        isDying=true;
        img_state_index_=2;
        img_index_=0;
    }else if(hungury_value_<=FISH_HUNGRY_THRESHOLD[name_])
    {
        isHungry=true;
    }else if(hungury_value_>FISH_HUNGRY_THRESHOLD[name_])
    {
        isHungry=false;
    }
    if(isDying)
    {
        if(step_%4==0)
        {
            if(img_index_<9)
            {
                img_index_++;
            }
        }
        if (img_index_==9&&pos_y_<620-real_height_)
        {
            pos_y_+=3;
            setPos(pos_x_,pos_y_);
        }
        if(pos_y_>=619-real_height_)
        {
            setVisible(false);
         //   enabled_=false;
            need_deleted_=true;
        }
    }
    if(!isDying&&!isHungry)
    {
      img_state_index_=0;

        has_target_=false;
        target_=nullptr;
        if(step_%120==0)
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

        if(step_%3==0){Move();}


        if(step_%300==0)
        {
            ProduceBonus(FISHES_TO_BONUS[name_]);
        }
        if(step_%2==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
    }
    else if(!isDying&&isHungry)
    {
       img_state_index_=1;
        if(has_target_)
        {
            //  qDebug()<<name_<<"has target"<<target_->x()<<target_->y();
            if(step_%10==0)
            {
                qreal delta_x=(pos_x_-target_->pos().x());
                qreal delta_y=(pos_y_-target_->pos().y());
                qreal cos_theta=-delta_x/sqrt(delta_x*delta_x+delta_y*delta_y);
                qreal sin_theta=-delta_y/sqrt(delta_x*delta_x+delta_y*delta_y);
                speed_x_=speed_*cos_theta*1.5;
                speed_y_=speed_*sin_theta*1.5;
            }
        }
        else
        {
            if(step_%120==0)
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

        if(step_%3==0){Move();}


        if(!has_target_)
        {
            FindTarget();
        }


        if(step_%300==0)
        {
            ProduceBonus(FISHES_TO_BONUS[name_]);
        }
        if(step_%2==0)
        {
            img_index_++;
            img_index_=img_index_%10;
        }
    }

    update();


    }



    void Grubber::SetSpeed()
    {
        speed_=8;
        srand((int)time(0));
        direction_=random(360);
        speed_x_=speed_*cos(direction_*3.1416/180);
        speed_y_=speed_*sin(direction_*3.1416/180);
    }



    Ulturavore::Ulturavore(qreal l,qreal w,
                           qreal pos_x,qreal pos_y,
                           QString name,QGraphicsScene *scene,
                           QGraphicsItem *parent )
        :Fish(l,w,pos_x,pos_y,name,scene,parent)
    {
        SetSpeed();
    }

    void Ulturavore::SetSpeed()
    {
        speed_=8;
        srand((int)time(0));
        direction_=random(360);
        speed_x_=speed_*cos(direction_*3.1416/180);
        speed_y_=speed_*sin(direction_*3.1416/180);
    }




