#include <cstdio>

struct face {
  static int x;
};

int face::x = 3;

class a {};

int main() {
  a b;
  a c;
  c = b;
  std::printf("%d\n", face::x);
}
