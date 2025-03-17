#include "src/chessLogic/board.h"
#include "src/render/render.h"
#include <raylib.h>

int main(int argc, char **argv) {
   board *mainBoard = new board;
   mainBoard->print();
	renderBoard(mainBoard);
}
