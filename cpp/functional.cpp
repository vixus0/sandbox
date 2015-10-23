#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename It>
int balls(It begin, It end) {
  auto is_odd = [](int n) { return n%2 == 1; };
  auto pos = std::find_if(begin, end, is_odd);
  return (pos != end)? *pos : -1;
}

template <typename T, size_t N>
int first_odd(T(&arr)[N]) {
  return balls(std::begin(arr), std::end(arr));
}

template <typename T>
int first_odd(T t) {
  return balls(std::begin(t), std::end(t));
}

int main() {
  int arr[] = {2,3,4,5,6,7,8,9};
  std::vector<int> vec;

  for (auto it = std::begin(arr); it != std::end(arr); it++) {
    vec.push_back(*it);
  }

  auto i = first_odd(arr);
  auto j = first_odd(vec);

  printf("%d %d\n", i, j);

  return 0;
}
