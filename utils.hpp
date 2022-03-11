#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft {

/* Less for map */

template <class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

template <class T>
struct less : binary_function<T, T, bool> {
  bool operator()(const T& x, const T& y) const { return x < y; }
};

/* Pair */
template <class T1, class T2>
class pair {
 public:
  typedef T1 first_type;
  typedef T2 second_type;

  pair(void) : first(), second() {}

  pair(const first_type& a, const second_type& b) : first(a), second(b) {}

  template <class U, class V>
  pair(const pair<U, V>& src) : first(src.first), second(src.second) {}

  ~pair() {}

  pair& operator=(pair const& rhs) {
    if (*this != rhs) {
      first = rhs.first;
      second = rhs.second;
    }
    return *this;
  }

  T1 first;
  T2 second;
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
  return (pair<T1, T2>(x, y));
}

template <class T>
void swap(T& _a, T& _b) {
  T _tmp(_a);
  _a = _b;
  _b = _tmp;
}

/* lexicographical_compare and equal */

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  while (first1 != last1) {
    if (*first1 != *first2) {
      return (false);
    }
    first1++, first2++;
  }
  return (true);
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate p) {
  while (first1 != last1) {
    if (p(*first1, *first2) == false) {
      return (false);
    }
    first1++, first2++;
  }
  return (true);
}

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2, BinaryPredicate p) {
  for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
    if (p(*first1, *first2)) return true;
    if (p(*first2, *first1)) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

/* Type traits */
template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
  operator T() { return v; }
};

typedef integral_constant<bool, false> false_type;

typedef integral_constant<bool, true> true_type;

// Template (no specialization)
template <typename>
struct is_integral_base : false_type {};

// Template specialization
template <>
struct is_integral_base<bool> : true_type {};

template <>
struct is_integral_base<char> : true_type {};

template <>
struct is_integral_base<char16_t> : true_type {};

template <>
struct is_integral_base<char32_t> : true_type {};

template <>
struct is_integral_base<wchar_t> : true_type {};

template <>
struct is_integral_base<signed char> : true_type {};

template <>
struct is_integral_base<short int> : true_type {};

template <>
struct is_integral_base<int> : true_type {};

template <>
struct is_integral_base<long int> : true_type {};

template <>
struct is_integral_base<long long int> : true_type {};

template <>
struct is_integral_base<unsigned char> : true_type {};

template <>
struct is_integral_base<unsigned short int> : true_type {};

template <>
struct is_integral_base<unsigned int> : true_type {};

template <>
struct is_integral_base<unsigned long int> : true_type {};

template <>
struct is_integral_base<unsigned long long int> : true_type {};

template <typename T>
struct is_integral : is_integral_base<T> {};

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};

}  // namespace ft

#endif