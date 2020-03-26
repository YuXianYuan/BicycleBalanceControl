/**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为 自行车平衡控制 仿真环境 接口文件
**  Version    : 
**  Notes      : 
**  Author     : 于宪元
**********************************************************/
#include <stdio.h>

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/inertial_unit.h>
#include <webots/gyro.h>

#include "webotsInterface.h"

//-----------------------------------------------------------device
/*电机*/
WbDeviceTag Driver_motor;
WbDeviceTag Direction_motor;

/*惯导系统*/
WbDeviceTag IMU;

/*
函数功能：初始化devices
*/
void webots_device_init()
{
  //get device
  Driver_motor      = wb_robot_get_device("driver motor");
  Direction_motor   = wb_robot_get_device("direction motor");
  
  IMU               = wb_robot_get_device("inertial unit");
  
  //enable
  wb_inertial_unit_enable(IMU, TIME_STEP);
  
  wb_keyboard_enable(TIME_STEP);
}
//-----------------------------------------------------------motor
/*
函数功能：设置方向电机转角，角度制
*/
void set_direction_motor_angle(double angle)
{
  wb_motor_set_position(Direction_motor, angle/180.0*PI); 
}
/*
函数功能：设置驱动电机转速，rad/s
*/
void set_driver_motor_velocity(double velocity)
{
  wb_motor_set_position(Driver_motor, INFINITY);
  wb_motor_set_velocity(Driver_motor, velocity);
}
//-----------------------------------------------------------sensor
/*
函数功能：读取IMU数据
*/
eulerAngleTypeDef get_IMU_Angle()
{
  const double* data = wb_inertial_unit_get_roll_pitch_yaw(IMU);
  
  eulerAngleTypeDef eulerAngle;
  eulerAngle.roll  = data[0]*180.0f/PI;
  eulerAngle.pitch = data[1]*180.0f/PI;
  eulerAngle.yaw   = data[2]*180.0f/PI;
  
  return eulerAngle;
}
//-----------------------------------------------------------keyboard
/*
函数功能：读取键盘键值
*/
int get_keyboard()
{
  return wb_keyboard_get_key();
}

