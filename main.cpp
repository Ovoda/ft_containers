
#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <iostream>
#include <map.hpp>
#include <string>
#include <utils.hpp>

// ? what happens when begin with empty map, vector, etc...
// |----- SEGV when I do it

int main() {
  ft::map<char, int> mymap;

  // first insert function version (single parameter):
  mymap.insert(ft::pair<char, int>('a', 100));
  mymap.insert(ft::pair<char, int>('z', 200));

  ft::pair<ft::map<char, int>::iterator, bool> ret;
  ret = mymap.insert(ft::pair<char, int>('z', 500));
  if (ret.second == false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  ft::map<char, int>::iterator it = mymap.begin();

  std::cout << "mymap contains:\n";
  for (it = mymap.begin(); it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}