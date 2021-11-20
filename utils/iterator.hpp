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
class random_access_iterator {
 public:
  /// Typedefs
  typedef typename iterator_traits<T*>::value_type value_type;
  typedef typename iterator_traits<T*>::pointer pointer;
  typedef typename iterator_traits<T*>::reference reference;
  typedef typename iterator_traits<T*>::difference_type difference_type;
  typedef typename iterator_traits<T*>::iterator_category iterator_category;

  /// Constructers and destructor
  random_access_iterator() {}
  template <class iterator>
  random_access_iterator(iterator const& src) : _ptr(nullptr) {
    *this = src;
  }
  random_access_iterator(pointer ptr) : _ptr(ptr) {}
  ~random_access_iterator() {}

  /// Operator overloads
  // random_access_iterator& operator=(random_access_iterator src) {
  //   if (this != &src) _ptr = src._ptr;
  //   return *this;
  // }

  pointer& ptr() { return _ptr; }

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

  bool operator==(const random_access_iterator& rhs) const {
    return _ptr == rhs._ptr;
  };

  typename random_access_iterator::difference_type operator-(
      const random_access_iterator& rhs) {
    return (_ptr - rhs._ptr);
  }

  random_access_iterator& operator+(
      typename random_access_iterator::difference_type amount) {
    _ptr += amount;
    return *this;
  }

  friend bool operator!=(random_access_iterator const& rhs,
                         random_access_iterator const& lhs) {
    return (rhs._ptr != lhs._ptr);
  }

 private:
  pointer _ptr;
};

template <class Iterator>
Iterator& operator+(typename Iterator::difference_type amount, Iterator& src) {
  src += amount;
  return (src);
}

// template <class iterator, class iterator2>
// bool operator==(const iterator& rhs, const iterator2& lhs) {
//   return (rhs.ptr() == lhs.ptr());
// }

template <class Iterator, class Distance>
void advance(Iterator& it, Distance n) {
  it += n;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first,
                                                             Iterator last) {
  return first - last;
}

};  // namespace ft
#endif
