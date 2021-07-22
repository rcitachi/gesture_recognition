/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author      Notes
 *
 */
/*
 * ������������������������cp ���������������
 *
 * ��������������������� tcp ���������������������������
 * ��������� tcpclient ���������������������������������
 * ���������������������������������cpclient URL PORT
 * URL��������������������������� PORT:������������������
 * ��������������������������������������������������������������������������������������������������������������������������������� 'q' ������ 'Q' ������������������������������������
*/
#include <rtthread.h>
#include <sys/socket.h> /* ���������BSD socket������������������������ocket.h��������������� */
#include <netdb.h>
#include <string.h>
#include <finsh.h>

#define BUFSZ   1024

static const char send_data[] = "This is TCP Client from RT-Thread."; /* ��������������������������������� */
void tcpclient(void)
{

    int ret;
    char *recv_data;
    struct hostent *host;
    int sock, bytes_received;
    struct sockaddr_in server_addr;
//    const char *url;
//    int port;
    struct rt_mailbox *box = RT_NULL;
    struct rt_ipc_object *obj = RT_NULL;

    rt_ubase_t *value = RT_NULL;

    obj = rt_object_find("mbt",RT_Object_Class_MailBox);
    box = rt_container_of(obj, struct rt_mailbox ,parent);
//    if (argc < 3)
//    {
//        rt_kprintf("Usage: tcpclient URL PORT\n");
//        rt_kprintf("Like: tcpclient 192.168.12.44 5000\n");
//        return ;
//    }

//    url = argv[1];
//    port = strtoul(argv[2], 0, 10);

    /* ������������������������������������url���������host����������������������������������������������������������������������� */
    host = gethostbyname("192.168.225.159");

    /* ������������������������������������������������������������ */
    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        rt_kprintf("No memory\n");
        return;
    }

    /* ���������������������ocket������������������SOCKET_STREAM������CP��������� */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* ���������socket��������� */
        rt_kprintf("Socket error\n");

        /* ��������������������������� */
        rt_free(recv_data);
        return;
    }

    /* ������������������������������������������������������ */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* ��������������������������� */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        closesocket(sock);
        /* ������������������ */
        rt_kprintf("Connect fail!\n");


    }
    else
    {
        /* ������������������ */
        rt_kprintf("Connect successful\n");
    }

    while (1)
    {
        /* ������ock���������������������������������UFSZ - 1������������������ */
//        bytes_received = recv(sock, recv_data, BUFSZ - 1, 0);
//        if (bytes_received < 0)
//        {
//            /* ��������������������������������������������������� */
//            closesocket(sock);
//            rt_kprintf("\nreceived error,close the socket.\r\n");
//
//            /* ��������������������������� */
//            rt_free(recv_data);
//            break;
//        }
//        else if (bytes_received == 0)
//        {
//            /* ��������� recv ��������������������������������������������0������������������������������������������������������������ */
//            closesocket(sock);
//            rt_kprintf("\nreceived error,close the socket.\r\n");
//
//            /* ��������������������������� */
//            rt_free(recv_data);
//            break;
//        }
//
//        /* ������������������������������������������������������ */
//        recv_data[bytes_received] = '\0';
//
//        if (strncmp(recv_data, "q", 1) == 0 || strncmp(recv_data, "Q", 1) == 0)
//        {
//            /* ������������������������������������������������������������������������ */
//            closesocket(sock);
//            rt_kprintf("\n got a 'q' or 'Q',close the socket.\r\n");
//
//            /* ��������������������������� */
//            rt_free(recv_data);
//            break;
//        }
//        else
//        {
//            /* ������������������������������������������������������ */
//            rt_kprintf("\nReceived data = %s ", recv_data);
//        }

        /* ������������������������sock��������� */

        rt_mb_recv(box, &value, 1000);
        if(value == RT_NULL)
        {
            ret = send(sock, "NULL", strlen("NULL"), 0);
        }
        else {
            ret = send(sock, value, strlen(value), 0);
        }

        if (ret < 0)
        {
            /* ��������������������������������������������������� */
            do {
                ret = send(sock, value, strlen(value), 0);
                rt_thread_mdelay(500);


            } while (ret > 0);

        }
        else if (ret == 0)
        {
            /* ���������send���������������������������0������������������������ */
            rt_kprintf("\n Send warning,send function return 0.\r\n");
        }
        rt_thread_mdelay(500);
    }
    return;
}

MSH_CMD_EXPORT(tcpclient, a tcp client sample);
