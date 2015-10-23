/*
 * Smart pointers
 */

#include <cstdio>
#include <memory>

int main() {
  std::unique_ptr<int> p1(new int(42));
  std::unique_ptr<int> p2 = std::move(p1);

  if (p1) printf("*p1 = %d\n", *(p1.get()));
  if (p2) printf("*p2 = %d\n", *(p2.get()));

  auto s1 = std::make_shared<int>(30);
  std::shared_ptr<int> s2 = s1;

  (*s2)++;

  if (s1) printf("*s1 = %d\n", *(s1.get()));
  if (s2) printf("*s2 = %d\n", *(s2.get()));

  return 0;
}
