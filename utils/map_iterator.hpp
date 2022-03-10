#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP
#include <cstddef>

namespace ft {

template <class T>
class node {
 public:
  node() : _right(nullptr), _left(nullptr), _parent(nullptr) {}
  node(T src)
      : _right(nullptr), _left(nullptr), _parent(nullptr), _pair(T(src)) {}
  ~node() {}

  node<T> &operator=(node<T> rhs) {
    if (this != &rhs) {
      _right = rhs._right;
      _left = rhs._left;
      _pair = rhs._pair;
      _parent = rhs._parent;
    }
    return *this;
  }

  // getters
  T &data() { return (_pair); }
  node *parent() const { return (_parent); }
  node *left() const { return (_left); }
  node *right() const { return (_right); }

  node<T> *min() {
    node<T> *tmp = this;
    while (tmp->_left) {
      tmp = tmp->_left;
    }
    return tmp;
  }

  node<T> *max() {
    node<T> *tmp = this;
    while (tmp->_right) {
      tmp = tmp->_right;
    }
    return tmp;
  }

  bool is_end() {
    node<T> *tmp = this;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->max() == this;
  }

  bool is_begin() {
    node<T> *tmp = this;
    while (tmp->_parent) {
      tmp = tmp->_parent;
    }
    return tmp->min() == this;
  }

  bool is_left_child() {
    if (_parent != nullptr && _parent->left() == this) {
      return true;
    }
    return false;
  }

  bool is_right_child() {
    if (_parent != nullptr && _parent->right() == this) {
      return true;
    }
    return false;
  }

  bool is_left_leaf() {
    if (is_left_child() && !_right && !_left) {
      return true;
    }
    return false;
  }

  bool is_right_leaf() {
    if (is_right_child() && !_right && !_left) {
      return true;
    }
    return false;
  }

  // setters
  void set_left(node *src) { _left = src; }
  void set_right(node *src) { _right = src; }
  void set_pair(T src) { _pair = src; }

  pair<node *, bool> insert(T src) {
    if (src.first > _pair.first) {
      if (_right == nullptr) {
        _right = _alloc.allocate(sizeof(src));
        _alloc.construct(_right, src);
        _right->_parent = this;
      } else {
        return (_right->insert(src));
      }
      return make_pair(_right, true);
    } else if (src.first < _pair.first) {
      if (_left == nullptr) {
        _left = _alloc.allocate(sizeof(src));
        _alloc.construct(_left, src);
        _left->_parent = this;
      } else {
        return (_left->insert(src));
      }
      return make_pair(_left, true);
    }
    return make_pair(this, false);
  }

  // TODO : change return function
  node *search(typename T::first_type const &key) {
    if (key == _pair.first) {
      return this;
    } else if (_right && key > _pair.first) {
      return _right->search(key);
    } else if (_left && key < _pair.first) {
      return _left->search(key);
    }
    return nullptr;
  }

  node *_right;
  node *_left;
  node *_parent;
  T _pair;

 private:
  std::allocator<ft::node<T> > _alloc;
};

/// Iterator
template <class T>
class map_iterator : public iterator<node<T> > {
 public:
  typedef node<T> base_type;
  typedef typename iterator<node<T> >::value_type value_type;
  typedef typename iterator<node<T> >::reference node_reference;
  typedef typename iterator<node<T> >::pointer node_pointer;
  typedef T *pointer;
  typedef T &reference;
  typedef typename iterator<node<T> >::difference_type difference_type;
  typedef typename iterator<node<T> >::iterator_category iterator_category;

  map_iterator() : _is_past_last(false), _is_past_first(false) {}
  map_iterator(const map_iterator &src)
      : _ptr(src._ptr),
        _is_past_last(src._is_past_last),
        _is_past_first(src._is_past_first) {}

  map_iterator(node_pointer const ptr)
      : _ptr(ptr), _is_past_last(false), _is_past_first(false) {}

  ~map_iterator() {}

  node_pointer base() const { return _ptr; }

  map_iterator &operator++() {
    if (_ptr) {
      if (_is_past_first) {
        _ptr += 1;
        _is_past_first = false;
        return *this;
      }
      if (_ptr->is_end()) {
        _ptr += 1;
        _is_past_last = true;
        return *this;
      }

      if (_ptr->is_right_leaf()) {
        while (_ptr->is_right_child()) {
          _ptr = _ptr->parent();
        }
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->is_left_leaf() || !_ptr->right()) {
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->right()) {
        _ptr = _ptr->right();
        _ptr = _ptr->min();
        return *this;
      }
    }
    return *this;
  }

  T &operator*() const { return _ptr->data(); }
  T *operator->() const { return &operator*(); }

  map_iterator operator++(int) {
    map_iterator tmp = *this;
    operator++();
    return tmp;
  }

  map_iterator &operator--() {
    if (_ptr) {
      // coming back from past-the-end pointer
      if (_is_past_last) {
        _ptr -= 1;
        _is_past_last = false;
        return *this;
      }
      if (_ptr->is_begin()) {
        _ptr -= 1;
        _is_past_first = true;
        return *this;
      }
      // regular decrementation
      if (_ptr->is_left_leaf()) {
        while (_ptr->is_left_child()) {
          _ptr = _ptr->parent();
        }
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->is_right_leaf() || !_ptr->left()) {
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->left()) {
        _ptr = _ptr->left();
        _ptr = _ptr->max();
        return *this;
      }
    }
    return *this;
  }

  map_iterator operator--(int) {
    map_iterator tmp = *this;
    operator--();
    return tmp;
  }

  //   reference operator[](difference_type index) const { return (_ptr[index]);
  //   }

  //   bool operator>(map_iterator const& rhs) const {
  //     return (this->_ptr > rhs._ptr);
  //   }

  //   bool operator>=(map_iterator const& rhs) const {
  //     return (this->_ptr >= rhs._ptr);
  //   }

  //   bool operator<(map_iterator const& rhs) const {
  //     return (this->_ptr < rhs._ptr);
  //   }

  //   bool operator<=(map_iterator const& rhs) const {
  //     return (this->_ptr <= rhs._ptr);
  //   }

  //   map_iterator& operator-=(const difference_type n) {
  //     _ptr -= n;
  //     return (*this);
  //   }

  //   map_iterator& operator+=(const difference_type n) {
  //     _ptr += n;
  //     return (*this);
  //   }

  //   map_iterator operator-(const difference_type n) {
  //     return (map_iterator(_ptr - n));
  //   }

  //   map_iterator operator+(const difference_type n) {
  //     return (map_iterator(_ptr + n));
  //   }

  //   difference_type operator-(const map_iterator& rhs) {
  //     return (_ptr - rhs._ptr);
  //   }

  //   difference_type operator+(const map_iterator& rhs) {
  //     return (_ptr + rhs._ptr);
  //   }

  /// Overloads
  template <class Ite1, class Ite2>
  friend bool operator!=(const map_iterator<Ite1> &rhs,
                         const map_iterator<Ite2> &lhs);

  //   template <class Ite1, class Ite2>
  //   friend bool operator==(const map_iterator<Ite1>& rhs,
  //                          const map_iterator<Ite2>& lhs);

  //   template <class Ite1, class Ite2>
  //   friend bool operator>(const map_iterator<Ite1>& rhs,
  //                         const map_iterator<Ite2>& lhs);

  //   template <class Ite1, class Ite2>
  //   friend bool operator<(const map_iterator<Ite1>& rhs,
  //                         const map_iterator<Ite2>& lhs);

  //   template <class Ite1, class Ite2>
  //   friend bool operator>=(const map_iterator<Ite1>& rhs,
  //                          const map_iterator<Ite2>& lhs);

  //   template <class Ite1, class Ite2>
  //   friend bool operator<=(const map_iterator<Ite1>& rhs,
  //                          const map_iterator<Ite2>& lhs);

 protected:
  node_pointer _ptr;
  bool _is_past_last;
  bool _is_past_first;
};

// template <class T>
// map_iterator<T> operator+(
//     typename map_iterator<T>::difference_type n,
//     map_iterator<T>& it) {
//   return (it + n);
// }

// template <class Ite1, class Ite2>
// typename map_iterator<Ite1>::difference_type operator-(
//     map_iterator<Ite1> ite1, map_iterator<Ite2> ite2) {
//   return (ite1.base() - ite2.base());
// }

template <class T, class U>
bool operator!=(const map_iterator<T> &rhs, const map_iterator<U> &lhs) {
  return (rhs._ptr != lhs._ptr);
}

// template <class T, class U>
// bool operator==(const map_iterator<T>& rhs,
//                 const map_iterator<U>& lhs) {
//   return (rhs._ptr == lhs._ptr);
// }

// template <class T, class U>
// bool operator>(const map_iterator<T>& rhs,
//                const map_iterator<U>& lhs) {
//   return (rhs._ptr > lhs._ptr);
// }

// template <class T, class U>
// bool operator<(const map_iterator<T>& rhs,
//                const map_iterator<U>& lhs) {
//   return (rhs._ptr < lhs._ptr);
// }

// template <class T, class U>
// bool operator>=(const map_iterator<T>& rhs,
//                 const map_iterator<U>& lhs) {
//   return (rhs._ptr >= lhs._ptr);
// }

// template <class T, class U>
// bool operator<=(const map_iterator<T>& rhs,
//                 const map_iterator<U>& lhs) {
//   return (rhs._ptr <= lhs._ptr);
// }

/// Iterator
template <class T>
class const_map_iterator : public iterator<node<const T> > {
 public:
  typedef typename iterator<node<const T> >::value_type value_type;
  typedef typename iterator<node<const T> >::pointer node_pointer;
  typedef typename iterator<node<const T> >::reference node_reference;
  typedef T *pointer;
  typedef T &reference;
  typedef typename iterator<node<const T> >::difference_type difference_type;
  typedef
      typename iterator<node<const T> >::iterator_category iterator_category;

  const_map_iterator() : _is_past_last(false), _is_past_first(false) {}
  const_map_iterator(const const_map_iterator &src)
      : _ptr(src._ptr),
        _is_past_last(src._is_past_last),
        _is_past_first(src._is_past_first) {}

  const_map_iterator(node_pointer const ptr)
      : _ptr(ptr), _is_past_last(false), _is_past_first(false) {}

  ~const_map_iterator() {}

  node_pointer base() { return _ptr; }

  const_map_iterator &operator++() {
    if (_ptr) {
      if (_is_past_first) {
        _ptr += 1;
        _is_past_first = false;
        return *this;
      }
      if (_ptr->is_end()) {
        _ptr += 1;
        _is_past_last = true;
        return *this;
      }

      if (_ptr->is_right_leaf()) {
        while (_ptr->is_right_child()) {
          _ptr = _ptr->parent();
        }
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->is_left_leaf() || !_ptr->right()) {
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->right()) {
        _ptr = _ptr->right();
        _ptr = _ptr->min();
        return *this;
      }
    }
    return *this;
  }

  T &operator*() const { return _ptr->data(); }
  T *operator->() const { return &operator*(); }

  const_map_iterator operator++(int) {
    const_map_iterator tmp = *this;
    operator++();
    return tmp;
  }

  const_map_iterator &operator--() {
    if (_ptr) {
      // coming back from past-the-end pointer
      if (_is_past_last) {
        _ptr -= 1;
        _is_past_last = false;
        return *this;
      }
      if (_ptr->is_begin()) {
        _ptr -= 1;
        _is_past_first = true;
        return *this;
      }
      // regular decrementation
      if (_ptr->is_left_leaf()) {
        while (_ptr->is_left_child()) {
          _ptr = _ptr->parent();
        }
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->is_right_leaf() || !_ptr->left()) {
        _ptr = _ptr->parent();
        return *this;
      }

      if (_ptr->left()) {
        _ptr = _ptr->left();
        _ptr = _ptr->max();
        return *this;
      }
    }
    return *this;
  }

  const_map_iterator operator--(int) {
    const_map_iterator tmp = *this;
    operator--();
    return tmp;
  }

 protected:
  node_pointer _ptr;
  bool _is_past_last;
  bool _is_past_first;
};
}  // namespace ft

#endif