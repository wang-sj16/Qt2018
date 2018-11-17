#ifndef GLOBAL_H
#define GLOBAL_H

#include<QPixmap>
#include<QGraphicsScene>
#include<QMap>
#include<QString>
#include<QDebug>
#include"stdlib.h"
#include"time.h"
#include<QMediaPlayer>
#define random(x) (rand()%x)


typedef QList<QPixmap> pixmap_array;
typedef QList<pixmap_array> pixmap_matrix;


extern int g_max_food;
extern int g_egg_state;
extern int g_food_state;
extern int g_current_money;
extern int g_fish_amount;
extern int g_alien_amount;
extern int g_pet_amount;
extern int g_food_number;


//屏幕尺寸和缩放比例
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;



extern const QMap<QString, int> BONUS_REAL_WIDTH;
extern const QMap<QString, int> BONUS_REAL_HEIGHT;

extern const QMap<QString, int> FISH_REAL_WIDTH;
extern const QMap<QString, int>  FISH_REAL_HEIGHT;

extern const QMap<int, int> FOOD_REAL_WIDTH ;
extern const QMap<int, int> FOOD_REAL_HEIGHT ;


extern const QMap<QString, int> ALIENS_REAL_WIDTH;
extern const QMap<QString, int> ALIENS_REAL_HEIGHT;

extern const  QMap<QString, int>  PETS_REAL_WIDTH ;
extern const  QMap<QString, int>  PETS_REAL_HEIGHT ;


extern const QMap<QString, int> FISH_EATEN_EXP;
extern const QMap<QString, int> FISH_UPGRADE_EXP ;
extern const QMap<QString, int> FISH_INIT_HUNGRY ;
extern const QMap<QString, int> FISH_MAX_HUNGRY ;
extern const QMap<QString, int> FISH_HUNGRY_THRESHOLD;
extern const QMap<QString, int> FISH_FULL_THRESHOLD ;
extern const QMap<int, int> FOODS_EXP;
extern const QMap<QString, int> ALIENS_MAX_HEALTH;

extern const  QMap<int, QString> ALIENS_NAME ;
extern const  QMap<QString, int> BONUS_VALUE;
extern const  QMap<QString, int>  BONUS_INDEX;
extern const  QMap<QString, int>  BTNS_COST;
extern const QMap<QString,QString> FISHES_TO_BONUS;




//存放各种路径
extern const QString LOADING_PATH;
extern const QString FOOD_PATH;
extern const QString BONUS_PATH;
extern const QMap<QString,QString> ALIENS_PATH;
extern const QMap<int,QString> BACKGROUND_PATH;
extern const QMap<QString,QString> BTN_PATH;
extern const QMap<QString, QString> PETS_PATH ;
extern const QMap<QString, QString> ALIENS_PATH;
extern const QMap<QString, QString>  LABELS_PATH ;
extern const QMap<int, QString>  DIGIT_PATH ;
extern const QMap<QString, QString> FISH_PATH;

extern pixmap_matrix CreatePixMat(QPixmap & pix, int count_x, int count_y,int l,int w);




#endif // GLOBAL_H
