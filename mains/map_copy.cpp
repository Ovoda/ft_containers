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

int main() {
  NAMESPACE::map<int, int> _m;
  _m.insert(NAMESPACE::pair<int, int>(5, 5));
  _m.insert(NAMESPACE::pair<int, int>(1, 1));
  _m.insert(NAMESPACE::pair<int, int>(10, 10));
  _m.insert(NAMESPACE::pair<int, int>(18, 18));
  _m.insert(NAMESPACE::pair<int, int>(3, 3));
  _m.insert(NAMESPACE::pair<int, int>(6, 6));

  NAMESPACE::map<int, int> _m2(_m.begin(), _m.end());
  NAMESPACE::map<int, int> _m3(_m2);
  NAMESPACE::map<int, int> _m4;

  NAMESPACE::map<int, int> _m5 = _m4;
  _m4.insert(_m3.begin(), _m3.end());

  for (NAMESPACE::map<int, int>::iterator _ite = _m.begin(); _ite != _m.end();
       _ite++) {
    std::cout << _ite->first << std::endl;
  }
  for (NAMESPACE::map<int, int>::iterator _ite = _m2.begin(); _ite != _m2.end();
       _ite++) {
    std::cout << _ite->first << std::endl;
  }
  for (NAMESPACE::map<int, int>::iterator _ite = _m3.begin(); _ite != _m3.end();
       _ite++) {
    std::cout << _ite->first << std::endl;
  }
  for (NAMESPACE::map<int, int>::iterator _ite = _m4.begin(); _ite != _m4.end();
       _ite++) {
    std::cout << _ite->first << std::endl;
  }
  for (NAMESPACE::map<int, int>::iterator _ite = _m5.begin(); _ite != _m5.end();
       _ite++) {
    std::cout << _ite->first << std::endl;
  }

  return (0);
}