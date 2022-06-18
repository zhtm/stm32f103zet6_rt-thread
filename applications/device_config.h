#ifndef __DEVICE_CONFIG_H__
#define __DEVICE_CONFIG_H__

#include <./led/led.h>
#include <./key/key.h>



#define THREAD_TICK     2

#define LED_0_DEVICE            1
#define LED_1_DEVICE            1

#define LED_THREAD_SIZE         256
#define LED_THREAD_PRIORITY     29

#define KEY_DEVICE              1

#define KEY_THREAD_SIZE         256
#define KEY_THREAD_PRIORITY     28





void all_thread_entry(void *parameter);

#endif
