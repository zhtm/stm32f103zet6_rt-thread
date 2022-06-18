/*
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-19     ztiming      first modify.
 *
 * 程序清单：key up键通过外部中断的方式触发；
 *  key0，1通过轮训方式触发；
 * 所有的按键触发后都通过消息发送出去。
*/
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


/* 邮箱控制块 */
struct rt_mailbox key_mb;
/* 用于放邮件的内存池 */
uint8_t key_mb_pool[24];

static uint8_t key_up_mb_str[] = "key_up";
static uint8_t key_0_mb_str[] = "key0";
static uint8_t key_1_mb_str[] = "key1";





/* 引脚编号，通过查看驱动文件drv_gpio.c确定 */
#define KEY_UP_PIN          GET_PIN(A, 0)  /* PA0 */
#define KEY0_PIN            GET_PIN(E, 4)  /* PE4 */
#define KEY1_PIN            GET_PIN(E, 3)  /* PE3 */



void key_up_callback(void *args)
{
    /* 发送 key_up_mb_str 地址到邮箱中 */
    rt_mb_send(&key_mb, (rt_uint32_t)&key_up_mb_str);
}

static void key_init(void)
{
    /* KEY_UP引脚为唤醒模式 */
    rt_pin_mode(KEY_UP_PIN, PIN_MODE_INPUT_PULLDOWN);

    /*KEY_UP设置外部上升沿触发*/
    rt_pin_attach_irq(KEY_UP_PIN, PIN_IRQ_MODE_RISING, key_up_callback, RT_NULL);

    /*使能中断*/
    rt_pin_irq_enable(KEY_UP_PIN, PIN_IRQ_ENABLE);

    /* KEY0,1引脚为内部上拉输入模式 */
    rt_pin_mode(KEY0_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLUP);
}


void key_thread_entry(void *parameter)
{
    rt_err_t ret;
    /* 初始化一个 mailbox */
    ret = rt_mb_init(&key_mb,
                        "key_mb",                       /* 名称是 key_mb */
                        &key_mb_pool[0],                /* 邮箱用到的内存池是 key_mb_pool */
                        sizeof(key_mb_pool) / 4,        /* 邮箱中的邮件数目，因为一封邮件占 4 字节 */
                        RT_IPC_FLAG_FIFO);              /* 采用 FIFO 方式进行线程等待 */
    if (ret != RT_EOK)
    {
        rt_kprintf("key mailbox init failed.\n");
        return;
    }

    //按键初始化
    key_init();
    while(1)
    {
        //KEY0
        if(rt_pin_read(KEY0_PIN) == PIN_LOW)    //低电平触发按件
        {
            rt_thread_mdelay(100);
            if(rt_pin_read(KEY0_PIN) == PIN_LOW)
            {
                /* 发送 key_up_mb_str 地址到邮箱中 */
                rt_mb_send(&key_mb, (rt_uint32_t)&key_0_mb_str);
            }
        }

        //KEY1
        if(rt_pin_read(KEY1_PIN) == PIN_LOW)    //低电平触发按件
        {
            rt_thread_mdelay(100);
            if(rt_pin_read(KEY1_PIN) == PIN_LOW)
            {
                /* 发送 key_up_mb_str 地址到邮箱中 */
                rt_mb_send(&key_mb, (rt_uint32_t)&key_1_mb_str);
            }
        }
        rt_thread_mdelay(50);
    }
}
