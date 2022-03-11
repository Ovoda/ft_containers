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
  typedef random_access_iterator<T> iterator;
  typedef random_access_iterator<const T> const_iterator;
  typedef reverse_iterator_base<iterator> reverse_iterator;
  typedef reverse_iterator_base<const_iterator> const_reverse_iterator;
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
    for (InputIterator i = first; i != last; i++) push_back(*i);
  }

  vector(const vector& src) : _array(nullptr), _size(0), _capacity(0) {
    *this = src;
  }

  ~vector() {
    if (_capacity <= 0) return;
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
      for (size_t i = _size; i < n; i++) {
        _alloc.destroy(_array + i);
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
      vector<value_type> tmp;
      tmp._array = tmp._alloc.allocate(n);
      tmp._capacity = n;
      tmp._size = 0;

      for (size_t i = 0; i < _size; i++) {
        tmp._alloc.construct(tmp._array + i, _array[i]);
        tmp._size++;
      }

      tmp.swap(*this);
    }
  }

  vector& operator=(const vector& x) {
    if (this != &x) {
      assign(x.begin(), x.end());
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
    if (_size >= _capacity) {
      _capacity <= 0 ? reserve(1) : reserve(_capacity *= 2);
    }
    _alloc.construct(&_array[_size++], val);
  }

  void pop_back() { _alloc.destroy(&_array[_size-- - 1]); }

  iterator insert(iterator position, const value_type& val) {
    int n = position - begin();
    insert(position, 1, val);
    return (iterator(&operator[](n)));
  }

  void insert(iterator position, size_type n, const value_type& val) {
    vector<T> tmp;
    for (iterator tmp_it = position; tmp_it != end(); tmp_it++) {
      tmp.push_back(*tmp_it);
    }
    resize(position - begin());
    for (size_type i = 0; i < n; i++) {
      push_back(val);
    }
    for (iterator tmp_it = tmp.begin(); tmp_it != tmp.end(); tmp_it++) {
      push_back(*tmp_it);
    }
  }

  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* =
          0) {
    vector<T> tmp;
    for (iterator tmp_it = begin(); tmp_it != position; tmp_it++) {
      tmp.push_back(*tmp_it);
    }

    for (; first != last; ++first) {
      tmp.push_back(*first);
    }

    for (iterator tmp_it = position; tmp_it != end(); tmp_it++) {
      tmp.push_back(*tmp_it);
    }
    tmp.swap(*this);
  }

  iterator erase(iterator position) { return (erase(position, position + 1)); }

  iterator erase(iterator first, iterator last) {
    difference_type distance = last - first;
    iterator ret = last - distance;
    for (; &(*(first + distance)) != &(*end()); ++first) {
      *first = *(first + distance);
    }
    _size -= distance;
    return (ret);
  }

  void swap(vector& x) {
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

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
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
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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
      lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
  return (rhs < lhs);
}

template <class T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
  return (!(lhs > rhs));
}

template <class T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
  return (!(lhs < rhs));
}

template <class T>
void swap(vector<T>& _a, vector<T>& _b) {
  _a.swap(_b);
}
};  // namespace ft

#endif