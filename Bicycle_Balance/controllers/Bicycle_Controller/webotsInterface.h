 /**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为 自行车平衡控制 仿真环境或硬件接口 头文件
**  Version    : 
**  Notes      : 
**  Author     : 于宪元
**********************************************************/
#ifndef _WEBOTSINTERFACE_H_
#define _WEBOTSINTERFACE_H_

//-----------------------------------------------------------macro
#define PI           (3.141892654f)
#define TIME_STEP    (10)

//-----------------------------------------------------------typedef
/* 
陀螺仪数据定义,为了方便调试采用角度制，注意，采用角度制
*/
typedef struct
{
  double roll;       //横滚，x轴
  double pitch;      //俯仰，z轴
  double yaw;        //偏航，y轴
}eulerAngleTypeDef;

//-----------------------------------------------------------extern
extern void              webots_device_init                                           ();
extern void              set_direction_motor_angle                        (double angle);
extern void              set_driver_motor_velocity                     (double velocity);
extern int               get_keyboard                                                 ();
extern eulerAngleTypeDef get_IMU_Angle                                                ();

#endif

