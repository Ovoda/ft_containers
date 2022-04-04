#include <list>
#include <map.hpp>
#include <map>

int main() {
  std::list<ft::pair<int, int> > lst;
  unsigned int lst_size = 7;
  for (unsigned int i = 0; i < lst_size; ++i)
    lst.push_back(T3(lst_size - i, i));

  ft::map<int, int> mp(lst.begin(), lst.end());
  ft::map<int, int>::iterator it = mp.begin(), ite = mp.end();

  ft::map<int, int> mp_range(it, --(--ite));
  for (int i = 0; it != ite; ++it) it->second = ++i * 5;

  it = mp.begin();
  ite = --(--mp.end());
  ft::map<int, int> mp_copy(mp);
  for (int i = 0; it != ite; ++it) it->second = ++i * 7;
  return (0);
}