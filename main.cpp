
#include <map>
#include <set.hpp>
#include <set>

#ifndef STD
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

template <class T>
void print_set(const NAMESPACE::set<T> &_s) {
  NAMESPACE::set<int>::iterator bit = _s.begin();
  NAMESPACE::set<int>::const_iterator cbit = _s.begin();
  NAMESPACE::set<int>::iterator eit = _s.end();
  NAMESPACE::set<int>::const_iterator ceit = _s.end();

  std::cout << "size: " << _s.size() << std::endl;
  std::cout << "max_size: " << _s.max_size() << std::endl;
  std::cout << "empty: " << std::boolalpha << _s.empty() << std::endl;

  for (; bit != eit; bit++) {
    std::cout << *bit << " ";
  }
  std::cout << std::endl;
  for (; cbit != ceit; cbit++) {
    std::cout << *cbit << " ";
  }
  std::cout << std::endl;
}

template <class T>
void constructor_test(const typename NAMESPACE::set<T> &_s) {
  NAMESPACE::set<T> _copy;
  _copy = _s;
  NAMESPACE::set<int> _range(_copy);
  print_set(_s);
  print_set(_copy);
  print_set(_range);
}

template <class T>
void erase_test(typename NAMESPACE::set<T> &_s) {
  typename NAMESPACE::set<T>::iterator it = _s.begin();
  _s.erase(1);
  print_set(_s);
}

int main() {
  NAMESPACE::set<int> _s;
  for (int i = 0; i <= 20; i++) {
    _s.insert(i - 10);
  }
  // constructor_test();
  erase_test(_s);
  return (0);
}