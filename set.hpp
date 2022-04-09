#ifndef SET_HPP
#define SET_HPP

#include <iterator.hpp>
#include <memory>
#include <tree.hpp>
#include <tree_iterator.hpp>
#include <utils.hpp>

namespace ft {

template <class T,                         // set::key_type/value_type
          class Compare = less<T>,         // set::key_compare/value_compare
          class Alloc = std::allocator<T>  // set::allocator_type
          >
class set {
 public:
  typedef T key_type;
  typedef T value_type;
  typedef red_black_tree<value_type, Compare> tree_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename tree_type::const_iterator iterator;
  typedef typename tree_type::const_iterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef size_t size_type;

  explicit set(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _tree(), _comp(comp), _alloc(alloc) {}

  template <class InputIterator>
  set(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _tree(), _comp(comp), _alloc(alloc) {
    for (; first != last; first++) {
      _tree.insert(*first);
    }
  }

  set(const set& x) { *this = x; }

  ~set() {}

  iterator begin() { return _tree.begin(); }
  const_iterator begin() const { return _tree.begin(); }

  iterator end() { return _tree.end(); }
  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return reverse_iterator(begin()); }

  set& operator=(const set& src) {
    if (this != &src) {
      _tree = src._tree;
      _comp = src._comp;
      _alloc = src._alloc;
    }
    return *this;
  }

  bool empty() const { return _tree.empty(); }
  size_type size() const { return _tree.size(); }
  size_type max_size() const { return _tree.max_size(); }

  pair<iterator, bool> insert(const value_type& val) {
    return (_tree.insert(val));
  }

  iterator insert(iterator position, const value_type& val) {
    (void)position;
    return (insert(val).first);
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  void erase(iterator position) { _tree.deleteNode(*position); }
  size_type erase(const value_type& val) {
    if (_tree.deleteNode(val)) return 1;
    return 0;
  }
  void erase(iterator first, iterator last) {
    iterator tmp;
    for (; first != last;) {
      tmp = first;
      first++;
      erase(tmp);
    }
  }

  void swap(set& x) {
    _tree.swap(x._tree);
    key_compare tmp = _comp;
    _comp = x._comp;
    x._comp = tmp;

    allocator_type tmp_alloc = _alloc;
    _alloc = x._alloc;
    x._alloc = tmp_alloc;
  }

  void clear() { _tree.clear(); }

  key_compare key_comp() const { return _comp; }
  value_compare value_comp() const { return key_comp(); }

  iterator find(const value_type& val) const {
    return iterator(_tree.searchTree(val));
  }

  size_type count(const value_type& val) const {
    if (_tree.count(val) != NULL) {
      return 1;
    }
    return 0;
  }

  iterator lower_bound(const value_type& val) const {
    iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (!_comp(*_ite, val)) {
        break;
      }
    }
    return _ite;
  }

  iterator upper_bound(const value_type& val) const {
    iterator _ite = begin();
    for (; _ite != end(); ++_ite) {
      if (_comp(val, *_ite)) {
        break;
      }
    }
    return _ite;
  }

  pair<iterator, iterator> equal_range(const value_type& val) const {
    return (pair<iterator, iterator>(lower_bound(val), upper_bound(val)));
  }

  allocator_type get_allocator() const { return _alloc; }

 private:
  red_black_tree<value_type, key_compare> _tree;
  key_compare _comp;
  allocator_type _alloc;
};

template <class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  if (lhs.size() == rhs.size()) {
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  return (false);
}
template <class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}

template <class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs) {
  return (rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs) {
  return !(rhs > lhs);
}

template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs,
          ft::set<Key, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft
#endif