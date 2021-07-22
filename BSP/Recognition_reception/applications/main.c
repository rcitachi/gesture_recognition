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
#include "drv_spi_ili9488.h"
#include "logo.h"
#include "ledshow.h"

extern void wlan_autoconnect_init(void);
extern void tcpserv(int argc, char **argv);
int main(void)
{

    ledoff();
    lcd_show_image(0, 0, 320, 240, LOGO);
    struct netdev *netdev= RT_NULL;
    ip_addr_t addr;
    addr.addr = netdev_ipaddr_addr("192.168.225.112");



    /* init Wi-Fi auto connect feature */
    wlan_autoconnect_init();
    /* enable auto reconnect on WLAN device */
    rt_wlan_config_autoreconnect(RT_TRUE);

    do
    {
        netdev = netdev_get_first_by_flags(NETDEV_FLAG_LINK_UP);
        rt_thread_mdelay(500);
    }while(netdev == RT_NULL);
    netdev_set_dns_server(netdev, 0, &addr);
    tcpserv(0,0);




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


