#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <vector.hpp>
#include <vector>

#include "utils/comparaison_tools.hpp"

// the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

template <class T>
void print_memory(T v) {
  std::cout << "Iterators" << std::endl;
  typename T::iterator it = v.begin();
  for (int i = 0; i < v.size() * 2; i++) {
    if (it == v.begin()) {
      std::cout << BLUE << "[" << &(*it) << "]" << RESET << " ";
    } else if (it == v.end()) {
      std::cout << RED << "[" << &(*it) << "]" << RESET << " ";
    } else {
      std::cout << &(*it) << " ";
    }
    it++;
  }

  std::cout << std::endl;

  std::cout << "Reverse Iterators" << std::endl;
  typename T::reverse_iterator rit = v.rbegin();
  for (int i = 0; i < v.size() * 2; i++) {
    if (rit == v.rbegin()) {
      std::cout << BLUE << "[" << &(*rit) << "]" << RESET << " ";
    } else if (rit == v.rend()) {
      std::cout << RED << "[" << &(*rit) << "]" << RESET << " ";
    } else {
      std::cout << &(*rit) << " ";
    }
    rit++;
  }
  std::cout << std::endl;
}

template <class T>
void test() {
  T v;
  v.push_back(5);
  v.push_back(15);
  v.push_back(25);
  v.push_back(35);

  print_memory(v);
  std::cout << std::endl;
}

template <class T>
void test_rite() {
  const int size = 5;
  T vct(size);
  typename T::reverse_iterator it = vct.rbegin();
  typename T::const_reverse_iterator ite = vct.rbegin();

  for (int i = 0; i < size; ++i) it[i] = (size - i) * 5;

  it = it + 5;
  it = 1 + it;
  it = it - 4;
  // std::cout << *(it += 2) << std::endl;
  // std::cout << *(it -= 1) << std::endl;

  *(it -= 2) = 42;
  *(it += 2) = 21;

  // std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2)
  // << std::endl;

  // std::cout << "(it == const_it): " << (ite == it) << std::endl;
  std::cout << "ite => " << &*ite << std::endl;
  std::cout << "it  => " << &*it << std::endl;
  std::cout << "(const_ite - it): " << (it - ite) << std::endl;

  std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
}

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1) {
  std::cout << (first < second) << std::endl;
  std::cout << (first <= second) << std::endl;
  std::cout << (first > second) << std::endl;
  std::cout << (first >= second) << std::endl;
  if (redo) ft_eq_ope(second, first, 0);
}

template <class T>
void test_eq_ope() {
  const int size = 5;
  T vct(size);
  typename T::reverse_iterator it_0(vct.rbegin());
  typename T::reverse_iterator it_1(vct.rend());
  typename T::reverse_iterator it_mid;
  typename T::const_reverse_iterator cit_0 = vct.rbegin();
  typename T::const_reverse_iterator cit_1;
  typename T::const_reverse_iterator cit_mid;

  for (int i = size; it_0 != it_1; --i) *it_0++ = i;
  it_0 = vct.rbegin();
  cit_1 = vct.rend();
  it_mid = it_0 + 3;
  cit_mid = it_0 + 3;
  cit_mid = cit_0 + 3;
  cit_mid = it_mid;

  std::cout << std::boolalpha;
  std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

  std::cout << "\t\tft_eq_ope:" << std::endl;
  // regular it
  ft_eq_ope(it_0 + 3, it_mid);
  ft_eq_ope(it_0, it_1);
  ft_eq_ope(it_1 - 3, it_mid);
  // const it
  ft_eq_ope(cit_0 + 3, cit_mid);
  ft_eq_ope(cit_0, cit_1);
  ft_eq_ope(cit_1 - 3, cit_mid);
  // both it
  ft_eq_ope(it_0 + 3, cit_mid);
  ft_eq_ope(it_mid, cit_0 + 3);
  ft_eq_ope(it_0, cit_1);
  ft_eq_ope(it_1, cit_0);
  ft_eq_ope(it_1 - 3, cit_mid);
  ft_eq_ope(it_mid, cit_1 - 3);
}

bool compare_string_nocase(std::string const a, std::string const b) {
  if (a.length() != b.length()) {
    return (false);
  }
  for (int i = 0; i < a.length(); i++) {
    if (std::toupper(a[i]) != std::toupper(b[i])) {
      return (false);
    }
  }
  return (true);
}

template <class vector>
void comparaison_tool_test() {
  vector v;
  vector v2;
  v.push_back(std::string("hi"));
  v.push_back(std::string("hello"));
  v.push_back(std::string("good morning"));
  v2.push_back(std::string("HI"));
  v2.push_back(std::string("HELlO"));
  v2.push_back(std::string("GOOD MORNING"));

  typedef
      typename ft::iterator_traits<typename vector::iterator>::value_type __v2;

  std::cout << typeid(__v2).name() << std::endl;

  std::cout << std::boolalpha
            << (ft::equal(v.begin(), v.end(), v2.begin(),
                          compare_string_nocase))
            << std::endl;
  std::cout << std::boolalpha
            << (std::equal(v.begin(), v.end(), v2.begin(),
                           compare_string_nocase))
            << std::endl;
}

template <class vector>
void relational_ope_test(vector lhs, vector rhs) {
  std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
  std::cout << "lt: " << (lhs < rhs) << " | le: " << (lhs <= rhs) << std::endl;
  std::cout << "gt: " << (lhs > rhs) << " | ge: " << (lhs >= rhs) << std::endl
            << std::endl;
}

int main() {
  ft::vector<int> v(4, 42);
  ft::vector<int>::iterator it = v.insert(++v.begin(), 43);
  std::cout << v << std::endl;
  std::cout << *it << std::endl;
  return (0);
}