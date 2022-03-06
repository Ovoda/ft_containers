#include <iostream>
#include <map.hpp>
#include <std_lib.hpp>

int main() {
  ft::map<int, int> _v;
  _v.insert(ft::pair<int, int>(1, 1));
  _v.insert(ft::pair<int, int>(2, 2));
  _v.insert(ft::pair<int, int>(3, 3));
  _v.insert(ft::pair<int, int>(4, 4));

  ft::map<int, int>::reverse_iterator _ite = _v.rbegin();

  for (; _ite != _v.rend(); _ite++) {
    std::cout << _ite->first << std::endl;
  }

  return (0);
}