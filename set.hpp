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
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef tree_iterator<key_type> iterator;
  typedef tree_iterator<const key_type> const_iterator;
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

  set& operator=(const set& src) {
    if (this != &src) {
      _tree = src._tree;
      _comp = src._comp;
      _alloc = src._alloc;
    }
  }

  bool empty() const { return _tree.empty(); }
  size_type size() const { return _tree.size(); }
  size_type max_size() const { return _tree.max_size(); }

 private:
  red_black_tree<value_type> _tree;
  key_compare _comp;
  allocator_type _alloc;
};

}  // namespace ft
#endif