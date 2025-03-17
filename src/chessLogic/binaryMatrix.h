#ifndef __BINARY_MATRIX__
#define __BINARY_MATRIX__
class BMatrix {
 public:
   BMatrix();
   ~BMatrix();
   void set(unsigned const char x, unsigned const char y);
   void set(unsigned const char x, unsigned const char y, const bool value);
   bool value(unsigned const char x, unsigned const char y);
   unsigned char allValues();
   BMatrix operator&(const BMatrix b);
   void operator=(const BMatrix b);
   void operator&=(const BMatrix b);
   BMatrix operator^(const BMatrix b);
   void operator^=(const BMatrix b);
   BMatrix operator|(const BMatrix b);
   void operator|=(const BMatrix b);
   void setto(const bool value);
   void print();
   void print(const char text[]);
   void clear();

 private:
   char mx[8];
};
#endif
