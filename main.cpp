
#include <iostream>
#include <node.hpp>

int main(void) {
  ft::tree<int> _t;

  _t.insert(3);
  _t.insert(1);
  _t.insert(2);

  ft::tree<int>::node_pointer five = _t.search(2);
  _t.remove(five);
  _t.print();

  return (0);
}