#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP
#include <cstddef>

namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Ite>
struct iterator_traits {
  typedef typename Ite::value_type value_type;
  typedef typename Ite::pointer pointer;
  typedef typename Ite::reference reference;
  typedef typename Ite::iterator_category iterator_category;
  typedef typename Ite::difference_type difference_type;
};

// Pointer specialisation
template <class T>
struct iterator_traits<T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

// Constant pointer specialization
template <class T>
struct iterator_traits<const T*> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator {
  typedef typename iterator_traits<T*>::value_type value_type;
  typedef typename iterator_traits<T*>::pointer pointer;
  typedef typename iterator_traits<T*>::reference reference;
  typedef typename iterator_traits<T*>::difference_type difference_type;
  typedef typename iterator_traits<T*>::iterator_category iterator_category;
};

template <class Iterator, class Distance>
void advance(Iterator& it, Distance n) {
  it += n;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first,
                                                             Iterator last) {
  return first - last;
}

template <class T>
class random_access_iterator : public iterator<T> {
 public:
  /// Typedefs
  typedef typename iterator<T>::value_type value_type;
  typedef typename iterator<T>::pointer pointer;
  typedef typename iterator<T>::reference reference;
  typedef typename iterator<T>::difference_type difference_type;
  typedef typename iterator<T>::iterator_category iterator_category;

  /// Constructers and destructor
  random_access_iterator() {}
  explicit random_access_iterator(random_access_iterator const& src)
      : _ptr(src._ptr) {}
  template <class it>
  random_access_iterator(random_access_iterator<it> const& src)
      : _ptr(src.ptr()) {}
  random_access_iterator(pointer ptr) : _ptr(ptr) {}
  ~random_access_iterator() {}

  pointer ptr() const { return _ptr; }

  random_access_iterator& operator++() {
    _ptr++;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp = *this;
    ++_ptr;
    return tmp;
  }

  random_access_iterator& operator--() {
    _ptr--;
    return *this;
  }

  random_access_iterator operator--(int) {
    random_access_iterator tmp = *this;
    operator--();
    return tmp;
  }

  reference operator*() { return *_ptr; }
  pointer operator->() { return _ptr; }

  bool operator>(random_access_iterator const& rhs) const {
    return (this->_ptr > rhs._ptr);
  }

  bool operator>=(random_access_iterator const& rhs) const {
    return (this->_ptr >= rhs._ptr);
  }

  bool operator<(random_access_iterator const& rhs) const {
    return (this->_ptr < rhs._ptr);
  }

  bool operator<=(random_access_iterator const& rhs) const {
    return (this->_ptr <= rhs._ptr);
  }

  random_access_iterator& operator-=(
      typename random_access_iterator<T>::difference_type amount) {
    this->_ptr -= amount;
    return *this;
  }

  random_access_iterator& operator+=(
      typename random_access_iterator::difference_type amount) {
    this->_ptr += amount;
    return *this;
  }

  typename random_access_iterator::reference operator[](
      typename random_access_iterator::difference_type index) const {
    return (_ptr[index]);
  }

  random_access_iterator& operator-(
      typename random_access_iterator::difference_type amount) {
    _ptr -= amount;
    return *this;
  }

  typename random_access_iterator::difference_type operator-(
      const random_access_iterator& rhs) {
    return (_ptr - rhs._ptr);
  }

  random_access_iterator operator+(const difference_type n) const {
    return (_ptr + n);
  }

  // typename random_access_iterator::difference_type operator+(
  //     const random_access_iterator& rhs) {
  //   return (_ptr + rhs._ptr);
  // }

 private:
  pointer _ptr;
};

template <class T>
random_access_iterator<T> operator+(
    typename random_access_iterator<T>::difference_type n,
    const random_access_iterator<T>& it) {
  return (it + n);
}

template <class T, class U>
bool operator!=(const random_access_iterator<T>& rhs,
                const random_access_iterator<U>& lhs) {
  return (rhs.ptr() != lhs.ptr());
}

template <class T, class U>
bool operator==(const random_access_iterator<T>& rhs,
                const random_access_iterator<U>& lhs) {
  return (rhs.ptr() == lhs.ptr());
}

template <class T, class U>
bool operator>(const random_access_iterator<T>& rhs,
               const random_access_iterator<U>& lhs) {
  return (rhs.ptr() > lhs.ptr());
}

template <class T, class U>
bool operator<(const random_access_iterator<T>& rhs,
               const random_access_iterator<U>& lhs) {
  return (rhs.ptr() < lhs.ptr());
}

template <class T, class U>
bool operator>=(const random_access_iterator<T>& rhs,
                const random_access_iterator<U>& lhs) {
  return (rhs.ptr() >= lhs.ptr());
}

template <class T, class U>
bool operator<=(const random_access_iterator<T>& rhs,
                const random_access_iterator<U>& lhs) {
  return (rhs.ptr() <= lhs.ptr());
}

};  // namespace ft
#endif
