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
struct iterator_traits<T *> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

// Constant pointer specialization
template <class T>
struct iterator_traits<const T *> {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template <class Iterator, class Distance>
void advance(Iterator &it, Distance n) {
  it += n;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first,
                                                             Iterator last) {
  return first - last;
}

/// Iterator
template <class T>
class random_access_iterator
    : public iterator<ft::random_access_iterator_tag, T> {
 public:
  typedef
      typename iterator<random_access_iterator_tag, T>::value_type value_type;
  typedef typename iterator<random_access_iterator_tag, T>::pointer pointer;
  typedef typename iterator<random_access_iterator_tag, T>::reference reference;
  typedef typename iterator<random_access_iterator_tag, T>::difference_type
      difference_type;
  typedef typename iterator<random_access_iterator_tag, T>::iterator_category
      iterator_category;

  random_access_iterator() {}
  random_access_iterator(pointer const ptr) : _ptr(ptr) {}
  random_access_iterator(const random_access_iterator &src) : _ptr(src._ptr) {}
  ~random_access_iterator() {}

  pointer base() const { return _ptr; }

  random_access_iterator &operator=(const random_access_iterator &rhs) {
    if (*this != rhs) {
      _ptr = rhs._ptr;
    }
    return *this;
  }

  random_access_iterator &operator++() {
    _ptr++;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp = *this;
    operator++();
    return tmp;
  }

  random_access_iterator &operator--() {
    _ptr--;
    return *this;
  }

  random_access_iterator operator--(int) {
    random_access_iterator tmp = *this;
    operator--();
    return tmp;
  }

  reference operator*() const { return *_ptr; }
  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type index) const { return (_ptr[index]); }

  bool operator>(random_access_iterator const &rhs) const {
    return (this->_ptr > rhs._ptr);
  }

  bool operator>=(random_access_iterator const &rhs) const {
    return (this->_ptr >= rhs._ptr);
  }

  bool operator<(random_access_iterator const &rhs) const {
    return (this->_ptr < rhs._ptr);
  }

  bool operator<=(random_access_iterator const &rhs) const {
    return (this->_ptr <= rhs._ptr);
  }

  random_access_iterator &operator-=(const difference_type n) {
    _ptr -= n;
    return (*this);
  }

  random_access_iterator &operator+=(const difference_type n) {
    _ptr += n;
    return (*this);
  }

  random_access_iterator operator-(const difference_type n) {
    return (random_access_iterator(_ptr - n));
  }

  random_access_iterator operator+(const difference_type n) {
    return (random_access_iterator(_ptr + n));
  }

  difference_type operator-(const random_access_iterator &rhs) {
    return (_ptr - rhs._ptr);
  }

  difference_type operator+(const random_access_iterator &rhs) {
    return (_ptr + rhs._ptr);
  }

  /// Overloads
  template <class Ite1, class Ite2>
  friend bool operator!=(const random_access_iterator<Ite1> &rhs,
                         const random_access_iterator<Ite2> &lhs);

  template <class Ite1, class Ite2>
  friend bool operator==(const random_access_iterator<Ite1> &rhs,
                         const random_access_iterator<Ite2> &lhs);

  template <class Ite1, class Ite2>
  friend bool operator>(const random_access_iterator<Ite1> &rhs,
                        const random_access_iterator<Ite2> &lhs);

  template <class Ite1, class Ite2>
  friend bool operator<(const random_access_iterator<Ite1> &rhs,
                        const random_access_iterator<Ite2> &lhs);

  template <class Ite1, class Ite2>
  friend bool operator>=(const random_access_iterator<Ite1> &rhs,
                         const random_access_iterator<Ite2> &lhs);

  template <class Ite1, class Ite2>
  friend bool operator<=(const random_access_iterator<Ite1> &rhs,
                         const random_access_iterator<Ite2> &lhs);

 protected:
  pointer _ptr;
};

template <class T>
random_access_iterator<T> operator+(
    typename random_access_iterator<T>::difference_type n,
    random_access_iterator<T> &it) {
  return (it + n);
}

template <class Ite1, class Ite2>
typename random_access_iterator<Ite1>::difference_type operator-(
    random_access_iterator<Ite1> ite1, random_access_iterator<Ite2> ite2) {
  return (ite1.base() - ite2.base());
}

template <class T, class U>
bool operator!=(const random_access_iterator<T> &rhs,
                const random_access_iterator<U> &lhs) {
  return (rhs._ptr != lhs._ptr);
}

template <class T, class U>
bool operator==(const random_access_iterator<T> &rhs,
                const random_access_iterator<U> &lhs) {
  return (rhs._ptr == lhs._ptr);
}

template <class T, class U>
bool operator>(const random_access_iterator<T> &rhs,
               const random_access_iterator<U> &lhs) {
  return (rhs._ptr > lhs._ptr);
}

template <class T, class U>
bool operator<(const random_access_iterator<T> &rhs,
               const random_access_iterator<U> &lhs) {
  return (rhs._ptr < lhs._ptr);
}

template <class T, class U>
bool operator>=(const random_access_iterator<T> &rhs,
                const random_access_iterator<U> &lhs) {
  return (rhs._ptr >= lhs._ptr);
}

template <class T, class U>
bool operator<=(const random_access_iterator<T> &rhs,
                const random_access_iterator<U> &lhs) {
  return (rhs._ptr <= lhs._ptr);
}

};  // namespace ft
#endif
