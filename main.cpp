
#include <vector.hpp>

int main(void) {
  const int size = 5;
  ft::vector<int> const vct(size);
  ft::vector<int>::iterator it = vct.begin();  // <-- error expected

  for (int i = 0; i < size; ++i) it[i] = i;

  return (0);
}