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
  typedef allocator_type::reference reference;
  typedef allocator_type::pointer pointer;
  typedef allocator_type::const_reference const_reference;
  typedef allocator_type::const_pointer const_pointer;
  typedef ft::tree_iterator<value_type> iterator;
  typedef ft::tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  tree _tree;
};

}  // namespace ft

#endif