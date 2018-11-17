#include "bonus.h"
#include "global.h"
Bonus::Bonus(qreal l,qreal w,
             qreal pos_x,qreal pos_y,
             QString name,QGraphicsScene *scene,
             QGraphicsItem *parent)
    :GameObject(l,w,name,scene,parent),pos_x_(pos_x),pos_y_(pos_y)

{
    width_=72;
    height_=72;
    kind_="bonus";
    value_=BONUS_VALUE[name_];
    img_state_index_=BONUS_INDEX[name_];
    setPos(pos_x_,pos_y_);
    img_x=7;
    img_y=10;
    img_= QPixmap(BONUS_PATH);
    img_matrix_=CreatePixMat(img_,img_y,img_x,width_,height_);
    real_width_=BONUS_REAL_HEIGHT[name_];
    real_height_=BONUS_REAL_WIDTH[name_];

}


QRectF Bonus::boundingRect() const
{
    QRectF outerRect = img_matrix_[0][0].rect();
    return QRectF((outerRect.width()-real_width_)/2, (outerRect.height()-real_height_)/2, real_width_, real_height_);
}
QPainterPath Bonus::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,img_matrix_[img_state_index_][img_index_]);
}
void Bonus::Act(int step)
{

    //下落和落地
    if(pos_y_<660-real_height_/2&&pos_y_>=80&&isVisible())
    {
        if(step%3==0)
        {
            img_index_++;
            img_index_=img_index_%10;

        }
        if(img_state_index_==5)
        {
            pos_y_--;
        }else
        {
            pos_y_++;
        }

        setPos(pos_x_,pos_y_);
    }else
    {
     //   enabled_=false;
        setVisible(false);
        countdown_++;
        need_deleted_=true;
        emit sgn_Deleted();
        if(countdown_>=1)
        {

        }
    }
    update();
}


//点击获取钱币
void Bonus:: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        event->accept();
        g_current_money+=value_;
        qDebug()<<"current money:"<<g_current_money;
     //   enabled_=false;
        need_deleted_=true;
        setVisible(false);
        emit sgn_Deleted();
        update();
    } else
    {
        event->ignore();
    }
}
