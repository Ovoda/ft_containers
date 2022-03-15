#ifndef MAP_HPP
#define MAP_HPP

#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <utils.hpp>

namespace ft
{

template <class Key, class T, class Compare = ft::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::tree_iterator<value_type> iterator;
  typedef ft::tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

  class value_compare
  {
    friend class map;

  protected:
    key_compare _key_comp;
    value_compare (Compare c)
        : _key_comp (c) {}
  
  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool
    operator() (const value_type &x, const value_type &y) const
    {
      return _key_comp (x.first, y.first);
    }
  };

private:
  typedef tree<value_type, key_compare> tree_type;

public:
  explicit map (const key_compare &comp = key_compare (),
                const allocator_type &alloc = allocator_type ())
      : _tree (tree_type ()), _alloc (alloc), _key_comp (comp)
  {
  }

  template <class InputIterator>
  map (InputIterator first, InputIterator last,
       const key_compare &comp = key_compare (),
       const allocator_type &alloc = allocator_type ())
      : _tree (tree_type ()), _key_comp (comp)
  {
    _alloc = alloc;
    for (; first != last; first++)
      {
        insert (*first);
      }
  }

  map (const map &x) { *this = x; }

  ~map () {}

  map &
  operator= (const map &x)
  {
    if (this != &x)
      {
        clear ();
        for (const_iterator _ite = x.begin (); _ite != x.end (); _ite++)
          {
            insert (*_ite);
          }
      }
    return *this;
  }

  value_compare
  value_comp () const
  {
    return value_compare (_key_comp);
  }

  iterator
  begin ()
  {
    return iterator (_tree.begin ());
  }
  const_iterator
  begin () const
  {
    return const_iterator (_tree.begin ());
  }

  iterator
  end ()
  {
    return iterator (_tree.end ());
  }
  const_iterator
  end () const
  {
    return const_iterator (_tree.end ());
  }

  reverse_iterator
  rbegin ()
  {
    return reverse_iterator (end ());
  }
  reverse_iterator
  rend ()
  {
    return reverse_iterator (begin ());
  }

  bool
  empty () const
  {
    return _tree.is_empty ();
  }

  size_type
  size () const
  {
    return _tree._size;
  }

  size_type
  max_size () const
  {
    return (_tree.max_size ());
  }

  mapped_type &
  operator[] (const key_type &k)
  {
    return (*((insert (ft::make_pair (k, mapped_type ()))).first)).second;
  }

  pair<iterator, bool>
  insert (const value_type &val)
  {
    ft::pair<typename tree_type::node_pointer, bool> _ret = _tree.insert (val);
    return (ft::make_pair (iterator (_ret.first), _ret.second));
  }

  iterator
  insert (iterator position, const value_type &val)
  {
    (void)position;
    return (insert (val).first);
  }

  template <class InputIterator>
  void
  insert (InputIterator first, InputIterator last)
  {
    for (; first != last; ++first)
      {
        insert (*first);
      }
  }

  void
  erase (iterator position)
  {
    _tree.remove (position->first);
  }

  size_type
  erase (const key_type &k)
  {
    return (_tree.remove (k));
  }

  void
  erase (iterator first, iterator last)
  {

    for (; first != last;)
      {
        key_type _v = first->first;
        first++;
        _tree.remove (_v);
      }
  }

  void
  swap (map &x)
  {
    _tree.swap (x._tree);
  }

  iterator
  find (const key_type &k)
  {
    typename tree_type::node_pointer ret = _tree.search (k);
    if (ret == NULL)
      return end ();
    return (iterator (ret));
  }

  const_iterator
  find (const key_type &k) const
  {
    typename tree_type::node_pointer ret = _tree.search (k);
    if (ret == NULL)
      return end ();
    return (const_iterator (ret));
  }

  size_type
  count (const key_type &k) const
  {
    return (_tree.search (k)) ? 1 : 0;
  }

  void
  clear ()
  {
    _tree.clear ();
  }

  key_compare
  key_comp () const
  {
    return _key_comp;
  }

  iterator
  lower_bound (const key_type &k)
  {
    iterator _ite = begin ();
    for (; _ite != end (); ++_ite)
      {
        if (!_key_comp (_ite->first, k))
          {
            break;
          }
      }
    return _ite;
  }

  const_iterator
  lower_bound (const key_type &k) const
  {
    const_iterator _ite = begin ();
    for (; _ite != end (); ++_ite)
      {
        if (!_key_comp (_ite->first, k))
          {
            break;
          }
      }
    return _ite;
  }

  iterator
  upper_bound (const key_type &k)
  {
    iterator _ite = begin ();
    for (; _ite != end (); ++_ite)
      {
        if (_key_comp (k, _ite->first))
          {
            break;
          }
      }
    return _ite;
  }

  const_iterator
  upper_bound (const key_type &k) const
  {
    const_iterator _ite = begin ();
    for (; _ite != end (); ++_ite)
      {
        if (_key_comp (k, _ite->first))
          {
            break;
          }
      }
    return _ite;
  }

  pair<iterator, iterator>
  equal_range (const key_type &k)
  {
    return (ft::make_pair (lower_bound (k), upper_bound (k)));
  }

  pair<const_iterator, const_iterator>
  equal_range (const key_type &k) const
  {
    return (ft::make_pair (lower_bound (k), upper_bound (k)));
  }

  allocator_type
  get_allocator () const
  {
    return _alloc;
  }

private:
  tree_type _tree;
  allocator_type _alloc;
  key_compare _key_comp;
};

template <class Key, class T, class Compare, class Alloc>
bool
operator== (const map<Key, T, Compare, Alloc> &lhs,
            const map<Key, T, Compare, Alloc> &rhs)
{
  if (lhs.size () == rhs.size ())
    return (ft::equal (lhs.begin (), lhs.end (), rhs.begin ()));
  return false;
}

template <class Key, class T, class Compare, class Alloc>
bool
operator!= (const map<Key, T, Compare, Alloc> &lhs,
            const map<Key, T, Compare, Alloc> &rhs)
{
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool
operator< (const map<Key, T, Compare, Alloc> &lhs,
           const map<Key, T, Compare, Alloc> &rhs)
{
  return (ft::lexicographical_compare (lhs.begin (), lhs.end (), rhs.begin (),
                                       rhs.end ()));
}

template <class Key, class T, class Compare, class Alloc>
bool
operator<= (const map<Key, T, Compare, Alloc> &lhs,
            const map<Key, T, Compare, Alloc> &rhs)
{
  return !(lhs > rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool
operator> (const map<Key, T, Compare, Alloc> &lhs,
           const map<Key, T, Compare, Alloc> &rhs)
{
  return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool
operator>= (const map<Key, T, Compare, Alloc> &lhs,
            const map<Key, T, Compare, Alloc> &rhs)
{
  return !(lhs < rhs);
}

template <class key, class mapped, class Compare, class Alloc>
void
swap (ft::map<key, mapped, Compare, Alloc> &map_a,
      ft::map<key, mapped, Compare, Alloc> &map_b)
{
  map_a.swap (map_b);
}
} // namespace ft

#endif