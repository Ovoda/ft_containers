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

  node(const value_type& value, node_type* parent = nullptr,
       node_type* right = nullptr, node_type* left = nullptr)
      : _value(value), _parent(parent), _right(right), _left(left) {}

  ~node() {}

  // node_type& operator=(node_type rhs) {
  //   if (this != &rhs) {
  //     _right = rhs._right;
  //     _left = rhs._left;
  //     _parent = rhs._parent;
  //     _value = rhs._value;
  //   }
  //   return (*this);
  // }

  value_type _value;
  node_pointer _parent;
  node_pointer _right;
  node_pointer _left;
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
    delete_tre
  }

  ft::pair<node_pointer, bool> insert(value_type value) {
    return (insert(_root, value, nullptr));
  }

  ft::pair<node_pointer, bool> insert(node_pointer& _curr, value_type value,
                                      node_pointer _parent) {
    if (!_curr) {
      _curr = _alloc.allocate(1);
      _alloc.construct(_curr, node_type(value, _parent));
      return (make_pair(_curr, true));
    }
    if (value > _curr->_value) {
      return (insert(_curr->_right, value, _curr));
    } else if (value < _curr->_value) {
      return (insert(_curr->_left, value, _curr));
    }
    return ft::make_pair(_curr, false);
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

  void print_node(node_pointer _curr) {
    if (!_curr) return;
    std::cout << _curr->_value << ": ";
    if (_curr->_parent == nullptr)
      std::cout << "nullptr" << std::endl;
    else {
      std::cout << _curr->_parent->_value << std::endl;
    }
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

  bool is_left_child(node_pointer _curr) {
    return ((_curr->_parent != nullptr && _curr->_parent->_left == _curr)
                ? true
                : false);
  }

  bool is_right_child(node_pointer _curr) {
    return ((_curr->_parent != nullptr && _curr->_parent->_right == _curr)
                ? true
                : false);
  }

  bool is_left_leaf(node_pointer _curr) {
    return ((is_left_child(_curr) && !_curr->_right && !_curr->_left) ? true
                                                                      : false);
  }

  bool is_right_leaf(node_pointer _curr) {
    return ((is_right_child(_curr) && !_curr->_right && !_curr->_left) ? true
                                                                       : false);
  }

  node_pointer min(node_pointer _curr) {
    node_pointer tmp = _curr;
    while (tmp->_left) tmp = tmp->_left;
    return tmp;
  }

  node_pointer max(node_pointer _curr) {
    node_pointer tmp = _curr;
    while (tmp->_right) tmp = tmp->_right;
    return tmp;
  }

  node_pointer destroy_node(node_pointer _curr) {
    node_pointer tmp_parent = nullptr;
    bool is_left = false;
    if (_curr->_parent) {
      tmp_parent = _curr->_parent;
      is_left = is_left_child(_curr) ? true : false;
    }
    _alloc.destroy(_curr);
    _alloc.deallocate(_curr, 1);
    if (tmp_parent && !is_left) {
      tmp_parent->_right = nullptr;
    } else if (tmp_parent && is_left) {
      tmp_parent->_left = nullptr;
    }
    return (tmp_parent);
  }

  void remove(node_pointer _curr) {
    if (!_curr->_right && !_curr->_left) {
      destroy_node(_curr);
    }
  }

  delete_tree(node_pointer _curr) {
    if (!_curr->_right && !_curr->_left) {
      destroy_node(_curr);
    }
    if (_curr->_right) {
      delete_tree(_curr->_right);
    }
    if (_curr->_left) {
      delete_tree(_curr->_left);
    }
  }

 private:
  node_pointer _root;
  alloc_type _alloc;
};

}  // namespace ft

#endif