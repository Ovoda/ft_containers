#ifndef NODE_HPP
#define NODE_HPP

#include <utils.hpp>

namespace ft
{

template <class T> class node
{
public:
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  typedef node<T> node_type;
  typedef node_type &node_reference;
  typedef const node_type &node_const_reference;
  typedef node_type *node_pointer;
  typedef const node_type *node_const_pointer;

  typedef std::allocator<node_type> alloc_type;

  node (const value_type value, node_type *parent = NULL,
        node_type *right = NULL, node_type *left = NULL)
      : _value (value), _parent (parent), _right (right), _left (left)
  {
  }

  /* Helpers */
  bool
  is_mutual_parents ()
  {
    if (_parent != NULL && _parent->_parent != NULL)
      return ((_parent->_parent == this) ? true : false);
    return false;
  }

  bool
  is_left_child ()
  {
    if (is_mutual_parents ())
      return false;
    return ((_parent != NULL && _parent->_left == this) ? true : false);
  }

  bool
  is_right_child ()
  {
    if (is_mutual_parents ())
      return false;
    return ((_parent != NULL && _parent->_right == this) ? true : false);
  }

  bool
  is_left_leaf ()
  {
    return ((is_left_child () && !_right && !_left) ? true : false);
  }

  bool
  is_right_leaf ()
  {
    return ((is_right_child () && !_right && !_left) ? true : false);
  }

  node_pointer
  min ()
  {
    node_pointer tmp = this;
    while (tmp->_left)
      tmp = tmp->_left;
    return tmp;
  }

  node_pointer
  max ()
  {
    node_pointer tmp = this;
    while (tmp->_right)
      tmp = tmp->_right;
    return tmp;
  }

  value_type _value;
  node_pointer _parent;
  node_pointer _right;
  node_pointer _left;
  alloc_type _alloc;
};

/* ! this btree only works with ft::pair or std::pair so far */

template <class T, class Compare = ft::less<typename T::first_type>,
          class Alloc = std::allocator<ft::node<T> > >
class tree
{
public:
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  typedef Alloc alloc_type;
  typedef Compare key_comp;

  typedef typename node<T>::node_type node_type;
  typedef node_type &node_reference;
  typedef const node_type &node_const_reference;
  typedef node_type *node_pointer;
  typedef const node_type *node_const_pointer;

  tree () : _root (NULL), _size (0)
  {
    _end = _alloc.allocate(1);
    _alloc.construct(_end, value_type());
    _end->_parent = NULL;
    _end->_left = NULL;
    _end->_right = NULL;
  }

  ~tree ()
  {
    delete_tree (_root);
    _alloc.destroy(_end);
    _alloc.deallocate(_end, 1);
  }

  tree &
  operator= (const tree &_src)
  {
    if (this != &_src)
      {
        _root = _src._root;
        _alloc = _src._alloc;
        _key_comp = _src._key_comp;
        _size = _src._size;
        if (_root != NULL)
          _root->_parent = _end;
        reset_root (_root);
      }
    return *this;
  }

  void
  swap (tree &x)
  {
    size_t tmp_size = _size;
    _size = x._size;
    x._size = tmp_size;

    node_type *tmp = _root;
    _root = x._root;
    x._root = tmp;

    tmp = _end;
    _end = x._end;
    x._end = tmp;

    if (_root)
      _root->_parent = _end;
    if (x._root)
      x._root->_parent = x._end;
  }

  node_pointer
  begin () const
  {
    if (!_root || _size == 0)
      return end ();
    return _root->min ();
  }

  node_pointer
  end () const
  {
    return _end;
  }

  /* Insert - Search - Remove*/

  /* Insert */
  ft::pair<node_pointer, bool>
  insert (value_type value)
  {
    ft::pair<node_pointer, bool> _ret = insert (_root, value, NULL);
    if (_root)
      _root->_parent = _end;
    _end->_parent = _root;
    _end->_right = _root;
    _end->_left = _root;
    return (_ret);
  }

  ft::pair<node_pointer, bool>
  insert (node_pointer &_curr, value_type &value, node_pointer _parent)
  {
    if (!_curr)
      {
        _curr = _alloc.allocate (1);
        _alloc.construct (_curr, node_type (value, _parent));
        _size++;
        return (ft::make_pair (_curr, true));
      }
    if (_key_comp (value.first, _curr->_value.first))
      {
        return (insert (_curr->_left, value, _curr));
      }
    else if (_key_comp (_curr->_value.first, value.first))
      {
        return (insert (_curr->_right, value, _curr));
      }
    return ft::make_pair (_curr, false);
  }

  /* Search */
  node_pointer
  search (const typename value_type::first_type &value) const
  {
    return search (_root, value);
  }

  node_pointer
  search (node_pointer _curr,
          const typename value_type::first_type &value) const
  {
    if (!_curr)
      return NULL;

    if (_key_comp (value, _curr->_value.first))
      {
        return search (_curr->_left, value);
      }
    else if (_key_comp (_curr->_value.first, value))
      {
        return search (_curr->_right, value);
      }
    return (_curr);
  }

  /* Remove */
private:
  void
  replace_one_child (node_pointer _curr, node_pointer _new_curr)
  {
    if (_curr->is_left_child ())
      {
        _curr->_parent->_left = _new_curr;
      }
    else
      {
        _curr->_parent->_right = _new_curr;
      }
    _new_curr->_parent = _curr->_parent;
    _alloc.destroy (_curr);
    _alloc.deallocate (_curr, 1);
    _curr = NULL;
    reset_root (_new_curr);
  }

  void
  replace_two_child (node_pointer node_a, node_pointer node_b)
  {
    /* Giving child of the replacing node to its parent */
    if (node_b->_parent->_left == node_b)
      {
        node_b->_parent->_left = node_b->_right;
      }
    if (node_b->_parent->_right == node_b)
      {
        node_b->_parent->_right = node_b->_right;
      }

    /* Giving parents of the replaced node to the replacing node */
    if (node_a->_parent->_left == node_a)
      {
        node_a->_parent->_left = node_b;
      }
    if (node_a->_parent->_right == node_a)
      {
        node_a->_parent->_right = node_b;
      }
    node_b->_parent = node_a->_parent;

    /* Giving childs of the replaced node to the replacing node */
    node_b->_left = node_a->_left;
    if (node_b->_left)
      node_b->_left->_parent = node_b;

    node_b->_right = node_a->_right;
    if (node_b->_right)
      node_b->_right->_parent = node_b;

    /* Deleting replaced node */
    _alloc.destroy (node_a);
    _alloc.deallocate (node_a, 1);
    node_a = NULL;
    /* Getting the root ont the right node since it might have been changed */
    reset_root (node_b);
  }

public:
  size_t
  remove (node_pointer _curr)
  {
    if (!_curr)
      return (0);

    /* No childs : destroy node */
    if (!_curr->_right && !_curr->_left)
      {
        if (_curr->is_left_child ())
          {
            _curr->_parent->_left = NULL;
          }
        else
          {
            _curr->_parent->_right = NULL;
          }
        _alloc.destroy (_curr);
        _alloc.deallocate (_curr, 1);
        _curr = NULL;
        _size--;
        return (1);
      }

    /* 2 children : swap node with it's successor and destroy it */
    if (_curr->_right && _curr->_left)
      {
        replace_two_child (_curr, _curr->_right->min ());
        _size--;
        return (1);
      }

    /* 1 child : swap node with it's successor and destroy it */
    if (_curr->_right && !_curr->_left)
      {
        replace_one_child (_curr, _curr->_right);
      }
    else if (!_curr->_right && _curr->_left)
      {
        replace_one_child (_curr, _curr->_left);
      }
    _size--;
    return (1);
  }

  size_t
  remove (const typename value_type::first_type &value)
  {
    return (remove (search (value)));
  }

  /* Helper functions */

  void
  reset_root (node_pointer _curr)
  {
    if (!_curr || !_end)
      return;
    _root = _curr;
    while (_root && _root->_parent && _root->_parent != _end)
      {
        _root = _root->_parent;
      }
    _end->_parent = _root;
    _end->_right = _root;
    _end->_left = _root;
    if (_root)
      _root->_parent = _end;
  }

  /* Printing helper */
  void
  print_node (node_pointer _curr)
  {
    if (!_curr)
      return;
    std::cout << _curr->_value << ": ";
    if (_curr->_parent == NULL)
      std::cout << "NULL" << std::endl;
    else
      {
        std::cout << _curr->_parent->_value << std::endl;
      }
  }

  void
  print (node_pointer root, int space = 0)
  {
    if (root == NULL)
      return;
    space += 5;
    print (root->_right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++)
      std::cout << " ";
    std::cout << root->_value.first << "\n";
    print (root->_left, space);
  }

  void
  print ()
  {
    print (_root, 0);
  }

  bool
  is_end (node_pointer _curr)
  {
    node<T> *tmp = _curr;
    while (tmp->_parent)
      {
        tmp = tmp->_parent;
      }
    return tmp->max () == _curr;
  }

  bool
  is_begin (node_pointer _curr)
  {
    node<T> *tmp = _curr;
    while (tmp->_parent)
      {
        tmp = tmp->_parent;
      }
    return tmp->min () == _curr;
  }

  /* Destroying helpers */

  void
  clear ()
  {
    delete_tree (_root);
    _root = NULL;
    _size = 0;
  }

  void
  delete_tree (node_pointer _curr)
  {
    if (!_curr || _size <= 0)
      return;
    if (_curr->_right)
      {
        delete_tree (_curr->_right);
      }
    if (_curr->_left)
      {
        delete_tree (_curr->_left);
      }
    if (_curr->is_left_child ())
      {
        _curr->_parent->_left = NULL;
      }
    else
      {
        _curr->_parent->_right = NULL;
      }
    _alloc.destroy (_curr);
    _alloc.deallocate (_curr, 1);
    _curr = NULL;
    return;
  }

  bool
  is_empty () const
  {
    return (_size == 0);
  }

  size_t max_size() const {
    return _alloc.max_size();
  }

public:
  node_pointer _root;
  size_t _size;

private:
  alloc_type _alloc;
  node_pointer _end;
  key_comp _key_comp;
};

} // namespace ft

#endif