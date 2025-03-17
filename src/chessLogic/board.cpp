#include "board.h"
#include <stdio.h>
board::board() { this->clear(); }
board::~board() {
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 0; y++)
      if (this->layout[x][y])
        this->layout[x][y]->~piece();
}
char piece::value() {
  switch (this->typ) {
  case PAWN:
    return 1;
  case KNIGHT:
    return 3;
  case BISHOP:
    return 3;
  case ROOK:
    return 4;
  case QUEEN:
    return 9;
  case KING:
    return 10;
  }
  return 0;
}
void board::clearAllFlags() {
  for (int x = 0; x < 4; x++) {
    this->flags[WHITE][x].clear();
    this->flags[BLACK][x].clear();
  }
}
void board::setPfunction(char (*f)(char)) { this->promotionFunction = f; }
void board::switchPlayer() { this->playing = (~this->playing) & 1; }
void board::operator=(board b) {}
void board::clear() {
  this->szach[0] = 0;
  this->szach[1] = 0;
  this->enPassant.passantable = nullptr;
  this->points[0] = 0;
  this->points[1] = 0;
  this->playing = WHITE;
  this->kings[WHITE][0] = 4;
  this->kings[WHITE][1] = 7;
  this->kings[BLACK][0] = 4;
  this->kings[BLACK][1] = 0;
  for (int x = 0; x < 4; x++) {
    this->flags[0][x].clear();
    this->flags[1][x].clear();
  }
  char content[8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 0; y++) {
      if (this->layout[x][y])
        this->layout[x][y]->~piece();
      this->layout[x][y] = nullptr;
    }
  for (int x = 0; x < 8; x++) {
    this->layout[x][0] = new piece(BLACK, content[x]);
    this->layout[x][1] = new piece(BLACK, PAWN);
    this->layout[x][2] = nullptr;
    this->layout[x][3] = nullptr;
    this->layout[x][4] = nullptr;
    this->layout[x][5] = nullptr;
    this->layout[x][6] = new piece(WHITE, PAWN);
    this->layout[x][7] = new piece(WHITE, content[x]);
  }
}
void board::print() {
  char symbol = ' ';
  char kolorek = 0;
  const char BG[4][7] = {
      {"\x1b[46m"}, {"\x1b[42m"}, {"\x1b[41m"}, {"\x1b[105m"}};
  const char PC[2][8] = {{"\x1b[1;37m"}, {"\x1b[1;30m"}};

  printf("\x1b[44;1;31m   ");
  for (int x = 0; x < 8; x++)
    printf("\x1b[44;1;31m%c ", 'A' + x);
  puts("\x1b[0m");

  for (int y = 0; y < 8; y++) {
    printf("\x1b[44;1;31m %c \x1b[0m", '8' - y);
    for (int x = 0; x < 8; x++) {
      if (this->layout[x][y] != nullptr) {
        symbol = this->layout[x][y]->symbol();
        kolorek = this->layout[x][y]->color;
        if (this->layout[x][y]->color)
          symbol += 32;
      }
      printf("%s%s%c \x1b[0m", BG[(x + y) & 1], PC[kolorek], symbol);
      symbol = ' ';
    }
    puts("");
  }
}

piece::piece(char kolor, char typ) {
  this->color = kolor;
  this->typ = typ;
  this->notMoved = true;
  this->pinned = 0;
}
piece::~piece() {}
char piece::symbol() {
  switch (this->typ) {
  case PAWN:
    return 'P';
  case KNIGHT:
    return 'N';
  case BISHOP:
    return 'B';
  case ROOK:
    return 'R';
  case QUEEN:
    return 'Q';
  case KING:
    return 'K';
  }
  return '?';
}
void piece::clearPin() { this->pinned = 0; }
void piece::setPin() { this->pinned++; }
void board::setBoardColor(bool tile, unsigned char r, unsigned char g,
                          unsigned char b) {
  this->colors[tile][0] = r;
  this->colors[tile][1] = g;
  this->colors[tile][2] = b;
}
