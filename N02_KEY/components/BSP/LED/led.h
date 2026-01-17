#ifndef __LED_H_
#define __LED_H_

//包含ESP32的gpio组件的头文件
#include "driver/gpio.h"

typedef enum {
    PIN_RESET = 0,     
    PIN_SET      
} gpio_output_state_t;

void led_init(void);

#endif