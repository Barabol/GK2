#ifndef __CHESS_RENDERER__
#define __CHESS_RENDERER__
#include "../chessLogic/board.h"
#include "../networking/socket.h"
void renderBoard(board *board, Conn *con);

#endif
