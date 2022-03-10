#ifndef NODE_HPP
#define NODE_HPP

#include <std_lib.hpp>

namespace ft {

template <class T>
class node {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef node<T> node_type;
  typedef node_type& node_reference;
  typedef const node_type& node_const_reference;
  typedef node_type* node_pointer;
  typedef const node_type* node_const_pointer;

  typedef std::allocator<node_type> alloc_type;

  node(const value_type& value, node_type* right = nullptr,
       node_type* left = nullptr, node_type* parent = nullptr)
      : _value(value), _right(right), _left(left), _parent(parent) {}

  ~node() {
    if (_right) {
      _alloc.destroy(_right);
      _alloc.deallocate(_right, 1);
    }
    if (_left) {
      _alloc.destroy(_left);
      _alloc.deallocate(_left, 1);
    }
  }

  node_type& operator=(node_type rhs) {
    if (this != &rhs) {
      _right = rhs._right;
      _left = rhs._left;
      _parent = rhs._parent;
      _value = rhs._value;
    }
    return (*this);
  }

  node_pointer min() {
    node_pointer tmp = this;
    while (tmp->_left) tmp = tmp->_left;
    return tmp;
  }

  node_pointer max() {
    node_pointer tmp = this;
    while (tmp->_right) tmp = tmp->_right;
    return tmp;
  }

  bool is_left_child() {
    return ((_parent != nullptr && _parent->_left == this) ? true : false);
  }

  bool is_right_child() {
    return ((_parent != nullptr && _parent->_right == this) ? true : false);
  }

  bool is_left_leaf() {
    return ((is_left_child() && !_right && !_left) ? true : false);
  }

  bool is_right_leaf() {
    return ((is_right_child() && !_right && !_left) ? true : false);
  }

  ft::pair<node_pointer, bool> insert(node_type src) {
    if (src._value > _value) {
      if (!_right) {
        _right = _alloc.allocate(1);
        _alloc.construct(_right, src);
        _right->_parent = this;
      } else {
        return (_right->insert(src));
      }
      return ft::make_pair(_right, true);
    } else if (src._value < _value) {
      if (!_left) {
        _left = _alloc.allocate(1);
        _alloc.construct(_left, src);
        _left->_parent = this;
      } else {
        return (_left->insert(src));
      }
      return ft::make_pair(_left, true);
    }
    return ft::make_pair(this, false);
  }

  node_pointer _right;
  node_pointer _left;
  node_pointer _parent;
  value_type _value;
  alloc_type _alloc;
};

template <class T, class Alloc = std::allocator<ft::node<T> > >
class tree {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef Alloc alloc_type;

  typedef typename node<T>::node_type node_type;
  typedef node_type& node_reference;
  typedef const node_type& node_const_reference;
  typedef node_type* node_pointer;
  typedef const node_type* node_const_pointer;

  tree() : _root(nullptr) {}
  ~tree() {
    _alloc.destroy(_root);
    _alloc.deallocate(_root, 1);
  }

  ft::pair<node_pointer, bool> insert(node_type node) {
    return (_root->insert(node));
  }

  ft::pair<node_pointer, bool> insert(value_type value) {
    if (!_root) {
      _root = _alloc.allocate(1);
      _alloc.construct(_root, node_type(value));
      return (make_pair(_root, true));
    }
    node_type _new_node(value);
    return (insert(_new_node));
  }

  node_pointer search(node_pointer _node, value_type value) {
    if (!_node) return nullptr;
    if (value > _node->_value) {
      return search(_node->_right, value);
    } else if (value < _node->_value) {
      return search(_node->_left, value);
    }
    return (_node);
  }

  node_pointer search(value_type value) { return search(_root, value); }

  bool is_empty() { return (_root == nullptr); }

  void print(node_pointer root, int space = 0) {
    if (root == NULL) return;
    space += 5;
    print(root->_right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++) std::cout << " ";
    std::cout << root->_value << "\n";
    print(root->_left, space);
  }

  void print() { print(_root, 0); }

 private:
  node_pointer _root;
  alloc_type _alloc;
};

}  // namespace ft

#endif