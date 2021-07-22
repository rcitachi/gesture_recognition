/*
#include <ledshow.h>
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-21     years       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "ledshow.h"


void ledoff(void)
{

    rt_pin_write(LED_PIN, PIN_HIGH);

}


void ledon(void)
{

    rt_pin_write(LED_PIN, PIN_LOW);

}


void ledshow_1(void)
{
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN, PIN_LOW);

}

void ledshow_2(void)
{
    rt_thread_mdelay(100);
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_thread_mdelay(100);
    rt_pin_write(LED_PIN, PIN_LOW);

}
