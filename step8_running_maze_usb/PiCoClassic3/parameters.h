
#ifndef _PARAMETER

#include "static_parameters.h"

//物理的なパラメータ
#define TIRE_DIAMETER	(48.0)					//タイヤの直径
#define TREAD_WIDTH	(72.6)					//トレッド幅
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)			//超信地旋回の時にタイヤが動く距離

//センサ関連パラメータ
#define WAITLOOP_SLED 300					//LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数

#define REF_SEN_R	280					//マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	415					//マウスを迷路中央に置いた時のセンサの値

/*#define TH_SEN_R	173					//壁があるか否かの閾値
#define TH_SEN_L	169					//壁があるか否かの閾値
#define TH_SEN_FR	145					//壁があるか否かの閾値
#define TH_SEN_FL	134					//壁があるか否かの閾値*/

#define TH_SEN_R	103					//壁があるか否かの閾値
#define TH_SEN_L	100					//壁があるか否かの閾値
#define TH_SEN_FR	150					//壁があるか否かの閾値
#define TH_SEN_FL	130					//壁があるか否かの閾値

#define CONTH_SEN_R	TH_SEN_R				//制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L				//制御をかけるか否かの閾値
//#define CON_WALL_KP	(0.5)					//壁センサによる姿勢制御の比例制御の比例定数
#define CON_WALL_KP	(0.5)

//走行パラメータ
#define SEARCH_SPEED	(400)					//探索の速度
#define SEARCH_ACCEL	(1.0)					//探索の加速度

#define TURN_ACCEL		(0.5)				//超信地旋回の加速度

//迷路関連パラメータ
#define GOAL_X	9		//ゴール座標(x)
#define GOAL_Y	9		//ゴール座標(y)

#define _PARAMETER

#endif
