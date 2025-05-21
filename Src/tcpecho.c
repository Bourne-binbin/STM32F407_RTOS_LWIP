 #include "tcpecho.h"

 #include "lwip/opt.h"

 #if LWIP_NETCONN

 #include "lwip/sys.h"
 #include "lwip/api.h"
 /*----------------------------------------------------------------*/
 static void
 tcpecho_thread(void *arg)
 {
     struct netconn *conn, *newconn;
     err_t err;
     LWIP_UNUSED_ARG(arg);

     /* Create a new connection identifier. */
     /* Bind connection to well known port number 7. */
 #if LWIP_IPV6
     conn = netconn_new(NETCONN_TCP_IPV6);
     netconn_bind(conn, IP6_ADDR_ANY, 5001);
 #else /* LWIP_IPV6 */
     conn = netconn_new(NETCONN_TCP);                        (1)
     netconn_bind(conn, IP_ADDR_ANY, 5001);          (2)
 #endif /* LWIP_IPV6 */
     LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

     /* Tell connection to go into listening mode. */
     netconn_listen(conn);                           (3)

     while (1)
     {

         /* Grab new connection. */
         err = netconn_accept(conn, &newconn);               (4)
         /*printf("accepted new connection %p\n", newconn);*/
         /* Process the new connection. */
         if (err == ERR_OK)
         {
             struct netbuf *buf;
             void *data;
             u16_t len;

             while ((err = netconn_recv(newconn, &buf)) == ERR_OK) (5)
             {
                 /*printf("Recved\n");*/
                 do
                 {
                 netbuf_data(buf, &data, &len);              (6)
                 err= netconn_write(newconn, data, len, NETCONN_COPY); (7)
 #if 0
                     if (err != ERR_OK)
                     {
                         printf("tcpecho: netconn_write: error \"%s\"\n",
                             lwip_strerr(err));
                     }
 #endif
                 }
                 while (netbuf_next(buf) >= 0);                      (8)
                 netbuf_delete(buf);                         (9)
             }
             /*printf("Got EOF, looping\n");*/
             /* Close connection and discard connection identifier. */
             netconn_close(newconn);                         (10)
             netconn_delete(newconn);                                (11)
         }
     }
 }
 /*----------------------------------------------------------------*/
 void
 tcpecho_init(void)
 {
     sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, 512, 4);
 }
 /*-----------------------------------------------------------------*/

 #endif /* LWIP_NETCONN */