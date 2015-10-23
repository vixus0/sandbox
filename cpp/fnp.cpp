#include <cstdio>

int balls(int x) { return x*2; }

int (*rballs(double a))(int) { 
  printf("rballs %f\n", a);
  return balls; 
}

void printo(int (*f)(int), int x) {
  printf("%d\n", f(x));
}

int main() {
  printo(rballs(3.2), 5);
  return 0;
}
