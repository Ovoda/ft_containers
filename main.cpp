#include <tree.hpp>

int main(void) {
  red_black_tree<int> _t;

  _t.insert(1);
  _t.insert(2);
  _t.insert(3);
  _t.insert(4);
  _t.insert(5);
  _t.insert(6);
  _t.insert(7);
  _t.insert(8);
  _t.insert(9);

  // _t.delete_node(9);
  // _t.delete_node(8);
  // _t.delete_node(7);
  // _t.delete_node(6);
  // _t.delete_node(5);
  _t.delete_node(4);
  // _t.delete_node(3);
  // _t.delete_node(2);
  // _t.delete_node(1);

  _t.print2D();
  return (0);
}
