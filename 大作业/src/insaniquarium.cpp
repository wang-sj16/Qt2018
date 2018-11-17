#include"insaniquarium.h"
#include"global.h"
#include"button.h"
#include"food.h"
#include"bonus.h"
#include"fish.h"
#include"pet.h"
#include"moneydigit.h"

#include"alien.h"
#include<QMediaPlayer>
#include<QPainter>
#include<QtGlobal>
#include<QTime>
#include<QTimer>


Insaniquarium::Insaniquarium(QWidget *parent)
    : QGraphicsView(parent)
{
    player_=new QMediaPlayer;
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene_ = new QGraphicsScene;
    scene_->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    scene_->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene_);

    setCacheMode(QGraphicsView::CacheBackground);

    // 关闭滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //计时器用用于刷新
    timer_ = new QTimer;
    connect(timer_, SIGNAL(timeout()),this, SLOT(slt_onTimeOut()));

    //监视游戏是否结束
    connect (this,SIGNAL(sgn_GameOver()),this,SLOT(slt_onGameOver()));

    //载入开始界面
    StartScene();
}

void Insaniquarium::StartScene()
{
    //设置开始界面背景
    setBackgroundBrush(QPixmap(":/images/backgrounds/talkshow.jpg")
                       .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                               Qt::KeepAspectRatioByExpanding));

    //放置开关  尺寸288*33  位置（336，480）
    Button* start_button=new Button(288,33,336,500,"start",scene_);
    connect(start_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
}

void Insaniquarium::ChoosePetScene()
{
    scene_->clear();
    QPixmap pix(LABELS_PATH["choosePetLabel"]);
    QGraphicsPixmapItem * pixmapItem = scene()->addPixmap(pix);
    //pixmapItem->setPos(230, 0);
    pixmapItem->setPos(230,0);
    Button* confirm_button=new Button(288,33,345,550,"confirm",scene_);

    connect(confirm_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));

    switch(g_pet_amount)
    {

    case 0:
    {
        break;
    }
    case 1:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        break;
    }
    case 2:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        Button *vert_button=new   Button(200,150,480,80,"vert",scene_   );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(vert_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        break;
    }
    case 3:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        Button *vert_button=new   Button(200,150,480,80,"vert",scene_   );
        Button *clyde_button=new  Button(200,150,280,230,"clyde",scene_ );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(vert_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(clyde_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));

        break;
    }
    case 4:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        Button *vert_button=new   Button(200,150,480,80,"vert",scene_   );
        Button *clyde_button=new  Button(200,150,280,230,"clyde",scene_ );
        Button *niko_button=new   Button(200,150,480,230,"niko",scene_  );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(vert_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(clyde_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(niko_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        break;
    }
    case 5:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        Button *vert_button=new   Button(200,150,480,80,"vert",scene_   );
        Button *clyde_button=new  Button(200,150,280,230,"clyde",scene_ );
        Button *niko_button=new   Button(200,150,480,230,"niko",scene_  );
        Button *meryl_button=new   Button(200,150,280,380,"meryl",scene_  );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(vert_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(clyde_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(niko_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(meryl_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        break;
    }
    case 6:
    {
        Button *stinky_button=new Button(200,150,280,80,"stinky",scene_ );
        Button *vert_button=new   Button(200,150,480,80,"vert",scene_   );
        Button *clyde_button=new  Button(200,150,280,230,"clyde",scene_ );
        Button *niko_button=new   Button(200,150,480,230,"niko",scene_  );
        Button *meryl_button=new   Button(200,150,280,380,"meryl",scene_  );
        Button *prego_button=new  Button(200,150,480,380,"prego",scene_ );
        connect(stinky_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(vert_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(clyde_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(niko_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(meryl_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        connect(prego_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
        break;
    }
    }

}

void Insaniquarium::RestartScene()
{
    player_->stop();
    scene_->clear();
    chosen_pets_.clear();
    during_game_=false;
    QPixmap pix(LABELS_PATH["restartLabel"]);
    QGraphicsPixmapItem * pixmapItem = scene_->addPixmap(pix);
    pixmapItem->setPos(230, 0);
    Button *restart_button=new Button(288,33,345,550,"restart",scene_);
    connect(restart_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
}

void Insaniquarium::NextLevelScene()
{
    player_->stop();
    scene_->clear();
    timer_->stop();
    chosen_pets_.clear();
    during_game_=false;
    if(g_pet_amount<6)
    {g_pet_amount++;}
    QPixmap pix(LABELS_PATH["nextLevelLabel"]);
    QGraphicsPixmapItem * pixmapItem = scene_->addPixmap(pix);
    pixmapItem->setPos(230, 0);
    Button *next_level_button=new Button(288,33,345,550,"nextLevel",scene_);
    connect(next_level_button, SIGNAL(sgn_ReleaseButton(QString)),this, SLOT(slt_onClickButton(QString)));
}

void Insaniquarium::MainGameScene()
{
    scene_->clear();
    g_max_food=1;
    g_egg_state=0;
    g_food_state=0;
    g_current_money=100000;
    SetMainUI();
    int x =40+ qrand()%760;   //随机生成
    int y=200;
    ProduceFish("smallGuppy",x,y);
    foreach (QString petName, chosen_pets_)
    {

        if(petName=="niko")
        {
            Niko* niko=new Niko(80,80,200,450,"niko",scene_);
            Q_UNUSED(niko);
        }else if(petName=="stinky")
        {
            Stinky* stinky=new Stinky(80,80,300,610,"stinky",scene_);
            Q_UNUSED(stinky);
        }
        else if(petName=="vert")
        {
            Vert* vert=new Vert(80,80,100,300,"vert",scene_);
            Q_UNUSED(vert);
        }else if(petName=="clyde")
        {
            Clyde* clyde=new Clyde(80,80,200,300,"clyde",scene_);
            Q_UNUSED(clyde);
        }else if(petName=="meryl")
        {
            Meryl* meryl=new Meryl(80,80,300,300,"meryl",scene_);
            Q_UNUSED(meryl);
        }else if(petName=="prego")
        {
            Prego* prego=new Prego(80,80,150,200,"prego",scene_);
            Q_UNUSED(prego);
        }
    }

    //开始每秒50次循环


    player_->setVolume(30);
    player_->play();

    timer_->start(20);

}

void Insaniquarium::SetMainUI()
{
    switch(g_pet_amount)
    {
    case 0:
        player_->setMedia(QUrl("qrc:/music/1.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[2])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 1:
        player_->setMedia(QUrl("qrc:/music/2.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[1])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 2:
        player_->setMedia(QUrl("qrc:/music/3.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[2])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 3:
        player_->setMedia(QUrl("qrc:/music/4.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[3])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 4:
        player_->setMedia(QUrl("qrc:/music/5.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[4])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 5:
        player_->setMedia(QUrl("qrc:/music/7.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[5])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    case 6:
        player_->setMedia(QUrl("qrc:/music/6.mp3"));
        setBackgroundBrush(QPixmap(BACKGROUND_PATH[6])
                .scaled(SCREEN_WIDTH, SCREEN_HEIGHT,
                        Qt::KeepAspectRatioByExpanding));
        break;
    }


    //布置按钮及其信号槽
    Button* smallguppy_button=new Button(100,75,0,0,"smallGuppy",scene_);
    Button* middlebreeder_button=new Button(100,75,100,0,"middleBreeder",scene_);
    Button* carnivore_button=new Button(100,75,200,0,"carnivore",scene_);
    Button* ultravore_button=new Button(100,75,300,0,"ulturavore",scene_);
    Button* grubber_button=new Button(100,75,400,0,"grubber",scene_);
    Button* gekko_button=new Button(100,75,500,0,"gekko",scene_);
    Button* upgrade_food_button=new Button(100,75,600,0,"foodUpgrade",scene_);
    Button* more_food_button=new Button(100,75,700,0,"moreFood",scene_);
    Button* egg_button=new Button(100,75,800,0,"egg",scene_);

    connect(smallguppy_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(middlebreeder_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(carnivore_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(ultravore_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(grubber_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(gekko_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(more_food_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(upgrade_food_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    connect(egg_button, SIGNAL(sgn_ReleaseButton(QString)),
            this, SLOT(slt_onClickButton(QString)));
    /*
    money_list_.append(new MoneyDigit(10,26,40,0,77,"digit",scene_));
    money_list_.append(new MoneyDigit(0,26,40,22,77,"digit",scene_));
    money_list_.append(new MoneyDigit(0,26,40,44,77,"digit",scene_));
    money_list_.append(new MoneyDigit(0,26,40,66,77,"digit",scene_));
    money_list_.append(new MoneyDigit(0,26,40,88,77,"digit",scene_));
    money_list_.append(new MoneyDigit(0,26,40,110,77,"digit",scene_));
*/


}

Insaniquarium::~Insaniquarium()
{

}

void Insaniquarium::slt_onClickButton(QString  btn_name)
{
    if(btn_name=="start"||btn_name=="nextLevel"||btn_name=="restart")
    {
        ChoosePetScene();
    }
    else if(btn_name=="confirm")
    {
        during_game_=true;
        MainGameScene();

    }else if(btn_name=="foodUpgrade")
    {
        if(g_food_state<4)
        {
            g_food_state++;
        }
    }else if(   btn_name == "smallGuppy"
                || btn_name == "middleBreeder"
                || btn_name == "carnivore"
                || btn_name == "ulturavore"
                || btn_name == "grubber"
                || btn_name == "gekko")
    {
        //产生随机数作为位置坐标
        if(g_current_money>=BTNS_COST[btn_name])
        {
            g_current_money-=BTNS_COST[btn_name];
            QTime time1;
            time1= QTime::currentTime();
            qsrand(time1.msec()+time1.second()*1000);
            int x =40+ qrand()%760;   //随机生成
            int y=100;
            ProduceFish(btn_name,x,y);
        }

    }
    else if(btn_name=="egg")
    {
        g_egg_state++;
        if(g_egg_state==3)
        {
            NextLevelScene();
        }
    }
    else if(btn_name == "stinky"
            || "vert"
            || "clyde"
            || "prego"
            || "niko"
            || "meryl")
    {
        qDebug()<<btn_name;
        if (chosen_pets_.size() <3)
        {
            //addTick(btnName);
            chosen_pets_.insert(btn_name);
        }
    }

}

void Insaniquarium::slt_onTimeOut()
{
    step_++;
    step_=step_%1400;
    Act(step_);
}

void Insaniquarium::slt_onGameOver()
{
    timer_->stop();
    during_game_ = false;
    RestartScene();

}
void Insaniquarium::Act(int step)
{
    if(g_fish_amount<=0)
    {
        emit sgn_GameOver();
    }
    if (!during_game_)
    {
        return;
    }
    else
    {/*
        if(g_current_money>=99999)
        {
            g_current_money=99999;
        }
        money_list_[1]->SetDigit(g_current_money/10000);
        money_list_[1]->update();
        money_list_[2]->SetDigit((g_current_money%10000)/1000);
        money_list_[2]->update();
        money_list_[3]->SetDigit((g_current_money%1000)/100);
        money_list_[3]->update();
        money_list_[4]->SetDigit((g_current_money%100)/10);
        money_list_[4]->update();
        money_list_[5]->SetDigit(g_current_money%10);
        money_list_[5]->update();
*/
        foreach (QGraphicsItem *item, scene_->items())
        {
                GameObject*gm=dynamic_cast<GameObject*>(item);
                gm->Act(step);
        }
        if(step%10==0)
        {
            foreach (QGraphicsItem *item, scene_->items())
            {
                    GameObject*gm=dynamic_cast<GameObject*>(item);
                    if(gm->need_deleted_)
                    {
                        scene_->removeItem(item);
                        delete item;
                        qDebug()<<"delete item";
                    }
            }
        }
        if(step%700==0)
        {
            if(g_pet_amount==0)
            { Sylv* s=new Sylv(160,160,200,400,"sylv",scene_);

            }else if(g_pet_amount==1)
            {
                Balrog* b=new Balrog(160,160,400,200,"balrog",scene_);
            }
            else if(g_pet_amount==2)
            {
                Gus* g=new Gus(160,160,200,450,"gus",scene_);
            }
            else if(g_pet_amount==3)
            {
                Psychosquid* p=new Psychosquid(160,160,100,200,"psychosquid",scene_);
            }
            else if(g_pet_amount==4)
            {
                Gus* gus=new Gus(160,160,200,450,"gus",scene_);
                Balrog* ba=new Balrog(160,160,350,400,"balrog",scene_);
            }
            else if(g_pet_amount==5)
            {
                Sylv* syl=new Sylv(160,160,100,300,"sylv",scene_);
                Balrog* balro=new Balrog(160,160,200,400,"balrog",scene_);
                Psychosquid* psychouid=new Psychosquid(160,160,500,200,"psychosquid",scene_);
            }
            else if(g_pet_amount==6)
            {
                Gus* gus=new Gus(160,160,200,450,"gus",scene_);
                Sylv* sv=new Sylv(160,160,100,300,"sylv",scene_);
                Balrog* brog=new Balrog(160,160,200,400,"balrog",scene_);
                Psychosquid* psysquid=new Psychosquid(160,160,100,200,"psychosquid",scene_);
            }

        }
    }
}


/*
void Insaniquarium::SetMoneyBoard()
{

    qDebug()<<"setmoneyboard";
    if (g_current_money>=99999)
    {
        g_current_money=99999;
    }
    for(int i=0;i<5;i++)
    {
        int m_pixIndex;
        switch (i)
        {
        case 0:
            m_pixIndex=10;
            break;
        case 1:
            m_pixIndex = g_current_money / 10000;
            break;
        case 2:
            m_pixIndex = (g_current_money % 10000) / 1000;
            break;
        case 3:
            m_pixIndex = (g_current_money % 1000) / 100;
            break;
        case 4:
            m_pixIndex = (g_current_money % 100) / 10;
            break;
        case 5:
            m_pixIndex = g_current_money % 10;
            break;

        }

    }
}*/
void Insaniquarium:: mousePressEvent(QMouseEvent *event)
{
    if(during_game_)
    {
        if (event->button() == Qt::LeftButton)
        {
            event->accept();
            if (feedable_)
            { // feed fish

                if ((scene_->items(event->pos())).size() == 0&&event->pos().y()<660&&g_food_number<g_max_food)
                { // if not press on other item
                    int x=event->pos().x();
                    int y=event->pos().y();
                    Food*food=new Food(40,40,x-20,y-20,"food",scene_);
                    Q_UNUSED(food);
                    g_current_money-=5;
                }
            }
        } else
        {
            event->ignore();
        }
    }else
    {
        event->ignore();
    }
    QGraphicsView::mousePressEvent(event);
}

void Insaniquarium::ProduceFish(QString name, int x, int y)
{
    if(name=="smallGuppy")
    {
        SmallGuppy* smallguppy=new SmallGuppy(80,80,x,y,name,scene_);
        Q_UNUSED(smallguppy);
    }
    else if(name=="middleBreeder")
    {
        MiddleBreeder* middle_breeder=new MiddleBreeder(80,80,x,y,name,scene_);
        Q_UNUSED(middle_breeder);
    }
    else if(name=="carnivore")
    {
        Carnivore* carnivore=new Carnivore(80,80,x,y,name,scene_);
        Q_UNUSED(carnivore);
    }
    else if(name=="ulturavore")
    {
        Ulturavore* ulturavore=new Ulturavore(160,160,x,y,name,scene_);
        Q_UNUSED(ulturavore);
    }
    else if(name=="grubber")
    {
        Grubber* grubber=new Grubber(80,80,x,600,name,scene_);
        Q_UNUSED(grubber);
    }
    else if(name=="gekko")
    {
        Gekko* gekko=new Gekko(80,80,x,y,name,scene_);
        Q_UNUSED(gekko);
    }
}
