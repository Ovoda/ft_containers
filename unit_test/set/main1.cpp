#include <header.hpp>

int main() {
  std::vector<int> v;
  for (int i = 0; i < 100; i++) {
    v.push_back(i - 50);
  }
  NS::set<int> s;
  NS::set<int> range(v.begin(), v.end());
  NS::set<int> copy(range);

  s = range;

  NS::set<int>::iterator b = s.begin();
  NS::set<int>::const_iterator cb = s.begin();
  NS::set<int>::reverse_iterator rb = s.rbegin();
  NS::set<int>::const_reverse_iterator rcb = s.rbegin();
  NS::set<int>::iterator e = s.end();
  NS::set<int>::const_iterator ce = s.end();
  NS::set<int>::reverse_iterator re = s.rend();
  NS::set<int>::const_reverse_iterator rce = s.rend();
  for (; b != e; b++) {
    std::cout << *b << " ";
  }
  std::cout << std::endl;
  for (; cb != ce; cb++) {
    std::cout << *cb << " ";
  }
  std::cout << std::endl;
  for (; rb != re; rb++) {
    std::cout << *rb << " ";
  }
  std::cout << std::endl;
  for (; rcb != rce; rcb++) {
    std::cout << *rcb << " ";
  }
  std::cout << std::endl;

  if (!s.empty()) {
    std::cout << s.size() << std::endl;
  }
  s.max_size();

  s.clear();
  for (int i = 0; i < 100; i++) {
    s.insert(i - 50);
  }
  NS::set<int>::iterator tmp;
  for (NS::set<int>::iterator it = s.begin(); it != s.end();) {
    tmp = it;
    it++;
    s.erase(tmp);
  }

  if (s.empty()) {
    std::cout << "empty set" << std::endl;
  }

  std::cout << s.size() << " : " << copy.size() << std::endl;
  swap(s, copy);
  std::cout << s.size() << " : " << copy.size() << std::endl;
  for (NS::set<int>::iterator it = s.begin(); it != s.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  s.clear();

  for (int i = 0; i < 10; i++) {
    s.insert(i);
  }

  std::cout << std::boolalpha << (s.find(10) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.find(1) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.find(-10) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.find(100) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.find(1000) == s.end()) << std::endl;

  std::cout << s.count(10) << std::endl;
  std::cout << s.count(1) << std::endl;
  std::cout << s.count(-10) << std::endl;
  std::cout << s.count(100) << std::endl;
  std::cout << s.count(1000) << std::endl;

  std::cout << std::boolalpha << (s.lower_bound(10) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.lower_bound(1) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.lower_bound(-10) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.lower_bound(100) == s.end()) << std::endl;
  std::cout << std::boolalpha << (s.lower_bound(1000) == s.end()) << std::endl;

  std::cout << std::boolalpha << (*s.upper_bound(1)) << std::endl;
  std::cout << std::boolalpha << (*s.upper_bound(-10)) << std::endl;

  std::cout << std::boolalpha << (*s.equal_range(1).first) << " : "
            << (*s.equal_range(1).second) << std::endl;
  std::cout << std::boolalpha << (*s.equal_range(2).first) << " : "
            << (*s.equal_range(2).second) << std::endl;

  s.get_allocator();
  s.key_comp();
  s.value_comp();
}