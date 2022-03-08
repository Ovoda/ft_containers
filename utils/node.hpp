#ifndef FT_NODE_HPP
#define FT_NODE_HPP

#include <map_iterator.hpp>
#include <std_lib.hpp>

namespace ft {

template <class T>
class node {
 public:
  node() : _right(nullptr), _left(nullptr), _parent(nullptr) {}
  node(T src)
      : _right(nullptr), _left(nullptr), _parent(nullptr), _pair(T(src)) {}
  ~node() {}

  node<T> &operator=(node<T> rhs) {
    if (this != &rhs) {
      _right = rhs._right;
      _left = rhs._left;
      _pair = rhs._pair;
      _parent = rhs._parent;
    }
    return *this;
  }

  // getters
  T &data() { return (_pair); }
  node *parent() const { return (_parent); }
  node *left() const { return (_left); }
  node *right() const { return (_right); }

  node<T> *min() {
    node<T> *tmp = this;
    while (tmp->_left) {
      tmp = tmp->_left;
    }
    return tmp;
  }

  node<T> *max() {
    node<T> *tmp = this;
    while (tmp->_right) {
      tmp = tmp->_right;
    }
    return tmp;
  }

  bool is_end() {
    node<T> *tmp = this;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->max() == this;
  }

  bool is_begin() {
    node<T> *tmp = this;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->min() == this;
  }

  bool is_left_child() {
    if (_parent != nullptr && _parent->left() == this) {
      return true;
    }
    return false;
  }

  bool is_right_child() {
    if (_parent != nullptr && _parent->right() == this) {
      return true;
    }
    return false;
  }

  bool is_left_leaf() {
    if (is_left_child() && !_right && !_left) {
      return true;
    }
    return false;
  }

  bool is_right_leaf() {
    if (is_right_child() && !_right && !_left) {
      return true;
    }
    return false;
  }

  // setters
  void set_left(node *src) { _left = src; }
  void set_right(node *src) { _right = src; }
  void set_pair(T src) { _pair = src; }

  pair<node *, bool> insert(T src) {
    if (src.first > _pair.first) {
      if (_right == nullptr) {
        _right = _alloc.allocate(sizeof(src));
        _alloc.construct(_right, src);
        _right->_parent = this;
      } else {
        return (_right->insert(src));
      }
      return make_pair(_right, true);
    } else if (src.first < _pair.first) {
      if (_left == nullptr) {
        _left = _alloc.allocate(sizeof(src));
        _alloc.construct(_left, src);
        _left->_parent = this;
      } else {
        return (_left->insert(src));
      }
      return make_pair(_left, true);
    }
    return make_pair(this, false);
  }

  // TODO : change return function
  node *search(typename T::first_type const &key) {
    if (key == _pair.first) {
      return this;
    } else if (_right && key > _pair.first) {
      return _right->search(key);
    } else if (_left && key < _pair.first) {
      return _left->search(key);
    }
    return nullptr;
  }

  node *_right;
  node *_left;
  node *_parent;
  T _pair;
 private:
  std::allocator<ft::node<T> > _alloc;
};

}  // namespace ft

#endif