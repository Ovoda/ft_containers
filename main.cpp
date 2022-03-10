
#include <iostream>
#include <node.hpp>

int main(void) {
  ft::tree<char> _t;

  _t.insert('c');
  _t.insert('a');
  _t.insert('d');
  _t.insert('b');
  _t.insert('e');

  _t.print();

  ft::node<char> *_node;
  _node = _t.search('e');

  std::cout << _node->_value << std::endl;

  return (0);
}