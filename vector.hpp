#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <cstddef>
#include <iostream>
// #include <xiterator.hpp>
#include <memory>

#include "utils/iterator.hpp"
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
  //   typedef reverse_iterator;
  //   typedef const_reverse_iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

  explicit vector() : _size(0), _capacity(0), _array(nullptr) {}

  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _size(0), _capacity(0), _array(nullptr) {
    for (size_type i = 0; i < n; i++) push_back(val);
  }

  template <class InputIterator>
  vector(InputIterator first,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type last)
      : _size(0), _capacity(0), _array(nullptr) {
    for (iterator i = first; i != last; i++) push_back(*i);
  }

  vector(const vector& src) : _size(0), _capacity(0), _array(nullptr) {
    *this = src;
  }

  ~vector() {
    if (_capacity > 0) {
      clear();
      _alloc.deallocate(_array, _capacity);
    }
  }

  iterator begin() { return iterator(&_array[0]); }
  const_iterator begin() const { return const_iterator(&_array[0]); }

  iterator end() { return iterator(&_array[_size]); }
  const_iterator end() const { return const_iterator(&_array[_size]); }

  //         reverse_iterator rbegin();
  // const_reverse_iterator rbegin() const;

  //         reverse_iterator rend();
  // const_reverse_iterator rend() const;

  size_type size() const { return _size; }

  size_type max_size() const { return (_alloc.max_size()); }

  //   void resize(size_type n, value_type val = value_type()) {}

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
      _array = _alloc.allocate(_capacity);
      for (const_iterator it = x.begin(); it != x.end(); ++it) {
        _alloc.construct(&_array[_size++], *it);
      }
    }
    return *this;
  }

  reference operator[](size_type index) { return (_array[index]); }
  const_reference operator[](size_type index) const { return (_array[index]); }

  reference at(size_type n) { return _array[n]; }
  const_reference at(size_type n) const { return _array[n]; }

  reference front() { return _array[0]; }
  const_reference front() const { return _array[0]; }

  reference back() { return _array[_size - 1]; }
  const_reference back() const { return _array[_size - 1]; }

  void push_back(value_type const& val) {
    static int i = 0;
    if (_size >= _capacity) {
      _capacity <= 0 ? reserve(1) : reserve(_capacity *= 2);
    }
    _alloc.construct(&_array[_size++], val);
    i++;
  }

  void pop_back() { _size--; }

  void swap(vector& x) {
    pointer tmp_array = _array;
    size_type tmp_size = _size;
    size_type tmp_capacity = _capacity;

    x._array = _array;
    x._size = _size;
    x._capacity = _capacity;

    _array = tmp_array;
    _size = tmp_size;
    _capacity = tmp_capacity;
  }

  void clear() {
    for (iterator it = begin(); it != end(); ++it) {
      _alloc.destroy(&(*it));
    }
    _size = 0;
  }

  void assign(size_type n, value_type const val) {
    vector<value_type> x(n, val);
    swap(x);
  }

  template <class Iterator>
  void assign(Iterator first, Iterator last) {
    vector<value_type> x(first, last);
    swap(x);
  }

 private:
  pointer _array;
  size_type _capacity;
  size_type _size;
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
};  // namespace ft

#endif