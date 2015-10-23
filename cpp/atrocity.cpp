#include <cstdio>

int& foo() {
  int* x = new int(3);
  return *x;
}

int main() {
  printf("%d\n", foo());
  foo() = 5;
  printf("%d\n", foo());
}
