#include"global.h"


//食物和蛋壳状态
int g_max_food=1;
int g_egg_state=1;
int g_pet_amount=0;
int g_food_state=0;
int g_current_money=100;
int g_fish_amount=0;
int g_alien_amount=0;
int g_food_number=0;

//屏幕尺寸和缩放比例
const int SCREEN_WIDTH=960;
const int SCREEN_HEIGHT=720;

const int POOL_UP_BOUND=80;
const int POOL_LOW_BOUND=660;



const  QMap<QString, int>  BONUS_REAL_HEIGHT = {
    { "silver",   48 },
    { "gold",     48 },
    { "star",     48 },
    { "diamond",  48 },
    { "treasure", 48 },
    { "insect",   48 },
    { "pearl",    48 }
};


const QMap<QString, int> BONUS_REAL_WIDTH = {
    { "silver",   48 },
    { "gold",     48 },
    { "star",     48 },
    { "diamond",  48 },
    { "treasure", 48 },
    { "insect",   48 },
    { "pearl",    48 }
};

const  QMap<QString, int>  PETS_REAL_WIDTH = {
    { "stinky", 80 },
    { "vert",   80 },
    { "clyde",  80 },
    { "prego",  80 },
    { "niko",   80 },
    { "meryl",  80 }
};


const  QMap<QString, int>  PETS_REAL_HEIGHT = {
    { "stinky", 60 },
    { "vert",   60 },
    { "clyde",  75 },
    { "prego",  75 },
    { "niko",   80 },
    { "meryl",  75 }
};

const QMap<QString, int> ALIENS_REAL_WIDTH = {
    { "sylv",        120 },
    { "gus",         120 },
    { "balrog",      135 },
    { "psychosquid", 155 }
};

const QMap<QString, int> ALIENS_REAL_HEIGHT = {
    { "sylv",    160 },
    { "gus",         150 },
    { "balrog",      150 },
    { "psychosquid", 160 }
};


const QMap<int, int> FOOD_REAL_WIDTH = {
    { 0,  15 },
    { 1,  17 },
    { 2,  15 },
    { 3,  31 },
    { 4,  13 }
};

const QMap<int, int> FOOD_REAL_HEIGHT = {
    { 0,  13 },
    { 1,  17 },
    { 2,  9  },
    { 3,  27 },
    { 4,  27 }
};


const QMap<QString, int> FISH_REAL_WIDTH = {
    { "smallGuppy",    35  },
    { "middleGuppy",   50  },
    { "bigGuppy",      70  },
    { "kingGuppy",     75  },
    { "carnivore",     75  },
    { "ulturavore",    145 },
    { "middleBreeder", 55  },
    { "bigBreeder",    70  },
    { "grubber",       65  },
    { "gekko",         70  }
};

const QMap<QString, int>  FISH_REAL_HEIGHT = {
    { "smallGuppy",    32  },
    { "middleGuppy",   45  },
    { "bigGuppy",      65  },
    { "kingGuppy",     70  },
    { "carnivore",     70  },
    { "ulturavore",    105 },
    { "middleBreeder", 50  },
    { "bigBreeder",    60  },
    { "grubber",       72  },
    { "gekko",         75  }
};





const QMap<QString,QString> FISHES_TO_BONUS=
{
    {"smallGuppy",   ""         },
    {"middleGuppy",  "silver"   },
    {"bigGuppy",     "gold"     },
    {"kingGuppy",    "diamond"  },
    {"carnivore",    "diamond"  },
    {"ulturavore",   "treasure" },
    {"middleBreeder",""         },
    {"bigBreeder",   ""         },
    {"grubber",      "insect"   },
    {"gekko",        "pearl"    }
};

const QMap<QString, int> FISH_EATEN_EXP = {
    { "smallGuppy",    10 },
    { "middleGuppy",   15 },
    { "bigGuppy",      20 },
    { "kingGuppy",     25 },
    { "carnivore",     30 },
    { "ulturavore",    45 },
    { "middleBreeder", 15 },
    { "bigBreeder",    20 },
    { "grubber",       25 },
    { "gekko",         40 }
};

const QMap<QString, int> FISH_UPGRADE_EXP = {
    { "smallGuppy",    30   },
    { "middleGuppy",   45   },
    { "bigGuppy",      60   },
    { "kingGuppy",     99999 },
    { "carnivore",     99999 },
    { "ulturavore",    99999 },
    { "middleBreeder", 45   },
    { "bigBreeder",    60   },
    { "grubber",       99999 },
    { "gekko",         99999 }
};

const QMap<QString, int> FISH_INIT_HUNGRY = {
    { "smallGuppy",    85  },
    { "middleGuppy",   125 },
    { "bigGuppy",      170 },
    { "kingGuppy",     210 },
    { "carnivore",     125 },
    { "ulturavore",    250 },
    { "middleBreeder", 125 },
    { "bigBreeder",    170 },
    { "grubber",       170 },
    { "gekko",         150 }
};

const QMap<QString, int> FISH_MAX_HUNGRY = {
    { "smallGuppy",    100 },
    { "middleGuppy",   150 },
    { "bigGuppy",      200 },
    { "kingGuppy",     250 },
    { "carnivore",     200 },
    { "ulturavore",    400 },
    { "middleBreeder", 150 },
    { "bigBreeder",    200 },
    { "grubber",       200 },
    { "gekko",         200 }
};

const QMap<QString, int> FISH_HUNGRY_THRESHOLD = {
    { "smallGuppy",    50  },
    { "middleGuppy",   75  },
    { "bigGuppy",      100 },
    { "kingGuppy",     125 },
    { "carnivore",     100 },
    { "ulturavore",    200 },
    { "middleBreeder", 75  },
    { "bigBreeder",    100 },
    { "grubber",       110 },
    { "gekko",         80  }
};

const QMap<QString, int> FISH_FULL_THRESHOLD = {
    { "smallGuppy",    85  },
    { "middleGuppy",   125 },
    { "bigGuppy",      170 },
    { "kingGuppy",     210 },
    { "carnivore",     125 },
    { "ulturavore",    250 },
    { "middleBreeder", 125 },
    { "bigBreeder",    170 },
    { "grubber",       180 },
    { "gekko",         180 }
};

const QMap<int, int> FOODS_EXP = {
    { 0,  10 },
    { 1,  15 },
    { 2,  20 },
    { 3,  25 },
    { 4,  30 }
};

const QMap<QString, int> ALIENS_MAX_HEALTH = {
    { "sylv",        50 },
    { "gus",         50 },
    { "balrog",      70 },
    { "psychosquid", 99 }
};




const  QMap<QString, int>  BONUS_INDEX = {
    { "silver",   0 },
    { "gold",     1 },
    { "star",     2 },
    { "diamond",  3 },
    { "treasure", 4 },
    { "insect",   5 },
    { "pearl",    6 }
};


const QMap<QString,int> BONUS_VALUE=
{
    { "silver",   15 },
    { "gold",     35 },
    { "star",     100 },
    { "diamond",  200 },
    { "treasure", 1000 },
    { "insect",   200 },
    { "pearl",    300 }
};


const  QMap<QString, int>  BTNS_COST = {
    { "start",         0     },
    { "nextLevel",     0     },
    { "restart",       0     },
    { "confirm",       0     },

    { "stinky",        0     },
    { "vert",          0     },
    { "clyde",         0     },
    { "prego",         0     },
    { "niko",          0     },
    { "meryl",         0     },

    { "smallGuppy",    100   },
    { "middleBreeder", 200   },
    { "carnivore",     1000  },
    { "ulturavore",    3000  },
    { "grubber",       750   },
    { "gekko",         2000  },
    { "foodUpgrade",   200   },
    { "moreFood",      300   },
    { "egg",           1000  }

};



//各种路径
const QString LOADING_PATH=":/images/labels/loading.gif";
const QString FOOD_PATH=":/images/foods/food.png";
const QString BONUS_PATH=":/images/money/money.png";

const QMap<QString,QString> ALIENS_PATH=
{
    {"balrog",       ":/images/aliens/balrog.png"      },
    {"gus",          ":/images/aliens/gus.png"         },
    {"psychosquid",  ":/images/aliens/psychosquid.png" },
    {"sylv",         ":/images/aliens/sylv.png"        }
};

const QMap<int,QString> BACKGROUND_PATH=
{
    {1,    ":/images/backgrounds/aquarium1.png"},
    {2,    ":/images/backgrounds/aquarium3.png"},
    {3,    ":/images/backgrounds/aquarium2.jpg"},
    {4,    ":/images/backgrounds/aquarium4.jpg"},
    {5,    ":/images/backgrounds/aquarium5.jpg"},
    {6,    ":/images/backgrounds/aquarium6.jpg"}
};

const QMap<QString,QString> BTN_PATH
{
    {"carnivore",    ":/images/buttons/carnivoreBtn.png"     },
    {"clyde",        ":/images/buttons/clydeBtn.png"         },
    {"confirm",      ":/images/buttons/confirmBtn.png"       },
    {"display",      ":/images/buttons/display.png"          },
    {"egg",          ":/images/buttons/eggBtn.png"           },
    {"foodUpgrade",  ":/images/buttons/foodUpgradeBtn.png"   },
    {"gekko",        ":/images/buttons/gekkoBtn.png"         },
    {"grubber",      ":/images/buttons/grubberBtn.png"       },
    {"meryl",        ":/images/buttons/meryBtn.png"          },
    {"middleBreeder",":/images/buttons/middleBreederBtn.png" },
    {"moreFood",     ":/images/buttons/moreFoodBtn.png"      },
    {"nextLevel",    ":/images/buttons/nextBtn.png"          },
    {"niko",         ":/images/buttons/nikoBtn.png"          },
    {"prego",        ":/images/buttons/pregoBtn.png"         },
    {"restart",      ":/images/buttons/restartGameBtn.png"   },
    {"smallGuppy",   ":/images/buttons/smallGuppyBtn.png"    },
    {"start",        ":/images/buttons/startGameBtn.png"     },
    {"stinky",       ":/images/buttons/stinkyBtn.png"        },
    {"ulturavore",   ":/images/buttons/ultravoreBtn.png"     },
    {"vert",         ":/images/buttons/vertBtn.png"          }
};

const  QMap<int, QString>  DIGIT_PATH = {
    { 0,  ":/images/num/0.png"  },
    { 1,  ":/images/num/1.png"  },
    { 2,  ":/images/num/2.png"  },
    { 3,  ":/images/num/3.png"  },
    { 4,  ":/images/num/4.png"  },
    { 5,  ":/images/num/5.png"  },
    { 6,  ":/images/num/6.png"  },
    { 7,  ":/images/num/7.png"  },
    { 8,  ":/images/num/8.png"  },
    { 9,  ":/images/num/9.png"  },
    { 10, ":/images/num/10.png" }
};

const  QMap<QString, QString>  LABELS_PATH = {
    { "nextLevelLabel", ":/images/labels/nextLevelLabel.png"  },
    { "restartLabel",   ":/images/labels/gameoverLabel.png"   },
    { "choosePetLabel", ":/images/labels/choosePetLabel.png"  },
    { "tickLabel",      ":/images/labels/ticket.png"          }
};


const  QMap<QString, QString> PETS_PATH = {
    { "stinky",  ":/images/pets/stinky.png" },
    { "vert",    ":/images/pets/vert.png"   },
    { "clyde",   ":/images/pets/clyde.png"  },
    { "prego",   ":/images/pets/prego.png"  },
    { "niko",    ":/images/pets/niko.png"   },
    { "meryl",   ":/images/pets/meryl.png"  }
};



const QMap<QString, QString> FISH_PATH = {
    { "smallGuppy",    ":/images/fish/smallGuppy.png"    },
    { "middleGuppy",   ":/images/fish/mediumGuppy.png"   },
    { "bigGuppy",      ":/images/fish/bigGuppy.png"      },
    { "kingGuppy",     ":/images/fish/kingGuppy.png"     },
    { "carnivore",     ":/images/fish/carnivore.png"     },
    { "ulturavore",    ":/images/fish/ulturaVore.png"    },
    { "middleBreeder", ":/images/fish/mediumBreeder.png" },
    { "bigBreeder",    ":/images/fish/bigBreeder.png"    },
    { "grubber",       ":/images/fish/grubgrubber.png"   },
    { "gekko",         ":/images/fish/gekko.png"         },
};

pixmap_matrix CreatePixMat(QPixmap &pix, int count_x, int count_y,int l,int w)
{
    qreal width = pix.width() / count_x;
    qreal height = pix.height() / count_y;
    pixmap_matrix img_mat;
    for (int j = 0; j < count_y; ++j) {
        pixmap_array img_array;
        for (int i = 0; i < count_x; ++i) {
            QPixmap temp = pix.copy(i * width, j * height,
                                    width, height).scaled(l, w, Qt::KeepAspectRatioByExpanding);;
            img_array.append(temp);
        }
        img_mat.append(img_array);
    }
    return img_mat;
}



