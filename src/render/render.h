#ifndef __CHESS_RENDERER__
#define __CHESS_RENDERER__
#include "../chessLogic/board.h"
#include "../networking/socket.h"
/**
 * Function: renderBoard
 * \---------------------
 *
 * magical function that glues evrything together
 */
void renderBoard(board *board, Conn *con);

#endif
