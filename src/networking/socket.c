#include "./socket.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void *conHandle(void *args) {
   Conn *selfCon = (Conn *)args;
   while (selfCon->flags & USED) {
      puts("test");
   }
   return NULL;
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

   if (host == NULL) {
      conSetFlag(newCon, IS_SERVER);
   } else {
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
   conDropFlag(con, USED);
   pthread_join(con->thread, NULL);
}
