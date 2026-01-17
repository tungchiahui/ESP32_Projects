#include "key.h"

//包含FreeRTOS头文件(为了用vTaskDelay)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


uint8_t key_value = 0;

void key_init(void)
{   
    //给结构体清零(C语言知识,要给局部变量清零,防止未被初始化的地方出现很奇怪的事情)
    gpio_config_t gpio_init_struct = {0}; 

    gpio_init_struct.pin_bit_mask = (1ULL << GPIO_NUM_0);    //初始化IO0
    gpio_init_struct.mode = GPIO_MODE_INPUT;                 //设置为输入模式
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;        //启用上拉电阻
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;    //禁用下拉电阻
    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;           //禁用中断

    gpio_config(&gpio_init_struct);        //配置GPIO

}


/**
 * @brief       按键扫描函数
 * @note        无
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              BOOT_PRES, 1, BOOT按键按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode)       /* 支持连按 */
    {
        key_up = 1;
    }

    if (key_up && (gpio_get_level(GPIO_NUM_0) == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);           /* 去抖动 */
        key_up = 0;

        if (gpio_get_level(GPIO_NUM_0) == 0)  keyval = BOOT_PRES;


    }
    else if (gpio_get_level(GPIO_NUM_0) == 1)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}