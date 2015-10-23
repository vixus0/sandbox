#include <iostream>

class A { 
  public:
    int balls = 3; 
};

int main() {
  int x = int();
  A y = A();

  std::cout << x << std::endl;
  x = 000000001;
  std::cout << x << std::endl;
  std::cout << y.balls << std::endl;
}
