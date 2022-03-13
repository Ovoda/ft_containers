
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

template <class Key, class T>
void print(NAMESPACE::map<Key, T>& lst) {
  for (typename NAMESPACE::map<Key, T>::iterator it = lst.begin();
       it != lst.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';
}

int main() {
  ft::map<char, int> _m;
  ft::map<char, int>::iterator it;

  _m['a'] = 10;
  _m['b'] = 20;
  _m['c'] = 30;
  _m['d'] = 40;
  _m['e'] = 50;
  _m['f'] = 60;

  // it = _m.find('b');
  // _m.erase(it);  // erasing by iterator

  // _m.erase('e');  // erasing by key
  _m.erase('f');  // erasing by key

  // it = _m.find('e');
  // _m.erase(it, _m.end());  // erasing by range

  // show content:
  for (it = _m.begin(); it != _m.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}