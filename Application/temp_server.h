/*
 * temp_server.h
 *
 *  Created on: Apr 2, 2025
 *      Author: micha
 */

#ifndef TEMP_SERVER_H_
#define TEMP_SERVER_H_

#include "tcp_server.h"


struct pbuf* temp_message_handle(struct tcp_pcb *tpcb, struct tcp_server_struct *es);


#endif /* TEMP_SERVER_H_ */
