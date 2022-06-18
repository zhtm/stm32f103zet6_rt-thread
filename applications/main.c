/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-11     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <device_config.h>

#define ALL_THREAD_SIZE     512
#define ALL_THREAD_PRIORITY 30


int main(void)
{
    rt_thread_t thread_create = NULL;
    thread_create = rt_thread_create("all_thread", all_thread_entry, NULL, ALL_THREAD_SIZE, ALL_THREAD_PRIORITY, 2);
    if(thread_create == RT_NULL)
    {
        LOG_E("create all thread failed. \n");
        return -RT_ERROR;
    }
    LOG_D("create all thread successed. \n");
    rt_thread_startup(thread_create);
    return 0;
}

