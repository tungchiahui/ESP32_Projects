//包含FreeRTOS头文件(为了用vTaskDelay)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//包含LED头文件,为了初始化LED和使用GPIO
#include "led.h"
//包含KEY头文件,为了初始化KEY和使用GPIO
#include "key.h"

//按键外部变量声明;
extern uint8_t key_value;


void app_main(void)
{
    //初始化led的GPIO
    led_init();
    //初始化key的GPIO
    key_init();

    //死循环,等同于while(1),但效率比while(1)更高
    for(;;)
    {
        key_value = key_scan(0);

        switch (key_value)
        {
        case BOOT_PRES:
            gpio_set_level(GPIO_NUM_43, !gpio_get_level(GPIO_NUM_43));   //翻转电平
            break;
        
        default:
            break;
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);  //延时10ms
    }
}