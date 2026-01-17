#ifndef __KEY_H_
#define __KEY_H_

//包含ESP32的gpio组件的头文件
#include "driver/gpio.h"

#define BOOT_PRES 1

void key_init(void);

uint8_t key_scan(uint8_t mode);

#endif