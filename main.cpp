#include <unistd.h>

#include <iostream>
#include <vector.hpp>
#include <vector>

int main() {
  // std::vector<int> ok;

  // ok.assign(10, 5);

  // for (std::vector<int>::iterator it = ok.begin(); it != ok.end(); it++) {
  //   std::cout << *it << " ";
  // }
  // std::cout << std::endl;

  ft::vector<int> ok2;
  ok2.push_back(0);
  ok2.push_back(1);
  ok2.push_back(2);
  return 0;
}