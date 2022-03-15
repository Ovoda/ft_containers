#ifndef BINARY_TREE_ITERATOR_HPP
#define BINARY_TREE_ITERATOR_HPP

#include <binary_tree.hpp>
#include <iterator.hpp>

namespace ft
{

template <class T>
class tree_iterator : public iterator<ft::bidirectional_iterator_tag, T>
{
public:
  typedef tree_iterator<T> iterator_type;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type
      value_type;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, node<T> >::reference
          node_reference;

  typedef typename iterator<ft::bidirectional_iterator_tag, node<T> >::pointer
      node_pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag, T>::reference
      reference;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T> >::difference_type difference_type;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T> >::iterator_category iterator_category;

  tree_iterator () : _ptr (NULL) {}
  tree_iterator (const iterator_type &src) : _ptr (src._ptr) {}
  tree_iterator (const node_pointer ptr) : _ptr (ptr) {}
  ~tree_iterator () {}

  node_pointer
  base () const
  {
    return _ptr;
  }

  iterator_type &
  operator= (const iterator_type &src)
  {
    if (*this != src)
      {
        _ptr = src._ptr;
      }
    return (*this);
  }

  reference
  operator* () const
  {
    return _ptr->_value;
  }

  pointer
  operator-> () const
  {
    return &(operator* ());
  }

  iterator_type
  operator++ (int)
  {
    iterator_type _tmp = *this;
    operator++ ();
    return _tmp;
  }

  iterator_type &
  operator++ ()
  {
    if (!_ptr)
      return *this;

    if (_ptr->_right)
      {
        _ptr = _ptr->_right->min ();
        return *this;
      }

    while (_ptr->is_right_child ())
      {
        _ptr = _ptr->_parent;
      }
    _ptr = _ptr->_parent;
    return *this;
  }

  iterator_type
  operator-- (int)
  {
    iterator_type _tmp = *this;
    operator-- ();
    return _tmp;
  }

  iterator_type &
  operator-- ()
  {
    if (!_ptr)
      return *this;

    if (_ptr->_left)
      {
        _ptr = _ptr->_left->max ();
        return *this;
      }

    while (_ptr->is_left_child ())
      {
        _ptr = _ptr->_parent;
      }
    _ptr = _ptr->_parent;
    return *this;
  }

private:
  node_pointer _ptr;
};

template <class T1, class T2>
bool
operator== (const tree_iterator<T1> &_ite1, const tree_iterator<T2> &_ite2)
{
  return (_ite1.base () == _ite2.base ());
}

template <class T1, class T2>
bool
operator!= (const tree_iterator<T1> &_ite1, const tree_iterator<T2> &_ite2)
{
  return (_ite1.base () != _ite2.base ());
}

template <class T>
class tree_const_iterator
    : public iterator<ft::bidirectional_iterator_tag, const T>
{
public:
  typedef tree_const_iterator<T> iterator_type;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, const T>::value_type
          value_type;
  typedef
      typename iterator<ft::bidirectional_iterator_tag, node<T> >::reference
          node_reference;
  typedef typename iterator<ft::bidirectional_iterator_tag, node<T> >::pointer
      node_pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag, const T>::reference
      reference;
  typedef typename iterator<ft::bidirectional_iterator_tag, const T>::pointer
      pointer;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T> >::difference_type difference_type;
  typedef typename iterator<ft::bidirectional_iterator_tag,
                            node<T> >::iterator_category iterator_category;

  tree_const_iterator () : _ptr (NULL) {}
  tree_const_iterator (const iterator_type &src) : _ptr (src.base ()) {}
  tree_const_iterator (const tree_iterator<T> &src) : _ptr (src.base ()) {}
  tree_const_iterator (const node_pointer ptr) : _ptr (ptr) {}
  ~tree_const_iterator () {}

  node_pointer
  base () const
  {
    return _ptr;
  }

  iterator_type &
  operator= (const iterator_type &src)
  {
    if (*this != src)
      {
        _ptr = src._ptr;
      }
    return (*this);
  }

  reference
  operator* () const
  {
    return _ptr->_value;
  }

  pointer
  operator-> () const
  {
    return &(operator* ());
  }

  iterator_type
  operator++ (int)
  {
    iterator_type _tmp = *this;
    operator++ ();
    return _tmp;
  }

  iterator_type &
  operator++ ()
  {
    if (!_ptr)
      return *this;

    if (_ptr->_right)
      {
        _ptr = _ptr->_right->min ();
        return *this;
      }

    while (_ptr->is_right_child ())
      {
        _ptr = _ptr->_parent;
      }
    _ptr = _ptr->_parent;
    return *this;
    return *this;
  }

  iterator_type
  operator-- (int)
  {
    iterator_type _tmp = *this;
    operator-- ();
    return _tmp;
  }

  iterator_type &
  operator-- ()
  {
    if (_ptr)
      {
        if (_ptr->is_left_leaf ())
          {
            while (_ptr->is_left_child ())
              {
                _ptr = _ptr->_parent;
              }
            _ptr = _ptr->_parent;
          }
        else if (_ptr->is_right_leaf () || !_ptr->_left)
          {
            _ptr = _ptr->_parent;
          }
        else if (_ptr->_left)
          {
            _ptr = _ptr->_left->max ();
          }
      }
    return *this;
  }

private:
  node_pointer _ptr;
};

template <class T1, class T2>
bool
operator== (const tree_const_iterator<T1> &_ite1,
            const tree_const_iterator<T2> &_ite2)
{
  return (_ite1.base () == _ite2.base ());
}

template <class T>
bool
operator== (const tree_iterator<T> &_ite1, const tree_const_iterator<T> &_ite2)
{
  return (_ite1.base () == _ite2.base ());
}

template <class T>
bool
operator== (const tree_const_iterator<T> &_ite1, const tree_iterator<T> &_ite2)
{
  return (_ite1.base () == _ite2.base ());
}

template <class T>
bool
operator!= (const tree_iterator<T> &_ite1, const tree_const_iterator<T> &_ite2)
{
  return (_ite1.base () != _ite2.base ());
}

template <class T>
bool
operator!= (const tree_const_iterator<T> &_ite1, const tree_iterator<T> &_ite2)
{
  return (_ite1.base () != _ite2.base ());
}

template <class T1, class T2>
bool
operator!= (const tree_const_iterator<T1> &_ite1,
            const tree_const_iterator<T2> &_ite2)
{
  return (_ite1.base () != _ite2.base ());
}

} // namespace ft
#endif