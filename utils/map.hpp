#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <cstddef>  // ptrdiff_t, size_t
#include <functional>
#include <iterator.hpp>
#include <std_lib.hpp>

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  //   typedef value_compare;
  typedef Alloc allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef random_access_iterator<value_type> iterator;
  typedef random_access_iterator<const value_type> const_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
};

}  // namespace ft
#endif