#include <cstdio>

template <typename T, typename V>
auto add(T t, V v) -> decltype(t + v) {
  return t+v;
}

int main() {
  auto s = add(2, 5.4);
  auto t = add(3, 4);
  std::printf("%f %d\n", s, t);
  return 0;
}
