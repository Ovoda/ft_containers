#include "header.hpp"

#ifndef T
#define T int
#endif

int
main (void)
{

  /* Testing the following :
  ** operator=()
  ** operator==()
  ** push_back()
  ** pop_back()
  ** clear()
  ** empty()
  ** size()
  ** capacity()
  */

  NS::vector<T> _v_default0;
  NS::vector<T> _v_default1;
  NS::vector<T> _v_fill (12, 0);

  for (size_t i = 0; i < 21; i++)
    {
      _v_default0.push_back (i);
      std::cout << _v_default0.capacity() << std::endl;
      std::cout << _v_default0.size() << std::endl;
    }

  _v_default1 = _v_default0;
  std::cout << test::print_vector (_v_default0) << std::endl;
  std::cout << test::print_vector (_v_default1) << std::endl;

  std::cout << std::boolalpha << (_v_default0 == _v_default1) << std::endl;
  _v_default0.push_back (0);
  std::cout << std::boolalpha << (_v_default0 == _v_default1) << std::endl;
  _v_default0.pop_back ();
  std::cout << std::boolalpha << (_v_default0 == _v_default1) << std::endl;
  _v_default0.clear ();
  _v_default1.clear ();
  std::cout << std::boolalpha << (_v_default0 == _v_default1) << std::endl;


  _v_default1.push_back(1);
  _v_default1.push_back(2);
  _v_default1.push_back(3);
  _v_fill = _v_default1;
  std::cout << test::print_vector (_v_fill) << std::endl;
  std::cout << test::print_vector (_v_default1) << std::endl;

  while (!_v_default1.empty()) {
    _v_fill.push_back(_v_default1.back());
    _v_default1.pop_back();
  } 

  std::cout << _v_fill.size() << std::endl;
  std::cout << _v_default1.size() << std::endl;

  _v_default1.push_back(1);
  _v_default1.push_back(2);
  _v_default1.push_back(3);
  _v_fill = _v_default1;
  std::cout << test::print_vector (_v_fill) << std::endl;
  std::cout << test::print_vector (_v_default1) << std::endl;

  while (!_v_fill.empty()) {
    _v_default1.push_back(_v_fill.front());
    _v_fill.pop_back();
  } 

  std::cout << _v_fill.size() << std::endl;
  std::cout << _v_default0.size() << std::endl;
  std::cout << _v_fill.capacity() << std::endl;
  std::cout << _v_default0.capacity() << std::endl;

  return (0);
}