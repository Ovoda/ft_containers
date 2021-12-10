#include "rbt.hpp"

int main(void) {
  ft::red_black_tree<int> tree;

  tree.insert(100);
  // right
  tree.insert(200);
  //   tree.insert(250);
  //   tree.insert(150);
  // left
  tree.insert(50);
  //   tree.insert(75);
  tree.insert(25);

  //   tree.insert(76);
  //   tree.insert(74);
  //   tree.insert(26);
  //   tree.insert(24);

  //   tree.traverse(tree.root(), &ft::red_black_tree<int>::print_node);
  //   tree.check_tree();
  tree.print();
  return (0);
}
