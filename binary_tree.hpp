#ifndef NODE_HPP
#define NODE_HPP

#include <utils.hpp>

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

  // node(node_type* parent = nullptr, node_type* right = nullptr,
  //      node_type* left = nullptr)
  //     : _value(value_type()), _parent(parent), _right(right), _left(left) {}

  /* Helpers */

  bool is_mutual_parents() {
    if (_parent != nullptr && _parent->_parent != nullptr)
      return ((_parent->_parent == this) ? true : false);
    return false;
  }

  bool is_left_child() {
    if (is_mutual_parents()) return false;
    return ((_parent != nullptr && _parent->_left == this) ? true : false);
  }

  bool is_right_child() {
    if (is_mutual_parents()) return false;
    return ((_parent != nullptr && _parent->_right == this) ? true : false);
  }

  bool is_left_leaf() {
    return ((is_left_child() && !_right && !_left) ? true : false);
  }

  bool is_right_leaf() {
    return ((is_right_child() && !_right && !_left) ? true : false);
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

  value_type _value;
  node_pointer _parent;
  node_pointer _right;
  node_pointer _left;
  alloc_type _alloc;
};

template <class T, class Alloc = std::allocator<ft::node<T>>>
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

  tree() : _root(nullptr) { _end = new node_type(value_type()); }
  ~tree() {
    delete_tree(_root);
    delete _end;
  }

  node_pointer begin() {
    if (!_root) return nullptr;
    return _root->min();
  }

  node_pointer end() { return _end; }

  /* Insert - Search - Remove*/

  /* Insert */
  ft::pair<node_pointer, bool> insert(value_type value) {
    ft::pair<node_pointer, bool> _ret = insert(_root, value, nullptr);
    _root->_parent = _end;
    _end->_parent = _root;
    _end->_right = _root;
    _end->_left = _root;
    return (_ret);
  }

  ft::pair<node_pointer, bool> insert(node_pointer& _curr, value_type& value,
                                      node_pointer _parent) {
    if (!_curr) {
      _curr = _alloc.allocate(1);
      _alloc.construct(_curr, node_type(value, _parent));
      return (ft::make_pair(_curr, true));
    }
    if (value > _curr->_value) {
      return (insert(_curr->_right, value, _curr));
    } else if (value < _curr->_value) {
      return (insert(_curr->_left, value, _curr));
    }
    return ft::make_pair(_curr, false);
  }

  /* Search */
  node_pointer search(value_type value) { return search(_root, value); }

  node_pointer search(node_pointer _node, value_type value) {
    if (!_node) return nullptr;
    if (value > _node->_value) {
      return search(_node->_right, value);
    } else if (value < _node->_value) {
      return search(_node->_left, value);
    }
    return (_node);
  }

  /* Remove */
  void remove(value_type value) { remove(search(value)); }

  void remove(node_pointer _curr) {
    if (!_curr->_right && !_curr->_left) {
      destroy_node(_curr);
    } else if (_curr->_right && _curr->_left) {
      node_pointer inorder_successor = min(_curr->_right);
      _curr->_value = inorder_successor->_value;
      destroy_node(inorder_successor);
    } else if (_curr->_right && !_curr->_left) {
      _curr->_value = _curr->_right->_value;
      destroy_node(_curr->_right);
    } else if (_curr->_left && !_curr->_right) {
      _curr->_value = _curr->_left->_value;
      destroy_node(_curr->_left);
    }
  }

  /* Helper functions */

  /* Printing helper */
  void print_node(node_pointer _curr) {
    if (!_curr) return;
    std::cout << _curr->_value << ": ";
    if (_curr->_parent == nullptr)
      std::cout << "nullptr" << std::endl;
    else {
      std::cout << _curr->_parent->_value << std::endl;
    }
  }

  void print(node_pointer root, int space = 0) {
    if (root == NULL) return;
    space += 5;
    print(root->_right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++) std::cout << " ";
    std::cout << root->_value.first << "\n";
    print(root->_left, space);
  }

  void print() { print(_root, 0); }

  bool is_end(node_pointer _curr) {
    node<T>* tmp = _curr;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->max() == _curr;
  }

  bool is_begin(node_pointer _curr) {
    node<T>* tmp = _curr;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->min() == _curr;
  }

  /* Destroying helpers */
  node_pointer destroy_node(node_pointer _curr) {
    if (_curr == _end) return nullptr;
    node_pointer tmp_parent = nullptr;
    bool is_left = false;
    if (_curr->_parent) {
      tmp_parent = _curr->_parent;
      is_left = _curr->is_left_child() ? true : false;
    }
    _alloc.destroy(_curr);
    _alloc.deallocate(_curr, 1);
    if (tmp_parent != nullptr && !is_left) {
      tmp_parent->_right = nullptr;
    } else if (tmp_parent && is_left) {
      tmp_parent->_left = nullptr;
    }
    return (tmp_parent);
  }

  void delete_tree(node_pointer _curr) {
    if (!_curr) return;
    if (_curr->_right) {
      delete_tree(_curr->_right);
    }
    if (_curr->_left) {
      delete_tree(_curr->_left);
    }
    destroy_node(_curr);
  }

  bool is_empty() { return (_root == nullptr); }

  // TODO put _root private
  node_pointer _root;

 private:
  alloc_type _alloc;
  node_pointer _end;
};

}  // namespace ft

#endif