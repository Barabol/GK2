#ifndef __SOCKET__
#define __SOCKET__
#include <sys/socket.h>
#include <threads.h>

/**
 * Enum: ConFlags
 * \-------------
 *
 * flags used in Conn structure
 *
 */
typedef enum {
   USED = 1,
   SEND = 2,
   RECIVED = 4,
   CONNECTED = 8,
   IS_SERVER = 8,
} ConFlags;

/**
 * Struct: Conn
 *\------------
 *
 *	base structure for network connection
 */
typedef struct {
   int sockFd;
   int flags;
   pthread_t thread;
   struct {
      void *content;
      char type;
   } packet;
} Conn;

/**
 * Function: conSetFlag
 * \-----------------
 *
 *	Sets connection flag
 *
 */
void conSetFlag(Conn *con, ConFlags flag);

/**
 * Function: conCreate
 * \-----------------
 *
 * creates new connection structure
 *
 */
Conn *conCreate(char flag, char *host);

/**
 * Function: conKill
 * \-----------------
 *
 * kills connection
 *
 */
void conKill(Conn *con);

/**
 * Function: conCheckFlag
 * \-----------------
 *
 *	checks connection flag
 *
 */
int conCheckFlag(Conn *con, ConFlags flag);

/**
 * Function: conDropFlag
 * \-----------------
 *
 *	disables connection flag
 *
 */
void conDropFlag(Conn *con, ConFlags flag);

/**
 * Function: conSetFlag
 * \-----------------
 *
 *	Sets connection flag
 *
 */
void conSetFlag(Conn *con, ConFlags flag);

#endif
