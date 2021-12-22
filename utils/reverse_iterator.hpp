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
