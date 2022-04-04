#ifndef BINARY_TREE_ITERATOR_HPP
#define BINARY_TREE_ITERATOR_HPP

#include <iterator.hpp>
#include <tree.hpp>

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
  tree_iterator(const iterator_type &src) : _ptr(src._ptr) {}
  tree_iterator(const node_ptr ptr) : _ptr(ptr) {}
  ~tree_iterator() {}

  node_ptr base() const { return _ptr; }

  iterator_type &operator=(const iterator_type &src) {
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
    if (!_ptr || _ptr->is_leaf) return *this;

    if (!_ptr->right->is_leaf) {
      _ptr = minimum(_ptr->right);
      return *this;
    }

    while (!_ptr->parent->is_leaf && _ptr == _ptr->parent->right) {
      _ptr = _ptr->parent;
    }
    _ptr = _ptr->parent;
    return *this;
  }

  iterator_type operator--(int) {
    iterator_type _tmp = *this;
    operator--();
    return _tmp;
  }

  iterator_type &operator--() {
    if (!_ptr || _ptr->is_leaf) return *this;

    if (!_ptr->left->is_leaf) {
      _ptr = maximum(_ptr->left);
      return *this;
    }

    while (!_ptr->parent->is_leaf && _ptr == _ptr->parent->left) {
      _ptr = _ptr->parent;
    }
    _ptr = _ptr->parent;
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