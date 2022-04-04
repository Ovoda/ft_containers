#include <map.hpp>

int main() {
  ft::map<int, int> m;
  for (int i = 0; i < 10; i++) {
    m[i] = i;
  }
  m._tree.print2D();
  return (0);
}