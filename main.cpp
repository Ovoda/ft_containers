
#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <iostream>
#include <map.hpp>
#include <string>
#include <utils.hpp>

// ? what happens when begin with empty map, vector, etc...
// |----- SEGV when I do it

int main(void) {
  ft::map<int, int> _m;
  return (0);
}