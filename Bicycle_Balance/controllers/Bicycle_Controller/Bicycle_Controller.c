/**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为 自行车平衡控制 主 文件
**  Version    : 
**  Notes      : 使用键盘 ← → 控制自行车运动方向
**  Author     : 于宪元
**********************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <webots/robot.h>
#include <webots/keyboard.h>

#include "webotsInterface.h"
#include "controller.h"
#include <math.h>
extern bicycleTypeDef bicycle;

int main(int argc, char **argv) {
  
  wb_robot_init();
  webots_device_init();                           //webots设备初始化
  bicycle_init();                                 //自行车初始化
  while (wb_robot_step(TIME_STEP) != -1) {

  updateRobotState();                             //自行车状态更新
  bicycle_control();                              //自行车控制
  }
  
  wb_robot_cleanup();
  return 0;
}


