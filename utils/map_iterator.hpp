#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP
#include <cstddef>
#include <node.hpp>

namespace ft {

/// Iterator
template <class T>
class map_iterator : public iterator<node<T> > {
 public:
  typedef node<T> base_type;
  typedef typename iterator<node<T> >::value_type value_type;
  typedef typename iterator<node<T> >::pointer pointer;
  typedef typename iterator<node<T> >::reference reference;
  typedef typename iterator<node<T> >::difference_type difference_type;
  typedef typename iterator<node<T> >::iterator_category iterator_category;

  map_iterator() : _is_past_last(false), _is_past_first(false) {}
  map_iterator(const map_iterator& src)
      : _ptr(src._ptr),
        _is_past_last(src._is_past_last),
        _is_past_first(src._is_past_first) {}

  map_iterator(pointer const ptr)
      : _ptr(ptr), _is_past_last(false), _is_past_first(false) {}

  ~map_iterator() {}

  pointer base() const { return _ptr; }

  map_iterator& operator++() {
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

  T& operator*() const { return _ptr->data(); }
  T* operator->() const { return &operator*(); }

  map_iterator operator++(int) {
    map_iterator tmp = *this;
    operator++();
    return tmp;
  }

  map_iterator& operator--() {
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
  friend bool operator!=(const map_iterator<Ite1>& rhs,
                         const map_iterator<Ite2>& lhs);

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
  pointer _ptr;
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
bool operator!=(const map_iterator<T>& rhs, const map_iterator<U>& lhs) {
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
  typedef typename iterator<node<const T> >::pointer pointer;
  typedef typename iterator<node<const T> >::reference reference;
  typedef typename iterator<node<const T> >::difference_type difference_type;
  typedef
      typename iterator<node<const T> >::iterator_category iterator_category;

  const_map_iterator() : _is_past_last(false), _is_past_first(false) {}
  const_map_iterator(const const_map_iterator& src)
      : _ptr(src._ptr),
        _is_past_last(src._is_past_last),
        _is_past_first(src._is_past_first) {}

  const_map_iterator(pointer const ptr)
      : _ptr(ptr), _is_past_last(false), _is_past_first(false) {}

  ~const_map_iterator() {}

  pointer base() { return _ptr; }

  const_map_iterator& operator++() {
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

  T& operator*() const { return _ptr->data(); }
  T* operator->() const { return &operator*(); }

  const_map_iterator operator++(int) {
    const_map_iterator tmp = *this;
    operator++();
    return tmp;
  }

  const_map_iterator& operator--() {
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
  pointer _ptr;
  bool _is_past_last;
  bool _is_past_first;
};

#ifndef FT_reverse_iterator_base_HPP
#define FT_reverse_iterator_base_HPP
#include <cstddef>

#include "iterator.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator_base {
 public:
  /// Typedefs
  typedef Iterator iterator_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::iterator_category iterator_category;

  /// Constructers and destructor
  reverse_iterator_base() {}
  explicit reverse_iterator_base(iterator_type it) : _base(it.base()) {}
  template <class Iter>
  reverse_iterator_base(const reverse_iterator_base<Iter>& rev_it)
      : _base(rev_it.base()) {}
  ~reverse_iterator_base() {}

  iterator_type base() const { return _base; }

  reverse_iterator_base& operator++() {
    --_base;
    return *this;
  }

  reverse_iterator_base operator++(int) {
    reverse_iterator_base tmp = *this;
    --_base;
    return tmp;
  }

  reverse_iterator_base& operator--() {
    ++_base;
    return *this;
  }

  reverse_iterator_base operator--(int) {
    reverse_iterator_base tmp = *this;
    ++_base;
    return tmp;
  }

  reference operator*() const {
    Iterator tmp = _base;
    tmp--;
    return *(tmp);
  }
  pointer operator->() const { return &(operator*()); }

  reverse_iterator_base& operator-=(
      typename reverse_iterator_base<Iterator>::difference_type amount) {
    this->_base += amount;
    return *this;
  }

  reverse_iterator_base& operator+=(
      typename reverse_iterator_base::difference_type amount) {
    this->_base -= amount;
    return *this;
  }

  typename reverse_iterator_base::reference operator[](
      typename reverse_iterator_base::difference_type index) const {
    return (base()[-index - 1]);
  }

  reverse_iterator_base operator-(difference_type n) const {
    reverse_iterator_base tmp = *this;
    tmp._base += n;
    return tmp;
  }

  template <class Ite>
  friend reverse_iterator_base<Ite> operator-(
      typename reverse_iterator_base<Ite>::difference_type n,
      const reverse_iterator_base<Ite>& rev_it);

  reverse_iterator_base operator+(difference_type n) const {
    reverse_iterator_base tmp = *this;
    tmp._base -= n;
    return tmp;
  }

  template <class Ite>
  friend reverse_iterator_base<Ite> operator+(
      typename reverse_iterator_base<Ite>::difference_type n,
      const reverse_iterator_base<Ite>& rev_it);

  template <class Ite1, class Ite2>
  friend bool operator!=(const reverse_iterator_base<Ite1>& rhs,
                         const reverse_iterator_base<Ite2>& lhs);

  template <class Ite1, class Ite2>
  friend bool operator==(const reverse_iterator_base<Ite1>& rhs,
                         const reverse_iterator_base<Ite2>& lhs);

  template <class Ite1, class Ite2>
  friend bool operator>(const reverse_iterator_base<Ite1>& rhs,
                        const reverse_iterator_base<Ite2>& lhs);

  template <class Ite1, class Ite2>
  friend bool operator<(const reverse_iterator_base<Ite1>& rhs,
                        const reverse_iterator_base<Ite2>& lhs);

  template <class Ite1, class Ite2>
  friend bool operator>=(const reverse_iterator_base<Ite1>& rhs,
                         const reverse_iterator_base<Ite2>& lhs);

  template <class Ite1, class Ite2>
  friend bool operator<=(const reverse_iterator_base<Ite1>& rhs,
                         const reverse_iterator_base<Ite2>& lhs);

 private:
  Iterator _base;
};

template <class Ite>
reverse_iterator_base<Ite> operator+(
    typename reverse_iterator_base<Ite>::difference_type n,
    const reverse_iterator_base<Ite>& rev_it) {
  return rev_it + n;
}

template <typename T, typename U>
typename reverse_iterator_base<T>::difference_type operator-(
    const reverse_iterator_base<T> lhs, const reverse_iterator_base<U> rhs) {
  return (rhs.base() - lhs.base());
}

template <class T, class U>
bool operator!=(const reverse_iterator_base<T>& rhs,
                const reverse_iterator_base<U>& lhs) {
  return (rhs.base() != lhs.base());
}

template <class T, class U>
bool operator==(const reverse_iterator_base<T>& rhs,
                const reverse_iterator_base<U>& lhs) {
  return (rhs.base() == lhs.base());
}

template <class T, class U>
bool operator>(const reverse_iterator_base<T>& rhs,
               const reverse_iterator_base<U>& lhs) {
  return (rhs.base() < lhs.base());
}

template <class T, class U>
bool operator<(const reverse_iterator_base<T>& rhs,
               const reverse_iterator_base<U>& lhs) {
  return (rhs.base() > lhs.base());
}

template <class T, class U>
bool operator>=(const reverse_iterator_base<T>& rhs,
                const reverse_iterator_base<U>& lhs) {
  return (rhs.base() <= lhs.base());
}

template <class T, class U>
bool operator<=(const reverse_iterator_base<T>& rhs,
                const reverse_iterator_base<U>& lhs) {
  return (rhs.base() >= lhs.base());
}

};  // namespace ft
#endif

}  // namespace ft
#endif
