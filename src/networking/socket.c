#include "./socket.h"
#include "../config.h"
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *conHandle(void *args) {
   Conn *selfCon = (Conn *)args;
   socklen_t conLen;
   struct sockaddr_in con;

   Packet *holder = (Packet *)malloc(sizeof(Packet));
   char buff[1024];
   ssize_t len;

   if (selfCon->flags & IS_SERVER) {
      selfCon->con =
          accept(selfCon->sockFd, (struct sockaddr *)(&con), &conLen);
      conSetFlag(selfCon, CONNECTED);
      conSend(selfCon);
   } else {
      selfCon->con = selfCon->sockFd;
      conSetFlag(selfCon, CONNECTED);
   }

   while (selfCon->flags & USED) {
      len = recv(selfCon->con, buff, 1024, 0);
      if (len == 0) {
         puts("bad connectrion");
         close(selfCon->con);
         conDropFlag(selfCon, CONNECTED);
         conSetFlag(selfCon, CON_CLOASED);
         return NULL;
      }
      if (len >= 3) {
         selfCon->recived.x = buff[0] - '0';
         selfCon->recived.y = buff[2] - '0';
      }
      conSetFlag(selfCon, RECIVED);
      printf("%zd, %d %d\n", len, selfCon->recived.x, selfCon->recived.y);
   }
   conDropFlag(selfCon, CONNECTED);
   conSetFlag(selfCon, CON_CLOASED);
   return NULL;
}

void conSend(Conn *con) {
   char buff[1024];
   sprintf(buff, "%d|%d", con->packet.content.x, con->packet.content.y);
   int a;
   if (con->flags & IS_SERVER)
      a = send(con->con, buff, strlen(buff), 0);
   else
      a = send(con->sockFd, buff, strlen(buff), 0);
   printf("%d,sending[%zd]: %s\n", a, strlen(buff), buff);
   conSetFlag(con, SENDING);
}

Conn *conCreate(char flag, char *host) {
   Conn *newCon;
   newCon = (Conn *)malloc(sizeof(Conn));
   if (newCon == NULL) {
      puts("cannot allocate memory");
      return NULL;
   }
   newCon->sockFd = -1;
   newCon->flags = flag | USED;

   struct sockaddr_in srv;

   newCon->sockFd = socket(AF_INET, SOCK_STREAM, 0);
   srv.sin_family = AF_INET;
   srv.sin_port = htons(PORT);

   if (newCon->sockFd < 0) {
      puts("unable to allocate socket");
      free(newCon);
      return NULL;
   }

   if (host == NULL) {
      conSetFlag(newCon, IS_SERVER);
      srv.sin_addr.s_addr = INADDR_ANY;
#ifdef DEBUG
      int opt = 1;
      if (setsockopt(newCon->sockFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                     &opt, sizeof(opt)) < 0) {
         puts("unable to set socket options");
         free(newCon);
         return NULL;
      }

#endif
      int binded = bind(newCon->sockFd, (struct sockaddr *)(&srv), sizeof(srv));
      if (binded < 0) {
         printf("unable to start server socket [%d]\n", binded);
         free(newCon);
         return NULL;
      }
      if (listen(newCon->sockFd, 1) < 0) {
         printf("unable to start listener\n");
         free(newCon);
         return NULL;
      }
   } else {
      if (inet_pton(AF_INET, host, &srv.sin_addr) < 0) {
         puts("unable to find server");
         free(newCon);
         return NULL;
      }
      int status =
          connect(newCon->sockFd, (struct sockaddr *)(&srv), sizeof(srv));
      if (status < 0) {
         puts("unable to connect to server");
         free(newCon);
         return NULL;
      }
   }

   pthread_create(&newCon->thread, 0, conHandle, newCon);
   return newCon;
}

void conSetFlag(Conn *con, ConFlags flag) {
   if (con == NULL || flag <= 0)
      return;
   con->flags |= flag;
}

int conCheckFlag(Conn *con, ConFlags flag) {
   if (con == NULL || flag <= 0)
      return -1;
   return con->flags & flag;
}

void conDropFlag(Conn *con, ConFlags flag) {
   if (con == NULL || flag <= 0)
      return;
   con->flags &= (~flag);
}
void conKill(Conn *con) {
   if (con == NULL)
      return;
   puts("cloasing socket");
   conDropFlag(con, USED);
   pthread_detach(con->thread);
   pthread_join(con->thread, NULL);
   puts("socket cloased");
   free(con);
}
