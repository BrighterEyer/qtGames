#ifndef LEVELGLOBAL_H
#define LEVELGLOBAL_H


#include <QString>

const static int TOOL_GROUND = 128;
const static int TOOL_GLASS = 129;
const static int TOOL_GLASS2 = 130;
const static int TOOL_TOMATO = 0;
const static int TOOL_CARROT = 1;
const static int TOOL_CABBAGE = 2;
const static int TOOL_CORN =3;
const static int TOOL_EGGPLANT = 4;
const static int TOOL_ONION = 5;
const static int TOOL_BARRIER = 6;
const static int TOOL_EMPTY = 7;

const static int TOOL_TOMATO_LARGE = 100;
const static int TOOL_CARROT_LARGE = 101;
const static int TOOL_CABBAGE_LARGE =102;
const static int TOOL_CORN_LARGE =103;
const static int TOOL_EGGPLANT_LARGE = 104;
const static int TOOL_REMOVE = 105;//init remove type


//特殊道具，只能被道具删除掉
const static int TOOL_BARRIER_SPECIAL = 99;

//道具类型：锁
const static int TOOL_LOCKIN = 8;

const static int TOOL_DIAMOND = 9;

const static int TOOL_MUSHROOM_MOVEABLE = 10;

const static int TOOL_NULL = -1;

//地面层 一共有2层
const static int GROUND_LAYER_1 = 1;
const static int GROUND_LAYER_2 = 2;

//没有泥土地面，只有地表
const static int GROUND_TYPE_FLOOR = 0;

//Barrier 障碍物 但是隐藏，不显示该帧，设置值为原值的2倍，读取时，如果值为原始2倍，则
//将隐藏barrier帧，值改为：TOOL_BARRIER
const static int TOOL_BARRIER_HIDE = TOOL_BARRIER*2;
const static int TOOL_BARRIER_MUSHROOM = TOOL_BARRIER*3;
const static int TOOL_BARRIER_CLONE = TOOL_BARRIER*4;//自身复制
const static int TOOL_BARRIER_MUSHROOMx2 = TOOL_BARRIER*5;//大蘑菇，需要2次爆炸


const static int DEFAULT_MAP_ROWS = 9;
const static int DEFAULT_MAP_COLUMNS = 7;


const static QString STR_LEVEL_HEADER_NAME = "关卡列表";


const static QString STR_LEVEL_SUFFIX = ".bin";
const static QString STR_PROJECT_SUFFIX = ".proj";

//const static QString STR_LEVEL_PREFFIX = "L";

const static QString STR_DEFAULT_NAME  = "Level_";


const static int FILE_CHECK_HEADER_CODE = 0x39473957;

const static int NULL_VALUE = 128;



const static int SCREEN_WIDTH = 1280;
const static int SCREEN_HEIGHT = 720;

const QString strAppName = "GameLevelEditor";

const QString strAppVersion = " Ver 2.1_002_2013.11.21";

const QString strIconPath = ":Icon/res/icon.png";

const QString strInformation = "Update 2013.11.21";

const QString strAbout = "版本发布于:";

//胜利条件

//最大时间
const static int MAX_TIME = 9999;
const static int MAX_ROUND = 9999;


//最大步数


const static int GROUND_MAP_DATA[DEFAULT_MAP_ROWS][DEFAULT_MAP_COLUMNS] = {

                    {1,7,3,7,3,7,-1},
                    {6,4,8,4,8,4,-6},
                    {2,8,4,8,4,8,-2},
                    {6,4,8,4,8,4,-6},
                    {2,8,4,8,4,8,-2},
                    {6,4,8,4,8,4,-6},
                    {2,8,4,8,4,8,-2},
                    {6,4,8,4,8,4,-6},
                    {5,-7,-3,-7,-3,-7,-5}
                    /*{8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},
                    {8,8,8,8,8,8,8},*/
                };

#endif // LEVELGLOBAL_H
