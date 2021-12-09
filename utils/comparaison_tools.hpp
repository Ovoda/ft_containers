#ifndef FT_COMPARAISON_TOOLS_CPP
#define FT_COMPARAISON_TOOLS_CPP

namespace ft {

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

}  // namespace ft

#endif