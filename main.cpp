#include <iostream>
#include <reverse_iterator.hpp>
#include <std_lib.hpp>
#include <vector.hpp>
#include <vector>

#define N ft
// #define N std

int main() {
  N::vector<int> _sv(3, 42);
  N::vector<int> _fv(4, 43);

  {
    N::vector<int>::iterator _ite = _sv.begin();
    for (; _ite != _sv.end(); _ite++) {
      std::cout << *_ite << " ";
    }
    std::cout << std::endl;

    N::vector<int>::iterator _ite1 = _fv.begin();
    for (; _ite1 != _fv.end(); _ite1++) {
      std::cout << *_ite1 << " ";
    }
    std::cout << std::endl;
  }

  N::vector<int>::iterator _ite = _sv.begin();
  _sv.swap(_fv);

  {
    for (; _ite != _fv.end(); _ite++) {
      std::cout << *_ite << " ";
    }
    std::cout << std::endl;

    N::vector<int>::iterator _ite1 = _fv.begin();
    for (; _ite1 != _fv.end(); _ite1++) {
      std::cout << *_ite1 << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}