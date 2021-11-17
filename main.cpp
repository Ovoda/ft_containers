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

  ft::vector<int> ori;
  ori.push_back(0);
  ori.push_back(1);
  ori.push_back(2);

  ft::vector<int> ori2;
  ori2.push_back(2);
  ori2.push_back(1);
  ori2.push_back(0);

  ft::vector<int> copy;

  copy = ori;
  std::cout << copy[0] << std::endl;
  std::cout << copy[1] << std::endl;
  std::cout << copy[2] << std::endl;

  copy = ori2;
  std::cout << copy[0] << std::endl;
  std::cout << copy[1] << std::endl;
  std::cout << copy[2] << std::endl;

  // for (ft::vector<int>::iterator it = copy.begin(); it != copy.end(); it++) {
  //   std::cout << *it << std::endl;
  // }
  return 0;
}