/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-15     misonyo      first implementation.
 */
/*
 * 程序清单：这是一个 PIN 设备使用例程
 * 例程导出了led_ctrl 命令到控制终端
 * 命令调用格式：led_ctrl
 * 程序功能：
*/
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

#include <device_config.h>

/* 引脚编号，通过查看驱动文件drv_gpio.c确定 */
#ifndef LED0_PIN_NUM
    #define LED0_PIN_NUM            21  /* PB5 */
#endif
#ifndef LED1_PIN_NUM
    #define LED1_PIN_NUM            69  /* PE5 */
#endif

void led0_on(void)
{
    rt_pin_write(LED0_PIN_NUM, PIN_LOW);
}

void led1_on(void)
{
    rt_pin_write(LED1_PIN_NUM, PIN_LOW);
}

void led0_off(void)
{
    rt_pin_write(LED0_PIN_NUM, PIN_HIGH);
}

void led1_off(void)
{
    rt_pin_write(LED1_PIN_NUM, PIN_HIGH);
}

static void led0_init(void)
{

    /* led引脚为输出模式 */
    rt_pin_mode(LED0_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认高电平，关灯 */
    rt_pin_write(LED0_PIN_NUM, PIN_HIGH);
}

static void led1_init(void)
{
    /* led引脚为输出模式 */
    rt_pin_mode(LED1_PIN_NUM, PIN_MODE_OUTPUT);
    /* 默认高电平，关灯 */
    rt_pin_write(LED1_PIN_NUM, PIN_HIGH);

}

void led0_thread_entry(void *parameter)
{
    led0_init();
    while(1)
    {
        led0_on();
        rt_thread_mdelay(100);
        led0_off();
        rt_thread_mdelay(400);
    }
    return;
}
#if KEY_DEVICE
extern struct rt_mailbox key_mb;
#endif
void led1_thread_entry(void *parameter)
{
    char *str;

    led1_init();
    while(1)
    {
#if KEY_DEVICE
        /* 从邮箱中收取邮件 */
        if (rt_mb_recv(&key_mb, (uint32_t *)&str, RT_WAITING_FOREVER) == RT_EOK)
        {
            rt_kprintf("get a key mailbox, the content:%s\n", str);
            if (!strcmp(str,"key_up"))
            {
                rt_kprintf("key_up press down! \n");
            }
            else if(!strcmp(str,"key0"))
            {
                led1_on();
            }
            else if(!strcmp(str,"key1"))
            {
                led1_off();
            }
        }
#else
        led1_on();
        rt_thread_mdelay(500);
        led1_off();
        rt_thread_mdelay(400);
#endif
        rt_thread_mdelay(100);
    }
    return;
}
