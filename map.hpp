#ifndef MAP_HPP
#define MAP_HPP

#include <binary_tree.hpp>
#include <binary_tree_iterator.hpp>
#include <utils.hpp>

namespace ft {

template <class Key, class T, class Compare = ft::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  //   typedef value_comp;
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

 private:
  typedef tree<value_type> tree_type;

 public:
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _tree(tree_type()) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type()) {}

  map(const map& x) {}

  ~map() {}

 private:
  tree_type _tree;
};

}  // namespace ft

#endif