#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <map.hpp>
#include <map>
#include <stack.hpp>
#include <stack>
#include <vector.hpp>
#include <vector>

#ifndef NS
#define NS ft
#endif

#ifndef T
#define T int
#endif

namespace test
{


template<class C>
void
reverse_ite_print_iterable (C &_c)
{
  for (typename C::reverse_iterator _rite = _c.rbegin ();
       _rite != _c.rend (); _rite++)
    {
      std::cout << *_rite << " ";
    }
  std::cout << std::endl;
}

template<class C>
void
const_reverse_ite_print_iterable (C &_c)
{
  for (typename C::const_reverse_iterator _rite = _c.rbegin ();
       _rite != _c.rend (); _rite++)
    {
      std::cout << *_rite << " ";
    }
  std::cout << std::endl;
}

template<class C>
void
const_ite_print_iterable (C &_c)
{
  for (typename C::const_iterator _cite = _c.begin ();
       _cite != _c.end (); _cite++)
    {
      std::cout << *_cite << " ";
    }
  std::cout << std::endl;
}

template<class C>
void
ite_print_iterable (C &_c)
{
  for (typename C::iterator _ite = _c.begin (); _ite != _c.end ();
       _ite++)
    {
      std::cout << *_ite << " ";
    }
  std::cout << std::endl;
}

template<class C>
void
size_bracket_print_ctn(C &_c)
{
  for (size_t i = 0; i < _c.size (); i++)
    {
      std::cout << _c[i] << " ";
    }
  std::cout << std::endl;
}

template<class C>
size_t
print_ctn (C &_c)
{
  test::const_ite_print_iterable (_c);
  test::ite_print_iterable (_c);
  test::size_bracket_print_ctn (_c);
  return (_c.size ());
}

}

#endif