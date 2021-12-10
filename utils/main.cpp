#include "rbt.hpp"

int main(void) {
  ft::red_black_tree<int> tree;

  tree.insert(5);
  tree.insert(2);
  tree.insert(9);
  tree.insert(3);
  tree.insert(6);
  tree.insert(1);
  tree.traverse(tree.root(), &ft::red_black_tree<int>::print_node);
  tree.check_tree();
  tree.print();
  return (0);
}
