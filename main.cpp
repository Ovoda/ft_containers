#include <iostream>
#include <reverse_iterator.hpp>
#include <std_lib.hpp>
#include <vector.hpp>
#include <vector>

#define NAMESPACE ft

int main() {
  typename NAMESPACE::vector<int> foo;
  typename NAMESPACE::vector<int> bar;

  foo.push_back(100);
  foo.push_back(100);


  bar.push_back(11);
  bar.push_back(22);
  bar.push_back(33);

  typename NAMESPACE::vector<int>::const_iterator _ite = foo.begin();

  std::swap(foo, bar);

  while (_ite != bar.end()) {
    std::cout << *_ite << std::endl;
    _ite++;
  }

  return 0;
}