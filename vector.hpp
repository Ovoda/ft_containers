#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <cstddef>
#include <iostream>
// #include <xiterator.hpp>
#include <memory>

#include "utils/comparaison_tools.hpp"
#include "utils/iterator.hpp"
#include "utils/reverse_iterator.hpp"
#include "utils/std_lib.hpp"
#include "utils/type_traits.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef ft::random_access_iterator<T> iterator;
  typedef ft::random_access_iterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

  vector() : _array(nullptr), _size(0), _capacity(0) {}

  explicit vector(size_type n, const value_type& val = value_type())
      : _array(nullptr), _size(0), _capacity(0) {
    for (size_type i = 0; i < n; i++) push_back(val);
  }

  template <class InputIterator>
  vector(InputIterator first,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type last)
      : _array(nullptr), _size(0), _capacity(0) {
    for (iterator i = first; i != last; i++) push_back(*i);
  }

  vector(const vector& src) : _array(nullptr), _size(0), _capacity(0) {
    *this = src;
  }

  ~vector() {
    if (_capacity > 0) {
      clear();
      // _alloc.deallocate(_array, _capacity);
    }
  }

  iterator begin() { return iterator(&_array[0]); }
  const_iterator begin() const { return const_iterator(&_array[0]); }

  iterator end() { return iterator(_array + size()); }
  const_iterator end() const { return const_iterator(_array + size()); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  size_type size() const { return _size; }

  size_type max_size() const { return (_alloc.max_size()); }

  void resize(size_type n, value_type val = value_type()) {
    if (n < _size) {
      for (iterator it = iterator(_array + _size); it != iterator(_array + n);
           it--) {
        _alloc.destroy(&(*it));
      }
      _size = n;
    } else if (n > _size) {
      for (size_type i = _size; i < n; i++) {
        push_back(val);
      }
    }
  }

  size_type capacity() const { return (_capacity); }

  bool empty() const { return (_size == 0); }

  void reserve(size_type n) {
    if (n >= _capacity) {
      vector<value_type> tmp(*this);

      if (_capacity > 0) {
        clear();
        _alloc.deallocate(_array, _capacity);
      }
      _array = _alloc.allocate(n);
      _capacity = n;
      for (iterator it = tmp.begin(); it != tmp.end(); ++it) {
        _alloc.construct(&_array[_size++], *it);
      }
    }
  }

  vector& operator=(const vector& x) {
    if (this != &x) {
      if (_capacity > 0) {
        clear();
        _alloc.deallocate(_array, _capacity);
      }
      _size = 0;
      _capacity = x.capacity();
      if (_capacity > 0) {
        _array = _alloc.allocate(_capacity);
      }
      for (const_iterator it = x.begin(); it != x.end(); ++it) {
        _alloc.construct(&_array[_size++], *it);
      }
    }
    return *this;
  }

  reference operator[](size_type index) { return (_array[index]); }
  const_reference operator[](size_type index) const { return (_array[index]); }

  reference at(size_type n) {
    if (n >= _size) {
      throw std::out_of_range("vector");
    }
    return _array[n];
  }
  const_reference at(size_type n) const {
    if (n >= _size) {
      throw std::out_of_range("vector");
    }
    return _array[n];
  }

  reference front() { return _array[0]; }
  const_reference front() const { return _array[0]; }

  reference back() { return _array[_size - 1]; }
  const_reference back() const { return _array[_size - 1]; }

  /// Vector Modifiers

  void assign(size_type n, value_type const val) {
    vector<value_type> x(n, val);
    swap(x);
  }

  void push_back(value_type const& val) {
    static int i = 0;
    if (_size >= _capacity) {
      _capacity <= 0 ? reserve(1) : reserve(_capacity *= 2);
    }
    _alloc.construct(&_array[_size++], val);
    i++;
  }

  void pop_back() { _alloc.destroy(&_array[_size-- - 1]); }

  iterator insert(iterator position, const value_type& val) {
    vector<T> tmp;
    for (iterator tmp_it = position + 1; tmp_it != end(); tmp_it++) {
      tmp.push_back(*tmp_it);
    }
    resize(position - begin());
    push_back(val);
    for (; position != end(); position++) {
      tmp.push_back(*position);
    }
  }

  // void insert(iterator position, size_type n, const value_type& val) {
  //   reserve(_size + n);
  //   iterator end = end();
  //   for (iterator it = begin() + n; it != position + n; it++) {
  //   }
  // }

  // template <class InputIterator>
  // void insert(iterator position, InputIterator first, InputIterator last);

  void swap(vector& x) {
    pointer tmp_array = _array;
    size_type tmp_size = _size;
    size_type tmp_capacity = _capacity;

    _array = x._array;
    _size = x._size;
    _capacity = x._capacity;

    x._array = tmp_array;
    x._size = tmp_size;
    x._capacity = tmp_capacity;
  }

  void clear() {
    for (iterator it = begin(); it != end(); ++it) {
      _alloc.destroy(&(*it));
    }
    _size = 0;
  }

  template <class Iterator>
  void assign(Iterator first, Iterator last) {
    vector<value_type> x(first, last);
    swap(x);
  }

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
  iterator _iterator;
};

template <class T>
std::ostream& operator<<(std::ostream& o, ft::vector<T>& vect) {
  for (int i = 0; i < vect.size(); i++) {
    o << vect[i] << " ";
  }
  return o;
}

template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
  if (lhs.size() == rhs.size()) {
    return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  return (false);
}

template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
  return (!(lhs == rhs));
}

template <class T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
  return (
      lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end()));
}

template <class T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
  return (rhs < lhs);
}

template <class T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
  return (!(lhs < rhs));
}

template <class T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
  return (!(lhs > rhs));
}

};  // namespace ft

#endif