/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */
#include "netdev_ipaddr.h"
#include "netdev.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports
#include <logo.h>

extern void wlan_autoconnect_init(void);
extern int hands_app(void);

#define LED_PIN GET_PIN(I, 8)

int main(void)
{



    lcd_show_image(0, 0, 320, 240, LOGO);
    lcd_show_string(90, 140, 16, "Hello RT-Thread!");
    lcd_show_string(90, 156, 16, "Demo: gc0328c & LCD");

    struct netdev *netdev= RT_NULL;
    ip_addr_t addr;
    addr.addr = netdev_ipaddr_addr("192.168.225.112");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    /* init Wi-Fi auto connect feature */
    wlan_autoconnect_init();
    /* enable auto reconnect on WLAN device */
    rt_wlan_config_autoreconnect(RT_TRUE);
    /* logo 1s showing */

    do
       {
           netdev = netdev_get_first_by_flags(NETDEV_FLAG_LINK_UP);
           rt_thread_mdelay(500);
       }while(netdev == RT_NULL);
//
       netdev_set_dns_server(netdev, 0, &addr);


       rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

       /* logo 1s showing */

       rt_thread_mdelay(500);

       hands_app();



    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


