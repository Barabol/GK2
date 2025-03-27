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
   IS_SERVER = 16,
   SENDING = 32,
   READ = 64,
	CON_CLOASED = 128
}
ConFlags;

/**
 * Struct: Packet
 *\------------
 *
 *	base structure for packet recived from clinet/server
 */
typedef struct {
   char type;
   struct {
      char x;
      char y;
   } content;
} Packet;

/**
 * Struct: Conn
 *\------------
 *
 *	base structure for network connection
 */
typedef struct {
   int sockFd;
   int con;
   int flags;
   pthread_t thread;
   Packet packet;
   struct {
      char x;
      char y;
   } recived;
} Conn;

/**
 * Function: conSend
 * \-----------------
 *
 *	sends packet
 *
 */
void conSend(Conn *con);

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
