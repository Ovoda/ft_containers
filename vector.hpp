#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator.hpp>
#include <memory>
#include <utils.hpp>

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef random_access_iterator<value_type> iterator;
  typedef random_access_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

  vector(const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(0), _alloc(alloc) {}

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(n), _capacity(n), _alloc(alloc) {
    _array = _alloc.allocate(n);
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_array + i, val);
    }
  }

  template <class InputIterator>
  vector(InputIterator first,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type last,
         const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(0), _alloc(alloc) {
    _size = last - first;
    _capacity = _size;
    _array = _alloc.allocate(_size);
    for (int i = 0; first != last; first++, i++) {
      _alloc.construct(_array + i, *first);
    }
  }

  vector(const vector &src) : _array(NULL), _size(0), _capacity(0) {
    *this = src;
  }

  ~vector() {
    for (size_t i = 0; i < _size; i++) {
      _alloc.destroy(_array + i);
    }
    _alloc.deallocate(_array, _capacity);
  }

  iterator begin() { return iterator(_array); }
  const_iterator begin() const { return const_iterator(_array); }

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
      while (_size > n) {
        pop_back();
      }
    } else if (n > _size) {
      insert(end(), n - _size, val);
      // if (n > _capacity) {
      //   if (_capacity * 2 > n) {
      //     reserve(_capacity * 2);
      //   } else {
      //     reserve(n);
      //   }
      //   while (_size < n) {
      //     std::cout << "here" << std::endl;
      //     _alloc.construct(&_array[_size++], val);
      //   }
      // } else {
      //   while (_size < n) {
      //     _alloc.construct(&_array[_size++], val);
      //   }
      // }
    }
  }

  size_type capacity() const { return (_capacity); }

  bool empty() const { return (_size == 0); }

  void reserve(size_type n) {
    if (n > max_size()) throw std::length_error("vector::reserve");
    if (n >= _capacity && n > 0) {
      pointer tmp = _alloc.allocate(n);
      if (_capacity > 0) {
        for (size_t i = 0; i < _size; i++) {
          _alloc.construct(tmp + i, _array[i]);
          _alloc.destroy(&_array[i]);
        }
        _alloc.deallocate(_array, _capacity);
      }
      _array = tmp;
      _capacity = n;
    }
  }

  vector &operator=(const vector &x) {
    if (this != &x) {
      for (size_t i = 0; i < _size; i++) {
        _alloc.destroy(_array + i);
      }
      if (_capacity < x.size()) {
        _alloc.deallocate(_array, _capacity);
        _array = _alloc.allocate(x._size);
        _capacity = x._size;
      }
      for (_size = 0; _size < x._size; _size++) {
        _alloc.construct(_array + _size, x[_size]);
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

  void push_back(value_type const &val) {
    if (_size >= _capacity) {
      _capacity <= 0 ? reserve(1) : reserve(_capacity *= 2);
    }
    _alloc.construct(&_array[_size++], val);
  }

  void pop_back() { _alloc.destroy(&_array[_size-- - 1]); }

  iterator insert(iterator position, const value_type &val) {
    int n = position - begin();
    insert(position, 1, val);
    return (iterator(&operator[](n)));
  }

  void insert(iterator position, size_type n, const value_type &val) {
    if (n <= 0) return;
    int index = (position - begin());
    if (_size + n > _capacity) {
      if (_size * 2 > _size + n) {
        reserve(_size * 2);
      } else {
        reserve(_size + n);
      }
    }

    for (int i = _size - 1; i >= index; i--) {
      _alloc.construct(_array + i + n, _array[i]);
      _alloc.destroy(_array + i);
    }

    for (size_t i = index; i < index + n; i++) {
      _alloc.construct(_array + i, val);
    }
    _size += n;
  }

  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    size_t n = last - first;
    int index = (position - begin());
    if (_size + n > _capacity) {
      if (_capacity * 2 > _size + n) {
        reserve(_capacity * 2);
      } else {
        reserve(_size + n);
      }
    }

    for (int i = _size - 1; i >= index; i--) {
      _alloc.construct(_array + i + n, _array[i]);
      _alloc.destroy(_array + i);
    }

    for (size_t i = index; i < index + n; i++, first++) {
      _alloc.construct(_array + i, *first);
    }
    _size += n;
  }

  iterator erase(iterator position) { return (erase(position, position + 1)); }

  iterator erase(iterator first, iterator last) {
    size_t diff = last - first;
    size_t i = first - _array;
    for (; i < _size - diff; i++) {
      _alloc.destroy(_array + i);
      _alloc.construct(_array + i, _array[i + diff]);
    }
    for (; i < _size; i++) {
      _alloc.destroy(_array + i);
    }
    _size -= diff;
    return iterator(first);
  }

  void swap(vector &x) {
    size_t tmp_size;
    tmp_size = _size;
    _size = x._size;
    x._size = tmp_size;

    size_t tmp_capacity;
    tmp_capacity = _capacity;
    _capacity = x._capacity;
    x._capacity = tmp_capacity;

    pointer tmp_array;
    tmp_array = _array;
    _array = x._array;
    x._array = tmp_array;
  }

  void clear() {
    for (size_t i = 0; i < _size; i++) {
      _alloc.destroy(_array + i);
    }
    _size = 0;
  }

  template <class Iterator>
  void assign(Iterator first,
              typename ft::enable_if<!is_integral<Iterator>::value,
                                     Iterator>::type last) {
    clear();
    for (; first != last; first++) {
      push_back(*first);
    }
  }

  allocator_type get_allocator() const { return (_alloc); }

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
};

template <class T>
std::ostream &operator<<(std::ostream &o, ft::vector<T> &vect) {
  for (int i = 0; i < vect.size(); i++) {
    o << vect[i] << " ";
  }
  return o;
}

template <class T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
  if (lhs.size() == rhs.size()) {
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  return (false);
}

template <class T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
  return (!(lhs == rhs));
}

template <class T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs) {
  return (
      lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs) {
  return (rhs < lhs);
}

template <class T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {
  return (!(lhs > rhs));
}

template <class T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {
  return (!(lhs < rhs));
}

template <class T>
void swap(vector<T> &_a, vector<T> &_b) {
  _a.swap(_b);
}
};  // namespace ft

#endif