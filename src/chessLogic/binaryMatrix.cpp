#include "binaryMatrix.h"
#include <stdio.h>
BMatrix::BMatrix() { this->clear(); }
BMatrix::~BMatrix() {}
void BMatrix::set(unsigned const char x, unsigned const char y) {
  if (x < 8 && y < 8)
    this->mx[y] |= (1 << x);
}
void BMatrix::set(unsigned const char x, unsigned const char y,
                 const bool value) {
  if (value)
    this->set(x, y);
  else
    this->mx[x] &= (~(1 << y));
}
bool BMatrix::value(unsigned const char x, unsigned const char y) {
  return (bool)(this->mx[y] & (1 << x));
}
unsigned char BMatrix::allValues() {
  unsigned char a = 0;
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      a += this->value(x, y);
  return a;
}
BMatrix BMatrix::operator&(const BMatrix b) {
  BMatrix a;
  for (int x = 0; x < 8; x++)
    a.mx[x] = this->mx[x] & b.mx[x];
  return a;
}
void BMatrix::operator=(const BMatrix b) {
  for (int x = 0; x < 8; x++)
    this->mx[x] = b.mx[x];
}
void BMatrix::operator&=(const BMatrix b) {
  for (int x = 0; x < 8; x++)
    this->mx[x] &= b.mx[x];
}
BMatrix BMatrix::operator^(const BMatrix b) {
  BMatrix a;
  for (int x = 0; x < 8; x++)
    a.mx[x] = this->mx[x] ^ b.mx[x];
  return a;
}
void BMatrix::operator^=(const BMatrix b) {
  for (int x = 0; x < 8; x++)
    this->mx[x] ^= b.mx[x];
}
BMatrix BMatrix::operator|(const BMatrix b) {
  BMatrix a;
  for (int x = 0; x < 8; x++)
    a.mx[x] = this->mx[x] | b.mx[x];
  return a;
}
void BMatrix::operator|=(const BMatrix b) {
  for (int x = 0; x < 8; x++)
    this->mx[x] |= b.mx[x];
}
void BMatrix::setto(const bool value) {
  if (value)
    for (int x = 0; x < 8; x++)
      this->mx[x] = -1;
  else
    this->clear();
}
void BMatrix::clear() {
  for (int x = 0; x < 8; x++)
    this->mx[x] = 0;
}
void BMatrix::print() {
  puts(" -----------------");
  for (int x = 0; x < 8; x++) {
    printf("| ");
    for (int y = 0; y < 8; y++) {
      if (this->value(y, x))
        printf("\033[1;31m1 \033[0m");
      else
        printf("\033[1;34m0 \033[0m");
    }
    printf("|\n");
  }
  puts(" -----------------");
}
void BMatrix::print(const char text[]) {
  printf("|\033[1;5;36m%s\033[0m|\n", text);
  puts(" -----------------");
  for (int x = 0; x < 8; x++) {
    printf("| ");
    for (int y = 0; y < 8; y++) {
      if (this->value(y, x))
        printf("\033[1;31m1 \033[0m");
      else
        printf("\033[1;34m0 \033[0m");
    }
    printf("|\n");
  }
  puts(" -----------------");
}
