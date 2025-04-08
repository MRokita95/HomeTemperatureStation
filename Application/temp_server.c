/*
 * temp_server.c
 *
 *  Created on: Apr 2, 2025
 *      Author: micha
 */

 #include "temp_server.h"
 #include "MCP9808.h"

 #include "lwip/debug.h"
 #include "lwip/stats.h"
 #include "lwip/tcp.h"

 char _buffer[256];

 struct pbuf* temp_message_handle(struct tcp_pcb *tpcb, struct tcp_server_struct *es){

    memset (_buffer, '\0', 256);
    strncpy(_buffer, (char *)es->p->payload, es->p->tot_len);
  
    if (strcmp(_buffer, "GETTEMP") == 0){
      float temp = 0.f;
      MPC_get_temp(&temp);
      sprintf(_buffer, "%f", temp);
    
      pbuf_free(es->p);
      
      struct pbuf* p = pbuf_alloc(PBUF_RAW, strlen (_buffer), PBUF_POOL);

      p->payload = (void *)_buffer;
      p->tot_len = strlen (_buffer);
      p->len = strlen (_buffer);

      return p;
    }
     
    return NULL;
   }
