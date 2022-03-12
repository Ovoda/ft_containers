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

  map& operator=(const map& x) {
    if (*this != x) {
    }
    return *this;
  }

  iterator begin() { return iterator(_tree.begin()); }
  const_iterator begin() const { return const_iterator(_tree.begin()); }

  iterator end() { return iterator(_tree.end()); }
  const_iterator end() const { return const_iterator(_tree.end()); }

  bool empty() const { return _tree.is_empty(); }

  size_type size() const {}

  size_type max_size() const { return (_alloc.max_size()); }

  mapped_type& operator[](const key_type& k) {
    return (*((insert(make_pair(k, mapped_type()))).first)).second;
  }

  pair<iterator, bool> insert(const value_type& val) {
    ft::pair<typename tree_type::node_pointer, bool> _ret = _tree.insert(val);
    return (ft::make_pair(iterator(_ret.first), _ret.second));
  }

  //   iterator insert(iterator position, const value_type& val) {}

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {}

  void erase(iterator position) {}

  size_type erase(const key_type& k) {
    _tree.remove(k);
    return 0;
  }

  void erase(iterator first, iterator last) {}

  iterator find(const key_type& k) { return (iterator(_tree.search(k))); }
  const_iterator find(const key_type& k) const {}

 private:
  tree_type _tree;
  allocator_type _alloc;
};

}  // namespace ft

#endif