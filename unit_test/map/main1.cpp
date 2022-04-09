#include <header.hpp>

int main() {
  NS::map<int, int> _m;
  NS::map<int, int> _m1;
  NS::map<int, int>::iterator _ite;
  NS::map<int, int>::reverse_iterator _rite;

  for (size_t i = 0; i < 10; i++) {
    _m[i] = i;
  }

  for (_ite = _m1.begin(); _ite != _m1.end(); _ite++) {
    std::cout << "_m1[" << _ite->first << "] = " << _ite->second << std::endl;
  }
  _m1 = _m;
  for (_ite = _m1.begin(); _ite != _m1.end(); _ite++) {
    std::cout << "_m1[" << _ite->first << "] = " << _ite->second << std::endl;
  }

  _m.clear();

  for (_rite = _m1.rbegin(); _rite != _m1.rend(); _rite++) {
    _m[_rite->first] = _rite->second;
    std::cout << "added " << _rite->first << std::endl;
  }

  for (_ite = _m.begin(); _ite != _m.end(); _ite++) {
    std::cout << "_m[" << _ite->first << "] = " << _ite->second << std::endl;
  }

  return (0);
}