
#include <iostream>
#include <node.hpp>

int main(void) {
  ft::tree<int> _t;

    _t.insert(50);
    _t.insert(40);
    _t.insert(70);
    _t.insert(60);
    _t.insert(80);

  _t.print();
  // ft::tree<int>::node_pointer five = _t.search(2);
  _t.remove(50);
  _t.print();

  return (0);
}