
#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <iostream>
#include <map>
#include <std_lib.hpp>
#include <string>

// ? what happens when begin with empty map, vector, etc...
// |----- SEGV when I do it

int main(void) {
  ft::tree<int> _t;
  _t.insert(8);
  _t.insert(3);
  _t.insert(10);
  // _t.insert(ft::pair<int, std::string>(3, "three"));
  // _t.insert(ft::pair<int, std::string>(4, "four"));
  // _t.insert(ft::pair<int, std::string>(8, "eight"));
  // _t.insert(ft::pair<int, std::string>(6, "six"));
  // _t.insert(ft::pair<int, std::string>(1, "one"));
  // _t.insert(ft::pair<int, std::string>(2, "two"));

  // _t.print();

  ft::tree_iterator<int> _ite = _t._root->min();

  std::cout << *_ite << std::endl;
  ++_ite;
  std::cout << *_ite << std::endl;
  _ite++;
  std::cout << *_ite << std::endl;

  std::cout << std::endl;

  std::cout << *_ite << std::endl;
  _ite--;
  std::cout << *_ite << std::endl;
  --_ite;
  std::cout << *_ite << std::endl;

  //   _t.insert(50);
  //   _t.insert(40);
  //   _t.insert(70);
  //   _t.insert(60);
  //   _t.insert(80);

  // _t.print();
  // // ft::tree<int>::node_pointer five = _t.search(2);
  // _t.remove(50);
  // _t.print();

  // std::map<int, int> _m;
  // _m.insert(std::make_pair<int, int>(3, 3));
  // _m.insert(std::make_pair<int, int>(1, 1));
  // _m.insert(std::make_pair<int, int>(2, 2));
  // _m.insert(std::make_pair<int, int>(4, 4));
  // _m.insert(std::make_pair<int, int>(5, 5));
  // _m.insert(std::make_pair<int, int>(6, 6));
  // _m.insert(std::make_pair<int, int>(7, 7));

  // std::map<int, int>::iterator _ite = _m.begin();

  // for (; _ite != _m.end(); _ite++) {
  //   std::cout << _ite->first << ": " << _ite->second << std::endl;
  // }

  return (0);
}