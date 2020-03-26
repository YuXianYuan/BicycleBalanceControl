/**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为 自行车平衡控制 控制器头 文件
**  Version    : 
**  Notes      : 
**  Author     : 于宪元
**********************************************************/
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <stdbool.h>

#include "webotsInterface.h"

//-----------------------------------------------------------macro
#define max(a,b) ( ((a)>(b)) ? (a):(b) )
#define min(a,b) ( ((a)>(b)) ? (b):(a) )

#define g        (9.8)
//-----------------------------------------------------------typedef
/*
自行车定义,包括自行车状态和自行车参数
*/
typedef struct
{
  //------------------------------------------------------------------------控制参数
  double k;      //弹簧刚度
  double c;      //阻尼系数
  //------------------------------------------------------------------------模型参数
  double d;      //轮子直径
  double l;      //前后轮直径的一半
  double h;      //质心高度
  double m;      //质量
  //------------------------------------------------------------------------状态区
  double Kd;     //期望转弯半径
  double v;      //自行车前进速度 m/s
  double Roll;   //横滚角
  double dRoll;  //横滚角的导数
}bicycleTypeDef;
//-----------------------------------------------------------extern
extern bicycleTypeDef bicycle;

extern void bicycle_init           ();
extern void updateRobotState       ();
extern void bicycle_control        ();

#endif

