#ifndef MAP_HPP
#define MAP_HPP

#include <iterator.hpp>
#include <memory>
#include <tree.hpp>
#include <utils.hpp>

namespace ft {
template <class Key,                      // map::key_type
          class T,                        // map::mapped_type
          class Compare = ft::less<Key>,  // map::key_compare
          class Alloc =
              std::allocator<ft::pair<const Key, T> >  // map::allocator_type
          >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;

  class value_compare {
   protected:
    key_compare _key_comp;

   public:
    value_compare(key_compare c = key_compare()) : _key_comp(c) {}

   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return _key_comp(x.first, y.first);
    }
  };

 private:
  typedef red_black_tree<value_type, value_compare> tree_type;

 public:
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename tree_type::iterator iterator;
  typedef typename tree_type::const_iterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename iterator_traits<iterator>::difference_type difference_type;
  typedef size_t size_type;

 private:
  tree_type _tree;
  key_compare _key_comp;
  value_compare _value_comp;
  allocator_type _alloc;

 public:
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _tree(tree_type(value_compare())), _key_comp(comp), _alloc(alloc) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _tree(tree_type(value_compare())), _key_comp(comp), _alloc(alloc) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  map(const map& x) { *this = x; }

  ~map() {}

  map& operator=(const map& src) {
    if (this != &src) {
      clear();
      _key_comp = src._key_comp;
      _value_comp = src._value_comp;
      _alloc = src._alloc;
      for (const_iterator it = src.begin(); it != src.end(); it++) {
        insert(*it);
      }
    }
    return *this;
  }

  mapped_type& operator[](const key_type& k) {
    return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
  }

  iterator begin() { return _tree.begin(); }
  const_iterator begin() const { return _tree.begin(); }

  iterator end() { return _tree.end(); }
  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  bool empty() const { return (_tree.empty()); }
  size_type size() const { return (_tree.size()); }
  size_type max_size() const { return (_tree.max_size()); }

  pair<iterator, bool> insert(const value_type& val) {
    return (_tree.insert(val));
  }

  iterator insert(iterator position, const value_type& val) {
    (void)position;
    return (_tree.insert(val).first);
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  void erase(iterator position) { _tree.deleteNode(*position); }

  size_type erase(const key_type& k) {
    if (_tree.deleteNode(value_type(k, mapped_type()))) return 1;
    return 0;
  }

  void erase(iterator first, iterator last) {
    iterator tmp;
    for (; first != last;) {
      tmp = first;
      first++;
      _tree.deleteNode(*tmp);
    }
  }

  void swap(map& x) {
    _tree.swap(x._tree);

    key_compare tmp_key_comp = x._key_comp;
    value_compare tmp_value_comp = x._value_comp;
    allocator_type tmp_alloc = x._alloc;

    x._key_comp = _key_comp;
    x._value_comp = _value_comp;
    x._alloc = _alloc;

    _key_comp = tmp_key_comp;
    _value_comp = tmp_value_comp;
    _alloc = tmp_alloc;
  }

  void clear() { _tree.clear(); }

  key_compare key_comp() const { return _key_comp; }

  value_compare value_comp() const { return _value_comp; }

  iterator find(const key_type& k) {
    return iterator(_tree.searchTree(value_type(k, mapped_type())));
  }

  const_iterator find(const key_type& k) const {
    return const_iterator(_tree.searchTree(value_type(k, mapped_type())));
  }

  size_type count(const key_type& k) const {
    if (_tree.count(value_type(k, mapped_type()))) {
      return 1;
    }
    return 0;
  }

  iterator lower_bound(const key_type& k) {
    iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (!_key_comp(_ite->first, k)) {
        break;
      }
    }
    return _ite;
  }

  const_iterator lower_bound(const key_type& k) const {
    const_iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (!_key_comp(_ite->first, k)) {
        break;
      }
    }
    return _ite;
  }

  iterator upper_bound(const key_type& k) {
    iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (_key_comp(k, _ite->first)) {
        break;
      }
    }
    return _ite;
  }

  const_iterator upper_bound(const key_type& k) const {
    const_iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (_key_comp(k, _ite->first)) {
        break;
      }
    }
    return _ite;
  }

  pair<iterator, iterator> equal_range(const key_type& k) {
    return (ft::make_pair(lower_bound(k), upper_bound(k)));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
    return (ft::make_pair(lower_bound(k), upper_bound(k)));
  }

  allocator_type get_allocator() const { return _alloc; }
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  if (lhs.size() == rhs.size()) {
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  return (false);
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs > lhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs,
          ft::map<Key, T, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

#endif