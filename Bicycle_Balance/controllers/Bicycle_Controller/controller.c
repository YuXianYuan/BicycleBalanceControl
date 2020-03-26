/**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为 自行车平衡控制 控制器 文件
**  Version    : 
**  Notes      :
**  Author     : 于宪元
**********************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <webots/keyboard.h>

#include "controller.h"

bicycleTypeDef bicycle;
//----------------------------------------------------------declaration
void update_Kd();
void update_IMU();
/*
自行车参数初始化，在while（1）之前调用
*/
void bicycle_init()
{
  //------------------------------------------------------------------------控制参数
  bicycle.k = 8.0;
  bicycle.c = 0.1;
  //------------------------------------------------------------------------模型参数
  bicycle.d = 0.6;
  bicycle.l = 0.5;
  bicycle.h = 1.1;
  bicycle.m = 65;
  //------------------------------------------------------------------------状态区
  bicycle.Kd    = 0.0;
  bicycle.v     = 2.0;
  bicycle.Roll  = 0.0;
  bicycle.dRoll = 0.0;
}
/*
自行车状态更新，包括读取传感器的数据以及一些状态估计
*/
void updateRobotState()
{
  /*通过键盘修改期望转弯曲率*/
  update_Kd();
  /*IMU和IMU导数更新*/
  update_IMU();
}
/*
机器人控制
*/
void bicycle_control()
{
  double v  = bicycle.v;
  double Kd = bicycle.Kd;
  double k  = bicycle.k;
  double c  = bicycle.c;
  double R  = bicycle.Roll;
  double dR = bicycle.dRoll;
  double m  = bicycle.m;
  double h  = bicycle.h;
  double l  = bicycle.l;
  double d  = bicycle.d;
  /*求期望横滚角*/
  double Rd = atan(v*v*Kd/g)*180.0/PI;
  /*弹簧阻尼*/
  printf("%f,%f,%f\r\n",R,Rd,R - Rd);
  double T = -k*(R - Rd) - c*dR;
  /*求拐弯曲率*/
  double K = (m*g*h*sin(R/180.0*PI) - T)/(m*v*v*h*cos(R/180.0*PI));
  /*求转向角*/
  double theta = atan(2*K*l/sqrt(1-K*K*l*l))*180.0/PI;
  /*转弯*/
  set_direction_motor_angle(theta);
  /*驱动*/
  set_driver_motor_velocity(v/(d/2));
}
/*
通过键盘修改期望转弯曲率
*/
void update_Kd()
{
   /*读取键盘，获取转弯曲率*/
  switch(get_keyboard())
  {
    case WB_KEYBOARD_RIGHT:
    {
      bicycle.Kd = 1.0/4.0;    //沿着5米的圆圈拐弯，K=1/R
      break;
    }
    case WB_KEYBOARD_LEFT:
    {
      bicycle.Kd = -1.0/4.0;
      break;
    }
    default:
    {
      bicycle.Kd = 0;
      break;
    }
  }
}
/*
IMU与IMU的导数更新
*/
void update_IMU()
{
  static eulerAngleTypeDef pre_eulerAngle = {0,0,0};
  eulerAngleTypeDef eulerAngle = get_IMU_Angle();
  //IMU
  bicycle.Roll  = eulerAngle.roll;
  //IMU'
  bicycle.dRoll = (eulerAngle.roll  - pre_eulerAngle.roll )/((double)TIME_STEP/1000.0);
  
  pre_eulerAngle = eulerAngle;
}