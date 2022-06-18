#include <rtthread.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rtdbg.h>


#include <./led/led.h>

#define THREAD_TICK     2

#define LED_THREAD_SIZE     256
#define LED_THREAD_PRIORITY 29







void all_thread_entry(void *parameter)
{
#if 1
    LOG_D("all_thread_entry \r\n");
    rt_thread_t led_thread = rt_thread_create("led0_thread", led0_thread_entry, NULL, LED_THREAD_SIZE, LED_THREAD_PRIORITY, THREAD_TICK);
    if(led_thread == RT_NULL)
    {
        LOG_E("rt_thread create led_thread failed. \n");
    }

    rt_thread_startup(led_thread);
#endif
    return;
}
