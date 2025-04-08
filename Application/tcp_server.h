/*
 * tcp_server.h
 *
 *  Created on: 30 mar 2025
 *      Author: micha
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "tcp.h"
#include "lwip/stats.h"

typedef struct pbuf* (*msg_handler_t)(struct tcp_pcb *tpcb, struct tcp_server_struct *es);

 /* structure for maintaining connection infos to be passed as argument 
    to LwIP callbacks*/
    struct tcp_server_struct
    {
        u8_t state;             /* current connection state */
        u8_t retries;
        struct tcp_pcb *pcb;    /* pointer on the current tcp_pcb */
        struct pbuf *p;         /* pointer on the received/to be transmitted pbuf */
        msg_handler_t handler;
    };





void tcp_server_init(uint16_t port, msg_handler_t handler);

void tcp_server_send_msg(uint16_t port, char* msg, uint16_t length);

#endif /* TCP_SERVER_H_ */
