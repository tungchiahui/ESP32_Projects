//包含FreeRTOS头文件(为了用vTaskDelay)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//包含LED头文件,为了初始化LED和使用GPIO
#include "led.h"

void app_main(void)
{
    //初始化led的GPIO
    led_init();
    //死循环,等同于while(1),但效率比while(1)更高
    for(;;)
    {
        gpio_set_level(GPIO_NUM_43, PIN_SET);   //设置为高电平
        vTaskDelay(500 / portTICK_PERIOD_MS);  //延时500ms
        gpio_set_level(GPIO_NUM_43, PIN_RESET); //设置为低电平
        vTaskDelay(500 / portTICK_PERIOD_MS);  //延时500ms
    }
}