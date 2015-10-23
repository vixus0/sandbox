#include <iostream>

int fib (int n) {
  switch (n) {
    case 0: return 0; break;
    case 1: return 1; break;
    default:
            return fib(n-1) + fib(n-2);
  }
}

int main () {
  int n;
  std::cin >> n;
  
  for (int i=0; i<=n; i++) {
    std::cout << i << " " << fib(i) << std::endl;
  }

  return 0;
}
