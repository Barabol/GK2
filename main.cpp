#include "src/chessLogic/board.h"
#include "src/networking/socket.h"
#include "src/render/render.h"
#include <cstdio>
#include <raylib.h>
// #define NO_BOARD
int main(int argc, char **argv) {
   Conn *con;
   if (argc == 1) {
      printf("server\n");
      con = conCreate(0, NULL);
      if (con == NULL)
         return 1;
   } else {
      printf("%s\n", argv[1]);
      con = conCreate(0, argv[1]);
      if (con == NULL) {
         return 1;
      }
      conSend(con);
   }
   board *mainBoard = new board;
   mainBoard->print();
   con->packet.content.y = 2;
   con->packet.content.x = 3;

#ifndef NO_BOARD
   renderBoard(mainBoard, con);
#endif

   mainBoard->~board();
#ifdef NO_BOARD
   getchar();
#endif
   conKill(con);
}
