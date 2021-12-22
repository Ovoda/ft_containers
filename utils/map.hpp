#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <cstddef>  // ptrdiff_t, size_t
#include <functional>
#include <iterator.hpp>
#include <pair_node.hpp>
#include <reverse_iterator.hpp>
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
  typedef reverse_iterator_base<iterator> reverse_iterator;
  typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _size(0), _base(nullptr) {}

  // template <class InputIterator>
  // map(InputIterator first, InputIterator last,
  //     const key_compare& comp = key_compare(),
  //     const allocator_type& alloc = allocator_type());

  // map(const map& x);

  ~map() {}

  pair<bool, bool> insert(ft::pair<key_type, mapped_type>& _pair) {
    _base->insert(_pair, _base);
    return pair<bool, bool>(true, true);
  }

 private:
  node<key_type, mapped_type>* _base;
  int _size;
};

}  // namespace ft
#endif