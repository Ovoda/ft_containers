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



void
const_ite_print_vector (NS::vector<T> &_vec)
{
  for (NS::vector<T>::const_iterator _cite = _vec.begin ();
       _cite != _vec.end (); _cite++)
    {
      std::cout << *_cite << " ";
    }
  std::cout << std::endl;
}

void
ite_print_vector (NS::vector<T> &_vec)
{
  for (NS::vector<T>::iterator _ite = _vec.begin (); _ite != _vec.end ();
       _ite++)
    {
      std::cout << *_ite << " ";
    }
  std::cout << std::endl;
}

void
size_bracket_print_vector (NS::vector<T> &_vec)
{
  for (size_t i = 0; i < _vec.size (); i++)
    {
      std::cout << _vec[i] << " ";
    }
  std::cout << std::endl;
}

void
size_at_print_vector (NS::vector<T> &_vec)
{
  for (size_t i = 0; i < _vec.size (); i++)
    {
      std::cout << _vec.at (i) << " ";
    }
  std::cout << std::endl;
}

size_t
print_vector (NS::vector<T> &_vec)
{
  test::const_ite_print_vector (_vec);
  test::ite_print_vector (_vec);
  test::size_bracket_print_vector (_vec);
  test::size_at_print_vector (_vec);
  return (_vec.size ());
}

}

#endif