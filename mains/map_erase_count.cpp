
#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <iostream>
#include <map.hpp>
#include <map>
#include <string>
#include <utils.hpp>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void print_map(ft::map<int, int> &_m) {
  ft::map<int, int>::iterator _ite = _m.begin();

  for (; _ite != _m.end(); _ite++) {
    std::cout << _ite->first << std::endl;
  }
}

int main() {
  NAMESPACE::map<int, int> _m;
  _m.insert(NAMESPACE::pair<int, int>(5, 5));
  _m.insert(NAMESPACE::pair<int, int>(1, 1));
  _m.insert(NAMESPACE::pair<int, int>(10, 10));
  _m.insert(NAMESPACE::pair<int, int>(18, 18));
  _m.insert(NAMESPACE::pair<int, int>(3, 3));
  _m.insert(NAMESPACE::pair<int, int>(7, 7));
  _m.insert(NAMESPACE::pair<int, int>(8, 8));
  _m.insert(NAMESPACE::pair<int, int>(6, 6));

  for (int i = 0; i < 20; i++) {
    std::cout << i;
    if (_m.count(i) > 0)
      std::cout << " is an element of map" << std::endl;
    else
      std::cout << " is not an element of map" << std::endl;
  }

  ft::map<int, int>::iterator it;

  print_map(_m);
  _m.erase(6);
  print_map(_m);
  _m.erase(7);
  print_map(_m);
  _m.erase(3);
  print_map(_m);
  _m.erase(10);
  print_map(_m);
  _m.erase(5);
  print_map(_m);

  return (0);
}