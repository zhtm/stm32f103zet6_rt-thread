#include <rtthread.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <device_config.h>


void all_thread_entry(void *parameter)
{
#if KEY_DEVICE
    rt_thread_t key_thread = rt_thread_create("key_thread", key_thread_entry, NULL, KEY_THREAD_SIZE, KEY_THREAD_PRIORITY, THREAD_TICK);
    if(key_thread == RT_NULL)
    {
        LOG_E("rt_thread create key_thread failed. \n");
    }

    rt_thread_startup(key_thread);
#endif

#if LED_0_DEVICE
    rt_thread_t led0_thread = rt_thread_create("led0_thread", led0_thread_entry, NULL, LED_THREAD_SIZE, LED_THREAD_PRIORITY, THREAD_TICK);
    if(led0_thread == RT_NULL)
    {
        LOG_E("rt_thread create led0_thread failed. \n");
    }

    rt_thread_startup(led0_thread);
#endif

#if LED_1_DEVICE
    rt_thread_t led1_thread = rt_thread_create("led1_thread", led1_thread_entry, NULL, LED_THREAD_SIZE, LED_THREAD_PRIORITY, THREAD_TICK);
    if(led1_thread == RT_NULL)
    {
        LOG_E("rt_thread create led1_thread failed. \n");
    }

    rt_thread_startup(led1_thread);
#endif


    return;
}
