#ifndef STD_LIB_HEADER
#define STD_LIB_HEADER

namespace ft {
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
    if (this != &rhs) {
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

};  // namespace ft

#endif