
#include <iostream>
#include <string>

#include "map.hpp"
#include "pair_node.hpp"

// void print(ft::map_pair<const int, int> *root, int space) {
//   if (root == nullptr) return;
//   space += 10;
//   print(root->right(), space);
//   std::cout << std::endl;
//   for (int i = 10; i < space; i++) std::cout << " ";
//   std::cout << root->data() << std::endl;
//   print(root->left(), space);
// }

int main(void) {
  ft::pair<int, int> one(1, 40);
  ft::pair<int, int> two(2, 41);

  ft::map<int, int> m;
  m.insert(one);
  m.insert(two);
  return (0);
}
