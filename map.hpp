#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <cstddef>  // ptrdiff_t, size_t
#include <functional>
#include <iterator.hpp>
#include <map_iterator.hpp>
#include <reverse_iterator.hpp>
#include <utils.hpp>

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;

 private:
  typedef node<value_type> _base;

  node<value_type>* _tree;

 public:
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef map_iterator<value_type> iterator;
  typedef const_map_iterator<value_type> const_iterator;
  typedef reverse_iterator_base<iterator> reverse_iterator;
  typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

  explicit map() : _size(0) {}
  // const key_compare& comp = key_compare(),
  // const allocator_type& alloc = allocator_type())

  pair<iterator, bool> insert(const value_type& value) {
    if (_size == 0) {
      _tree = _node_alloc.allocate(sizeof(node<value_type>));
      _node_alloc.construct(_tree, node<value_type>(value));
      _size++;
      return (make_pair(iterator(_tree), true));
    }
    pair<node<value_type>*, bool> _first_ret(_tree->insert(value));
    _first_ret.second == true ? _size++ : _size;
    return (make_pair(iterator(_first_ret.first), _first_ret.second));
  }

  T search(Key key) { return _tree->search(key); }

  iterator begin() { return iterator(_tree->min()); }
  const_iterator begin() const { return const_iterator(_tree->min()); }
  iterator end() { return ++iterator(_tree->max()); }
  const_iterator end() const { return ++const_iterator(_tree->max()); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }

  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }
  size_type max_size() const { return _node_alloc.max_size(); }

  mapped_type& operator[](const key_type& k) {
    return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
  }

  const_iterator find(const key_type& k) const {
    node<const value_type>* tmp_node;
    tmp_node = _tree->search(k);

    if (tmp_node == nullptr) {
      return end();
    }
    return const_iterator(tmp_node);
  }

  iterator find(const key_type& k) {
    node<value_type>* tmp_node;
    tmp_node = _tree->search(k);

    if (tmp_node == nullptr) {
      return end();
    }
    return iterator(tmp_node);
  }

  ~map() {}
  // TODO private

 private:
  int _size;
  std::allocator<node<pair<const Key, T> > > _node_alloc;
  Alloc _alloc;
};

}  // namespace ft
#endif