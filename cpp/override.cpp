#include <cstdio>

class Op {
  public:
    virtual int f(int, int) = 0;
};

class Add : public Op {
  public:
    virtual int f(int a, int b) override {return a+b;}
};

class Mult : public Op {
  public:
    virtual int f(int a, int b) override {return a*b;}
};

int main() {
  Add a;
  Mult m;

  printf("%d %d\n", a.f(2,3), m.f(2,3));
  
  return 0;
}
