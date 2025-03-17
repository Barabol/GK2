#include "../config.h"
#include "binaryMatrix.h"
#include "board.h"
#include <stdio.h>
BMatrix board::kingFlagging(const char color) {
   BMatrix holder, holder2;
   holder.clear();
   for (int y = 0; y < 8; y++)
      for (int x = 0; x < 8; x++) {
         if (this->layout[x][y] && this->layout[x][y]->color != color) {
            holder2 = __k_f(x, y);
            if (holder2.allValues()) {
               holder |= holder2;
               this->szach[color]++;
               holder2.clear();
            }
         }
      }
#ifdef DEBUG
   printf("Szachów: %d\n", this->szach[color]);
#endif
   return holder;
}
BMatrix board::__k_f(const char x, const char y) {
   piece *used = this->layout[x][y];
   BMatrix holder;
   holder.clear();
   const char Kholder[4][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
   switch (used->typ) {
   case PAWN:
      if (used->color == WHITE) {
         if (this->chk_layout(x + 1, y - 1) &&
             this->layout[x + 1][y - 1]->color != used->color &&
             this->layout[x + 1][y - 1]->typ == KING) {
            holder.set(x + 1, y - 1);
            holder.set(x, y);
            return holder;
         }
         if (this->chk_layout(x - 1, y - 1) &&
             this->layout[x - 1][y - 1]->color != used->color &&
             this->layout[x - 1][y - 1]->typ == KING) {
            holder.set(x - 1, y - 1);
            holder.set(x, y);
            return holder;
         }
      } else {
         if (this->chk_layout(x + 1, y + 1) &&
             this->layout[x + 1][y + 1]->color != used->color &&
             this->layout[x + 1][y + 1]->typ == KING) {
            holder.set(x + 1, y + 1);
            holder.set(x, y);
            return holder;
         }
         if (this->chk_layout(x - 1, y + 1) &&
             this->layout[x - 1][y + 1]->color != used->color &&
             this->layout[x - 1][y + 1]->typ == KING) {
            holder.set(x - 1, y + 1);
            holder.set(x, y);
            return holder;
         }
      }
      break;
   case KNIGHT:
      for (int z = 0; z < 4; z++) {
         if (this->chk_layout(x + Kholder[z][0], y + Kholder[z][1]) &&
             this->layout[x + Kholder[z][0]][y + Kholder[z][1]]->color !=
                 used->color &&
             this->layout[x + Kholder[z][0]][y + Kholder[z][1]]->typ == KING) {
            holder.set(x, y);
            return holder;
         }
         if (this->chk_layout(x + Kholder[z][1], y + Kholder[z][0]) &&
             this->layout[x + Kholder[z][1]][y + Kholder[z][0]]->color !=
                 used->color &&
             this->layout[x + Kholder[z][1]][y + Kholder[z][0]]->typ == KING) {
            holder.set(x, y);
            return holder;
         }
      }
      break;
   case QUEEN:
   case BISHOP:
      for (int z = x + 1, v = y + 1; z < 8 && v < 8; z++, v++) {
         holder.set(z, v);
         if (chk_layout(z, v)) {
            if (this->layout[z][v]->color != used->color &&
                this->layout[z][v]->typ == KING) {
               holder.set(z, v);
               holder.set(x, y);
               return holder;
            }
            break;
         }
      }
      holder.clear();
      for (int z = x - 1, v = y + 1; z > -1 && v < 8; z--, v++) {
         holder.set(z, v);
         if (chk_layout(z, v)) {
            if (this->layout[z][v]->color != used->color &&
                this->layout[z][v]->typ == KING) {
               holder.set(z, v);
               holder.set(x, y);
               return holder;
            }
            break;
         }
      }
      holder.clear();
      for (int z = x + 1, v = y - 1; z < 8 && v > -1; z++, v--) {
         holder.set(z, v);
         if (chk_layout(z, v)) {
            if (this->layout[z][v]->color != used->color &&
                this->layout[z][v]->typ == KING) {
               holder.set(z, v);
               holder.set(x, y);
               return holder;
            }
            break;
         }
      }
      holder.clear();
      for (int z = x - 1, v = y - 1; z > -1 && v > -1; z--, v--) {
         holder.set(z, v);
         if (chk_layout(z, v)) {
            if (this->layout[z][v]->color != used->color &&
                this->layout[z][v]->typ == KING) {
               holder.set(z, v);
               holder.set(x, y);
               return holder;
            }
            break;
         }
      }
      holder.clear();
      if (used->typ == BISHOP)
         break;
   case ROOK:
      for (int z = x + 1; z < 8; z++) {
         holder.set(z, y);
         if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
            break;
         if (this->layout[z][y] && this->layout[z][y]->color != used->color &&
             this->layout[z][y]->typ == KING) {
            holder.set(z, y);
            holder.set(x, y);
            return holder;
         }
      }
      holder.clear();
      for (int z = x - 1; z > -1; z--) {
         holder.set(z, y);
         if (chk_layout(z, y) && this->layout[z][y]->color == used->color)
            break;
         if (this->layout[z][y] && this->layout[z][y]->color != used->color &&
             this->layout[z][y]->typ == KING) {
            holder.set(z, y);
            holder.set(x, y);
            return holder;
         }
      }
      holder.clear();
      for (int z = y + 1; z < 8; z++) {
         holder.set(x, z);
         if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
            break;
         if (this->layout[x][z] && this->layout[x][z]->color != used->color &&
             this->layout[x][z]->typ == KING) {
            holder.set(x, z);
            holder.set(x, y);
            return holder;
         }
      }
      holder.clear();
      for (int z = y - 1; z > -1; z--) {
         holder.set(x, z);
         if (chk_layout(x, z) && this->layout[x][z]->color == used->color)
            break;
         if (this->layout[x][z] && this->layout[x][z]->color != used->color &&
             this->layout[x][z]->typ == KING) {
            holder.set(x, z);
            holder.set(x, y);
            return holder;
         }
      }
      holder.clear();
      break;
   case KING: // to niby też

      break;
   }
   return holder;
}
