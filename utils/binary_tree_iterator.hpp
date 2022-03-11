#ifndef BINARY_TREE_ITERATOR_HPP
#define BINARY_TREE_ITERATOR_HPP

#include <binary_tree.hpp>
#include <iterator.hpp>

namespace ft {

template <class T>
class tree_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
 public:
  typedef tree_iterator<T> iterator_type;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type
      value_type;
  typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::reference
      node_reference;
  typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::pointer
      node_pointer;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, T>::reference reference;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T>>::difference_type difference_type;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T>>::iterator_category iterator_category;

  tree_iterator() : _ptr(nullptr) {}
  tree_iterator(const iterator_type &src) : _ptr(src._ptr) {}
  tree_iterator(const node_pointer ptr) : _ptr(ptr) {}
  ~tree_iterator() {}

  iterator_type &operator=(const iterator_type &src) {
    if (*this != src) {
      _ptr = src._ptr;
    }
    return (*this);
  }

  bool operator==(const iterator_type &b) { return (_ptr == b._ptr); }

  bool operator!=(const iterator_type &b) { return (!operator==(b)); }

  reference operator*() const { return _ptr->_value; }

  pointer operator->() { return &(operator*()); }

  iterator_type operator++(int) {
    iterator_type _tmp = *this;
    operator++();
    return _tmp;
  }

  iterator_type &operator++() {
    if (_ptr) {
      if (_ptr->is_right_leaf()) {
        while (_ptr->is_right_child()) {
          _ptr = _ptr->_parent;
        }
        _ptr = _ptr->_parent;
      } else if (_ptr->is_left_leaf() || !_ptr->_right) {
        _ptr = _ptr->_parent;
      } else if (_ptr->_right) {
        _ptr = _ptr->_right;
        _ptr = _ptr->min();
      }
    }
    return *this;
  }

  iterator_type operator--(int) {
    iterator_type _tmp = *this;
    operator--();
    return _tmp;
  }

  iterator_type &operator--() {
    if (_ptr) {
      if (_ptr->is_left_leaf()) {
        while (_ptr->is_left_child()) {
          _ptr = _ptr->_parent;
        }
        _ptr = _ptr->_parent;
      } else if (_ptr->is_right_leaf() || !_ptr->_left) {
        _ptr = _ptr->_parent;
      } else if (_ptr->_left) {
        _ptr = _ptr->_left->max();
      }
    }
    return *this;
  }

 private:
  node_pointer _ptr;
};

}  // namespace ft
#endif