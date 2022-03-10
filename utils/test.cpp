#include <iostream>

template <class T>
class test {
 public:
  test(int val) : value(val) {}
  test(const test &src) : value(src.value) {}

  test &operator=(const test &rhs) {
    if (*this != rhs) {
      value = rhs.value;
    }
    return *this;
  }
  int value;

  operator test<const int>() { std::cout << "bonjour" << std::endl; }
};

int main(void) {
  test<const int> a(42);
  const int i = 0;

  test<const int> b(42);
  // test<int> b(a);

  // std::cout << "a = " << a.value << std::endl;
  // std::cout << "b = " << b.value << std::endl;
  return 0;
}