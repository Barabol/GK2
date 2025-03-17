#ifndef __BINARY_BOARD__
#define __BINARY_BOARD__
#include "binaryMatrix.h"
enum FLAGS : int { MOVE, ATTACK, GUARD, PLACED };
enum TYPES : int {
  PAWN = 0,
  KNIGHT = 1,
  BISHOP = 2,
  ROOK = 3,
  QUEEN = 4,
  KING = 5,
  WHITE = 0,
  BLACK = 1
};
enum MOVEMENT_FLAGS : int {
  NONE,
  CAPTURE,
  PROMOTION,
  SZACH,
  SZACH_MAT,
  CASTLE_SHORT,
  CASTLE_LONG
};
typedef struct {
  MOVEMENT_FLAGS move;
  MOVEMENT_FLAGS szach;
} returnType;
class piece {
public:
  char pinned;
  char typ;
  char color;
  bool notMoved;
  piece(const char kolor, const char typ);
  ~piece();
  char symbol();
  char value();
  void clearPin();
  void setPin();

private:
};

class board {
public:
  BMatrix flags[2][4];
  piece *layout[8][8];
  bool playing;
  char points[2];
  char kings[2][2];
  char szach[2];
  unsigned char colors[2][3];
  board();
  ~board();
  void operator=(const board b);
  void clear();
  void print();
  bool flag(const unsigned char x, const unsigned char y);
  void flagAll(const unsigned char color);
  void flagAll();
  void switchPlayer();
  returnType move(const char px, const char py, const char x, const char y);
  void kinglogic(const char x, const char y);
  void setPfunction(char (*f)(char));
  void clearAllFlags();
  BMatrix kingFlagging(const char color);
  BMatrix isPinned(const char x, const char y);
  void setBoardColor(bool tile, unsigned char r, unsigned char g,
                     unsigned char b);

private:
  struct {
    char x, y;
    piece *passantable;
  } enPassant;
  char (*promotionFunction)(char);
  BMatrix _f_attack_Extra_Extra(const char x, const char y, const char Ax,
                               const char Ay);
  BMatrix __k_f(const char x, const char y);
  BMatrix _f_Fking(const unsigned char color);
  void flag_(const unsigned char x, const unsigned char y);
  void _f_guard(const unsigned char x, const unsigned char y);
  void _f_move(const unsigned char x, const unsigned char y);
  void _f_placed(const unsigned char x, const unsigned char y);
  void _f_attack(const unsigned char x, const unsigned char y);
  BMatrix _f_attack_Extra(const char color);
  BMatrix _f_layout(const char color);
  bool chk_layout(const unsigned char x, const unsigned char y);
};
#endif
