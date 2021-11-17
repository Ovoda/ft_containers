#include <iostream>
#include <vector.hpp>
#include <vector>

int main() {
  std::vector<int> ok;

  ok.assign(10, 5);

  for (std::vector<int>::iterator it = ok.begin(); it != ok.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  ft::vector<int> ok2;

  ok2.assign(10, 5);

  for (ft::vector<int>::iterator it = ok2.begin(); it != ok2.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  return 0;
}