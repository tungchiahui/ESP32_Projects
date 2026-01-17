#include "led.h"

void led_init(void)
{   
    //给结构体清零(C语言知识,要给局部变量清零,防止未被初始化的地方出现很奇怪的事情)
    gpio_config_t gpio_init_struct = {0}; 

    gpio_init_struct.pin_bit_mask = (1ULL << GPIO_NUM_43);    //初始化IO43
    gpio_init_struct.mode = GPIO_MODE_OUTPUT;                 //设置为输出模式
    gpio_init_struct.pull_up_en = GPIO_PULLUP_DISABLE;        //禁用上拉电阻
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;    //禁用下拉电阻
    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;           //禁用中断

    gpio_config(&gpio_init_struct);        //配置GPIO

}