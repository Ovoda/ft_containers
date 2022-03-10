#include <string>
#include <vector.hpp>
#include <vector>

template <class T>
void print_vector(typename NAMESPACE::vector<T> &_v) {
  for (int i = 0; i < _v.size(); i++) {
    std::cout << _v[i];
  }
}

template <class T>
int swap_test(T _data1, T _data2) {
  typename NAMESPACE::vector<T> _v0(5, _data1);
  typename NAMESPACE::vector<T> _v1(2, _data2);
  std::vector<std::string> _addr_storage;

  typename NAMESPACE::vector<T>::iterator _begin0 = _v0.begin();
  typename NAMESPACE::vector<T>::iterator _end0 = _v0.end();
  typename NAMESPACE::vector<T>::iterator _begin1 = _v1.begin();
  typename NAMESPACE::vector<T>::iterator _end1 = _v1.end();
  print_vector<T>(_v0);
  print_vector<T>(_v1);
  _v0.swap(_v1);
  print_vector<T>(_v0);
  print_vector<T>(_v1);
  _v1.swap(_v0);
  print_vector<T>(_v0);
  print_vector<T>(_v1);

  return 0;
}

int main() {
  swap_test<int>(42, 43);
  swap_test<bool>(true, false);
  swap_test<std::string>("Bonjour, le monde!", "Hello, World!");
  swap_test<char>('B', 'H');
  return (0);
}