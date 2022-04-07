#ifndef BINARY_TREE_ITERATOR_HPP
#define BINARY_TREE_ITERATOR_HPP

#include <iterator.hpp>
#include <node.hpp>

namespace ft {

template <class T>
class tree_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
 public:
  typedef tree_iterator<T> iterator_type;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type
      value_type;
  typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::reference
      node_reference;

  typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::pointer
      node_ptr;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, T>::reference reference;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            Node<T> >::difference_type difference_type;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            Node<T> >::iterator_category iterator_category;

  tree_iterator() : _ptr(NULL) {}
  tree_iterator(const node_ptr ptr) : _ptr(ptr) {}
  tree_iterator(const tree_iterator<T> &src) { *this = src; }
  ~tree_iterator() {}

  node_ptr base() const { return _ptr; }

  tree_iterator &operator=(const tree_iterator &src) {
    if (this != &src) {
      _ptr = src._ptr;
    }
    return (*this);
  }

  reference operator*() const { return _ptr->data; }

  pointer operator->() const { return &(operator*()); }

  iterator_type operator++(int) {
    iterator_type _tmp = *this;
    operator++();
    return _tmp;
  }

  iterator_type &operator++() {
    if (_ptr->right == _ptr->left && _ptr->parent->parent == _ptr) {
      if (!_ptr->right) {
        _ptr = _ptr->parent;
      } else {
        _ptr = maximum(_ptr->right);
      }
    } else if (_ptr->right) {
      _ptr = _ptr->right;
      while (_ptr->left) _ptr = _ptr->left;
    } else {
      node_ptr y = _ptr->parent;
      while (y && _ptr == y->right) {
        _ptr = y;
        y = y->parent;
      }
      if (_ptr->right != y) _ptr = y;
    }
    return *this;
  }

  iterator_type operator--(int) {
    iterator_type _tmp = *this;
    operator--();
    return _tmp;
  }

  iterator_type &operator--() {
    if (_ptr->left) {
      _ptr = _ptr->left;
      while (_ptr->right) _ptr = _ptr->right;
    } else {
      node_ptr y = _ptr->parent;
      while (_ptr == y->left) {
        _ptr = y;
        y = y->parent;
      }
      if (_ptr->left != y) _ptr = y;
    }
    return *this;
  }

 private:
  node_ptr _ptr;
};

template <class T1, class T2>
bool operator==(const tree_iterator<T1> &_ite1,
                const tree_iterator<T2> &_ite2) {
  return (_ite1.base() == _ite2.base());
}

template <class T1, class T2>
bool operator!=(const tree_iterator<T1> &_ite1,
                const tree_iterator<T2> &_ite2) {
  return (_ite1.base() != _ite2.base());
}

}  // namespace ft
#endif