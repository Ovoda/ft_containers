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
      : _tree(tree_type()), _key_comp(comp) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _tree(tree_type()), _key_comp(comp) {
    _alloc = alloc;
    for (; first != last; first++) {
      insert(*first);
    }
  }

  map(const map& x) { *this = x; }

  ~map() {}

  map& operator=(const map& x) {
    if (this != &x) {
      clear();
      for (const_iterator _ite = x.begin(); _ite != x.end(); _ite++) {
        insert(*_ite);
      }
    }
    return *this;
  }

  iterator begin() { return iterator(_tree.begin()); }
  const_iterator begin() const { return const_iterator(_tree.begin()); }

  iterator end() { return iterator(_tree.end()); }
  const_iterator end() const { return const_iterator(_tree.end()); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }

  bool empty() const { return _tree.is_empty(); }

  size_type size() const { return _tree._size; }

  size_type max_size() const { return (_alloc.max_size()); }

  mapped_type& operator[](const key_type& k) {
    return (*((insert(make_pair(k, mapped_type()))).first)).second;
  }

  pair<iterator, bool> insert(const value_type& val) {
    ft::pair<typename tree_type::node_pointer, bool> _ret = _tree.insert(val);
    return (ft::make_pair(iterator(_ret.first), _ret.second));
  }

  // iterator insert(iterator position, const value_type& val) {
  // 	for ()
  // }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  void erase(iterator position) {
    _tree.print();
    std::cout << "__________________" << std::endl;
    _tree.remove(position->first);
    _tree.print();
  }

  size_type erase(const key_type& k) {
    _tree.print();
    std::cout << "__________________" << std::endl;
    _tree.remove(k);
    _tree.print();
    return 1;
  }

  void erase(iterator first, iterator last) {}

  iterator find(const key_type& k) { return (iterator(_tree.search(k))); }

  const_iterator find(const key_type& k) const {
    return (const_iterator(_tree.search(k)));
  }

  size_type count(const key_type& k) const { return (_tree.search(k)) ? 1 : 0; }

  void clear() { _tree.delete_tree(_tree._root); }

  key_compare key_comp() const { return _key_comp; }

 private:
  tree_type _tree;
  allocator_type _alloc;
  key_compare _key_comp;
};

}  // namespace ft

#endif