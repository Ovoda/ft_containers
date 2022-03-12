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

  NAMESPACE::map<int, int>::iterator begin = _m.end();
  NAMESPACE::map<int, int>::iterator end = _m.begin();

  begin--;
  for (; begin != end; begin--) {
    std::cout << begin->first << ": " << begin->second << std::endl;
  }
  return 0;
}