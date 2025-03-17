#include "board.h"
#include "../config.h"
BMatrix board::_f_attack_Extra_Extra(const char x, const char y, const char Ax,
                                    const char Ay) {
  BMatrix holder;
  BMatrix holder2;
  holder2.clear();
  char working = 0;
  holder.clear();
  piece *used = this->layout[x][y];
  const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  switch (used->typ) {
  case QUEEN:
  case BISHOP:
    for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
      holder2.set(z, v);
      if (chk_layout(z, v) && this->layout[z][v]->color == used->color)
        break;
      if (chk_layout(z, v)) {
        if (z == Ax && v == Ay) {
          working = 1;
          continue;
        }
        if (this->layout[z][v]->color != used->color && working &&
            this->layout[z][v]->typ == KING) {
          this->layout[Ax][Ay]->setPin();
          holder.set(x, y);
          holder |= holder2;
        } else if (this->layout[z][v])
          break;
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
      holder2.set(z, v);
      if (chk_layout(z, v) && this->layout[z][v]->color == used->color)
        break;
      if (chk_layout(z, v)) {
        if (z == Ax && v == Ay) {
          working = 1;
          continue;
        }
        if (this->layout[z][v]->color != used->color && working &&
            this->layout[z][v]->typ == KING) {
          this->layout[Ax][Ay]->setPin();
          holder.set(x, y);
          holder |= holder2;
        } else if (this->layout[z][v])
          break;
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
      holder2.set(z, v);
      if (chk_layout(z, v) && this->layout[z][v]->color == used->color)
        break;
      if (chk_layout(z, v)) {
        if (z == Ax && v == Ay) {
          working = 1;
          continue;
        }
        if (this->layout[z][v]->color != used->color && working &&
            this->layout[z][v]->typ == KING) {
          this->layout[Ax][Ay]->setPin();
          holder.set(x, y);
          holder |= holder2;
        } else if (this->layout[z][v])
          break;
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
      holder2.set(z, v);
      if (chk_layout(z, v) && this->layout[z][v]->color == used->color)
        break;
      if (chk_layout(z, v)) {
        if (z == Ax && v == Ay) {
          working = 1;
          continue;
        }
        if (this->layout[z][v]->color != used->color && working &&
            this->layout[z][v]->typ == KING) {
          this->layout[Ax][Ay]->setPin();
          holder.set(x, y);
          holder |= holder2;
        } else if (this->layout[z][v])
          break;
        break;
      }
    }
    holder2.clear();
    working = 0;
    if (used->typ == BISHOP)
      break;
  case ROOK:
    for (int z = x + 1; z < 8; z++) {
      holder2.set(z, y);
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color) {
        if (z == Ax && Ay == y) {
          working = 1;
          continue;
        }
        if (this->layout[z][y]->typ == KING && working) {
          holder.set(x, y);
          holder |= holder2;
          this->layout[Ax][Ay]->setPin();
        }
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = x - 1; z > -1; z--) {
      holder2.set(z, y);
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color) {
        if (z == Ax && Ay == y) {
          working = 1;
          continue;
        }
        if (this->layout[z][y]->typ == KING && working) {
          holder.set(x, y);
          holder |= holder2;
          this->layout[Ax][Ay]->setPin();
        }
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = y + 1; z < 8; z++) {
      holder2.set(x, z);
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color) {
        if (x == Ax && Ay == z) {
          working = 1;
          continue;
        }
        if (this->layout[x][z]->typ == KING && working) {
          holder.set(x, y);
          holder |= holder2;
          this->layout[Ax][Ay]->setPin();
        }
        break;
      }
    }
    holder2.clear();
    working = 0;
    for (int z = y - 1; z > -1; z--) {
      holder2.set(x, z);
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color) {
        if (x == Ax && Ay == z) {
          working = 1;
          continue;
        }
        if (this->layout[x][z]->typ == KING && working) {
          holder.set(x, y);
          holder |= holder2;
          this->layout[Ax][Ay]->setPin();
        }
        break;
      }
    }
    holder2.clear();
    working = 0;
    break;
  }
  return holder;
}
BMatrix board::isPinned(const char x, const char y) {
  BMatrix holder;
  holder.clear();
  this->layout[x][y]->clearPin();
  for (int z = 0; z < 8; z++)
    for (int v = 0; v < 8; v++)
      if (this->layout[z][v]) {
        holder |= _f_attack_Extra_Extra(z, v, x, y);
      }
#ifdef DEBUG
  holder.print("pin");
#endif
  if (!holder.allValues())
    this->layout[x][y]->clearPin();
  return holder;
}
bool board::chk_layout(const unsigned char x, const unsigned char y) {
  if (y > 7 || y < 0 || x > 7 || x < 0)
    return false;
  if (this->layout[x][y])
    return (bool)(this->layout[x][y]);
  return false;
}
void board::_f_move(const unsigned char x, const unsigned char y) {
  const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  piece *used = this->layout[x][y];
  switch (used->typ) {
  case PAWN:
    if (used->color == WHITE) {
      if (this->chk_layout(x, y - 1))
        break;
      this->flags[used->color][MOVE].set(x, y - 1);
      if (y == 6 && !this->layout[x][y - 2])
        this->flags[used->color][MOVE].set(x, y - 2);
    } else {
      if (this->chk_layout(x, y + 1))
        break;
      this->flags[used->color][MOVE].set(x, y + 1);
      if (y == 1 && !this->layout[x][y + 2])
        this->flags[used->color][MOVE].set(x, y + 2);
    }
    break;
  case KNIGHT:
    for (int z = 0; z < 4; z++) {
      if (!this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]))
        this->flags[used->color][MOVE].set(x + Kholder[z][0],
                                           y + Kholder[z][1]);
      if (!this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]))
        this->flags[used->color][MOVE].set(x + Kholder[z][1],
                                           y + Kholder[z][0]);
    }
    break;
  case QUEEN:
  case BISHOP:
    for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
      if (chk_layout(z, v))
        break;
      this->flags[used->color][MOVE].set(z, v);
    }
    for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
      if (chk_layout(z, v))
        break;
      this->flags[used->color][MOVE].set(z, v);
    }
    for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
      if (chk_layout(z, v))
        break;
      this->flags[used->color][MOVE].set(z, v);
    }
    for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
      if (chk_layout(z, v))
        break;
      this->flags[used->color][MOVE].set(z, v);
    }
    if (used->typ == BISHOP)
      break;
  case ROOK:
    for (int z = x + 1; z < 8; z++) {
      if (chk_layout(z, y))
        break;
      this->flags[used->color][MOVE].set(z, y);
    }
    for (int z = y + 1; z < 8; z++) {
      if (chk_layout(x, z))
        break;
      this->flags[used->color][MOVE].set(x, z);
    }
    for (int z = x - 1; z > -1; z--) {
      if (chk_layout(z, y))
        break;
      this->flags[used->color][MOVE].set(z, y);
    }
    for (int z = y - 1; z > -1; z--) {
      if (chk_layout(x, z))
        break;
      this->flags[used->color][MOVE].set(x, z);
    }
    break;
  case KING: // tu powinno być puste

    break;
  }
}
void board::_f_guard(const unsigned char x, const unsigned char y) {
  piece *used = this->layout[x][y];
  static const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  switch (used->typ) {
  case PAWN:
    if (used->color == WHITE) {
      if (this->chk_layout(x + 1, y - 1) &&
          this->layout[x + 1][y - 1]->color == used->color)
        this->flags[used->color][GUARD].set(x + 1, y - 1);
      if (this->chk_layout(x - 1, y - 1) &&
          this->layout[x - 1][y - 1]->color == used->color)
        this->flags[used->color][GUARD].set(x - 1, y - 1);

    } else {
      if (this->chk_layout(x + 1, y + 1) &&
          this->layout[x + 1][y + 1]->color == used->color)
        this->flags[used->color][GUARD].set(x + 1, y + 1);
      if (this->chk_layout(x - 1, y + 1) &&
          this->layout[x - 1][y + 1]->color == used->color)
        this->flags[used->color][GUARD].set(x - 1, y + 1);
    }
    break;
  case KNIGHT:
    for (int z = 0; z < 4; z++) {
      if (this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]) &&
          this->layout[x + Kholder[z][0]][y + Kholder[z][1]]->color ==
              used->color)
        this->flags[used->color][GUARD].set(x + Kholder[z][0],
                                            y + Kholder[z][1]);
      if (this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]) &&
          this->layout[x + Kholder[z][1]][y + Kholder[z][0]]->color ==
              used->color)
        this->flags[used->color][GUARD].set(x + Kholder[z][1],
                                            y + Kholder[z][0]);
    }
    break;
  case QUEEN:
  case BISHOP:
    for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color == used->color)
          this->flags[used->color][GUARD].set(z, v);
        break;
      }
    }
    for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color == used->color)
          this->flags[used->color][GUARD].set(z, v);
        break;
      }
    }
    for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color == used->color)
          this->flags[used->color][GUARD].set(z, v);
        break;
      }
    }
    for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color == used->color)
          this->flags[used->color][GUARD].set(z, v);
        break;
      }
    }

    if (used->typ == BISHOP)
      break;
  case ROOK:
    for (int z = x + 1; z < 8; z++) {
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color) {
        this->flags[used->color][GUARD].set(z, y);
        break;
      }
    }
    for (int z = x - 1; z > -1; z--) {
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color) {
        this->flags[used->color][GUARD].set(z, y);
        break;
      }
    }
    for (int z = y + 1; z < 8; z++) {
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color) {
        this->flags[used->color][GUARD].set(x, z);
        break;
      }
    }
    for (int z = y - 1; z > -1; z--) {
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color) {
        this->flags[used->color][GUARD].set(x, z);
        break;
      }
    }
    break;
  case KING: // to trzeba dodać jednak nie

    break;
  }
}
void board::_f_attack(unsigned char x, unsigned char y) {
  piece *used = this->layout[x][y];
  const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  switch (used->typ) {
  case PAWN: // DODAĆ EN PASSANT
    if (used->color == WHITE) {
      if (this->enPassant.passantable &&
          this->enPassant.passantable->color != used->color) {
        if (this->enPassant.y == y &&
            (this->enPassant.x - x == 1 || this->enPassant.x - x == -1)) {
          this->flags[used->color][ATTACK].set(this->enPassant.x,
                                               this->enPassant.y - 1);
        }
      }
      if (this->chk_layout(x + 1, y - 1) &&
          this->layout[x + 1][y - 1]->color != used->color)
        this->flags[used->color][ATTACK].set(x + 1, y - 1);
      if (this->chk_layout(x - 1, y - 1) &&
          this->layout[x - 1][y - 1]->color != used->color)
        this->flags[used->color][ATTACK].set(x - 1, y - 1);
    } else {
      if (this->enPassant.passantable &&
          this->enPassant.passantable->color != used->color) {
        if (this->enPassant.y == y &&
            (this->enPassant.x - x == 1 || this->enPassant.x - x == -1)) {
          this->flags[used->color][ATTACK].set(this->enPassant.x,
                                               this->enPassant.y + 1);
        }
      }
      if (this->chk_layout(x + 1, y + 1) &&
          this->layout[x + 1][y + 1]->color != used->color)
        this->flags[used->color][ATTACK].set(x + 1, y + 1);
      if (this->chk_layout(x - 1, y + 1) &&
          this->layout[x - 1][y + 1]->color != used->color)
        this->flags[used->color][ATTACK].set(x - 1, y + 1);
    }
    break;
  case KNIGHT:
    for (int z = 0; z < 4; z++) {
      if (this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]) &&
          this->layout[x + Kholder[z][0]][y + Kholder[z][1]]->color !=
              used->color)
        this->flags[used->color][ATTACK].set(x + Kholder[z][0],
                                             y + Kholder[z][1]);
      if (this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]) &&
          this->layout[x + Kholder[z][1]][y + Kholder[z][0]]->color !=
              used->color)
        this->flags[used->color][ATTACK].set(x + Kholder[z][1],
                                             y + Kholder[z][0]);
    }
    break;
  case QUEEN:
  case BISHOP:
    for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color != used->color)
          this->flags[used->color][ATTACK].set(z, v);
        break;
      }
    }
    for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color != used->color)
          this->flags[used->color][ATTACK].set(z, v);
        break;
      }
    }
    for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color != used->color)
          this->flags[used->color][ATTACK].set(z, v);
        break;
      }
    }
    for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
      if (chk_layout(z, v)) {
        if (this->layout[z][v]->color != used->color)
          this->flags[used->color][ATTACK].set(z, v);
        break;
      }
    }

    if (used->typ == BISHOP)
      break;
  case ROOK:
    for (int z = x + 1; z < 8; z++) {
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color) {
        this->flags[used->color][ATTACK].set(z, y);
        break;
      }
    }
    for (int z = x - 1; z > -1; z--) {
      if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
        break;
      if (chk_layout(z, y) && this->layout[z][y]->color != used->color) {
        this->flags[used->color][ATTACK].set(z, y);
        break;
      }
    }
    for (int z = y + 1; z < 8; z++) {
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color) {
        this->flags[used->color][ATTACK].set(x, z);
        break;
      }
    }
    for (int z = y - 1; z > -1; z--) {
      if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
        break;
      if (chk_layout(x, z) && this->layout[x][z]->color != used->color) {
        this->flags[used->color][ATTACK].set(x, z);
        break;
      }
    }

    break;
  case KING: // to niby też

    break;
  }
}
BMatrix board::_f_attack_Extra(const char color) {
  BMatrix returner;
  returner.clear();
  const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      if (this->layout[x][y] && this->layout[x][y]->color == color) {
        piece *used = this->layout[x][y];
        switch (this->layout[x][y]->typ) {
        case PAWN:
          if (color == WHITE) {
            if (y - 1 > -1) {
              if (x - 1 > -1)
                returner.set(x - 1, y - 1);
              if (x + 1 < 8)
                returner.set(x + 1, y - 1);
            }
          } else {
            if (y + 1 < 8) {
              if (x - 1 > -1)
                returner.set(x - 1, y + 1);
              if (x + 1 < 8)
                returner.set(x + 1, y + 1);
            }
          }
          break;
        case KNIGHT:
          for (int z = 0; z < 4; z++) {
            if (!this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]))
              returner.set(x + Kholder[z][0], y + Kholder[z][1]);
            if (!this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]))
              returner.set(x + Kholder[z][1], y + Kholder[z][0]);
          }
          break;
        case QUEEN:
        case BISHOP:
          for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
            if (chk_layout(z, v) && (this->layout[z][v]->typ != KING ||
                                     this->layout[z][v]->color == color))
              break;
            returner.set(z, v);
          }
          for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
            if (chk_layout(z, v) && (this->layout[z][v]->typ != KING ||
                                     this->layout[z][v]->color == color))
              break;
            returner.set(z, v);
          }
          for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
            if (chk_layout(z, v) && (this->layout[z][v]->typ != KING ||
                                     this->layout[z][v]->color == color))
              break;
            returner.set(z, v);
          }
          for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
            if (chk_layout(z, v) && (this->layout[z][v]->typ != KING ||
                                     this->layout[z][v]->color == color))
              break;
            returner.set(z, v);
          }
          if (used->typ == BISHOP)
            break;
        case ROOK:
          for (int z = x + 1; z < 8; z++) {
            if (chk_layout(z, y) && (this->layout[z][y]->typ != KING ||
                                     this->layout[z][y]->color == color))
              break;
            returner.set(z, y);
          }
          for (int z = y + 1; z < 8; z++) {
            if (chk_layout(x, z) && (this->layout[x][z]->typ != KING ||
                                     this->layout[x][z]->color == color))
              break;
            returner.set(x, z);
          }
          for (int z = x - 1; z > -1; z--) {
            if (chk_layout(z, y) && (this->layout[z][y]->typ != KING ||
                                     this->layout[z][y]->color == color))
              break;
            returner.set(z, y);
          }
          for (int z = y - 1; z > -1; z--) {
            if (chk_layout(x, z) && (this->layout[x][z]->typ != KING ||
                                     this->layout[x][z]->color == color))
              break;
            returner.set(x, z);
          }
          break;
        }
      }
  return returner;
}

BMatrix board::_f_layout(const char color) {
  BMatrix returner;
  returner.clear();
  const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      if (this->layout[x][y] && this->layout[x][y]->color == color) {
        piece *used = this->layout[x][y];
        switch (this->layout[x][y]->typ) {
        case PAWN:
          if (color == WHITE) {
            if (y - 1 > -1) {
              if (x - 1 > -1)
                returner.set(x - 1, y - 1);
              if (x + 1 < 8)
                returner.set(x + 1, y - 1);
            }
          } else {
            if (y + 1 < 8) {
              if (x - 1 > -1)
                returner.set(x - 1, y + 1);
              if (x + 1 < 8)
                returner.set(x + 1, y + 1);
            }
          }
          break;
        case KNIGHT:
          for (int z = 0; z < 4; z++) {
            if (!this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]))
              returner.set(x + Kholder[z][0], y + Kholder[z][1]);
            if (!this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]))
              returner.set(x + Kholder[z][1], y + Kholder[z][0]);
          }
          break;
        case QUEEN:
        case BISHOP:
          for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
            if (chk_layout(z, v))
              break;
            returner.set(z, v);
          }
          for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
            if (chk_layout(z, v))
              break;
            returner.set(z, v);
          }
          for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
            if (chk_layout(z, v))
              break;
            returner.set(z, v);
          }
          for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
            if (chk_layout(z, v))
              break;
            returner.set(z, v);
          }
          if (used->typ == BISHOP)
            break;
        case ROOK:
          for (int z = x + 1; z < 8; z++) {
            if (chk_layout(z, y))
              break;
            returner.set(z, y);
          }
          for (int z = y + 1; z < 8; z++) {
            if (chk_layout(x, z))
              break;
            returner.set(x, z);
          }
          for (int z = x - 1; z > -1; z--) {
            if (chk_layout(z, y))
              break;
            returner.set(z, y);
          }
          for (int z = y - 1; z > -1; z--) {
            if (chk_layout(x, z))
              break;
            returner.set(x, z);
          }
          break;
        }
      }
  return returner;
}
void board::_f_placed(unsigned char x, unsigned char y) {
  this->flags[this->layout[x][y]->color][PLACED].set(x, y);
}
bool board::flag(unsigned char x, unsigned char y) {
  if (!this->layout[x][y] || (x > 7 || y > 7))
    return false;
  for (int z = 0; z < 4; z++)
    this->flags[this->layout[x][y]->color][z].clear();
  if (x > 7 || y > 7)
    return false;
  if (this->layout[x][y]) {
    _f_placed(x, y);
    _f_attack(x, y);
    _f_move(x, y);
    _f_guard(x, y);
  }
  return true;
}
void board::flag_(unsigned char x, unsigned char y) {
  if (x > 7 || y > 7)
    return;
  if (this->layout[x][y]) {
    _f_placed(x, y);
    _f_attack(x, y);
    _f_move(x, y);
    _f_guard(x, y);
  }
}
void board::flagAll(unsigned char color) {
  for (int x = 0; x < 4; x++)
    this->flags[color][x].clear();
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++) {
      if (this->layout[x][y] && this->layout[x][y]->color == color)
        flag_(x, y);
    }
}
void board::flagAll() {
  for (int x = 0; x < 4; x++) {
    this->flags[WHITE][x].clear();
    this->flags[BLACK][x].clear();
  }
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++) {
      if (this->layout[x][y])
        flag_(x, y);
    }
}
