/*
 * Lambda expressions
 */

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  std::vector<int> a;

  for (int i=0; i<20; i++) a.push_back(i);

  std::for_each(a.begin(), a.end(), [] (int i) {
    if (i%3==0)
      std::printf("fizz ");
    else if
      (i%5==0) std::printf("buzz ");
    else
      std::printf("%d ", i);
  });

  std::printf("\n");

  return 0;
}
