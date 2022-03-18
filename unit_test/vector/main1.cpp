#include "header.hpp"

int
main (void)
{
  std::allocator<T> _alloc;
  size_t common_size = 0;

  /* Testing constructor */
  NS::vector<T> _v_default0;
  NS::vector<T> _v_default1 (_alloc);
  NS::vector<T> _v_fill0 (10, 42);
  NS::vector<T> _v_fill1 (10, 42, _alloc);
  NS::vector<T> _v_range0 (_v_fill0.begin (), _v_fill0.end ());
  NS::vector<T> _v_range1 (_v_fill0.begin (), _v_fill0.end (),
                           _v_fill0.get_allocator ());
  NS::vector<T>::const_iterator _cbegin = _v_range0.begin();
  NS::vector<T>::const_iterator _cend = _v_range0.end();
  const NS::vector<T> _v_range2 (_cbegin, _cbegin);

  NS::vector<T> _v_copy (_v_fill0);

  std::cout << _v_default0.size () << std::endl;
  std::cout << _v_default1.size () << std::endl;
  std::cout << _v_fill0.size () << std::endl;
  std::cout << _v_fill1.size () << std::endl;
  std::cout << _v_range0.size () << std::endl;
  std::cout << _v_range1.size () << std::endl;
  std::cout << _v_range2.size () << std::endl;
  std::cout << _v_copy.size () << std::endl;

  if ((_v_fill0.size () == _v_fill1.size ())
      && (_v_fill0.size () == _v_range0.size ())
      && (_v_fill0.size () == _v_range1.size ())
      && (_v_fill0.size () == _v_copy.size ()))
    {
      common_size = _v_fill0.size ();
    }
  if (common_size == 0)
    {
      return (1);
    }

  for (size_t i = 0; i < _v_fill0.size (); i++)
    {
      std::cout << _v_fill0[i] << std::endl;
      std::cout << _v_fill1[i] << std::endl;
      std::cout << _v_range0[i] << std::endl;
      std::cout << _v_range1[i] << std::endl;
      std::cout << _v_copy[i] << std::endl;
    }

  std::cout << std::boolalpha
            << (_v_range1.get_allocator () == _v_fill1.get_allocator ())
            << std::endl;
  std::cout << std::boolalpha
            << (_v_range1.get_allocator () == _v_default0.get_allocator ())
            << std::endl;

  return (0);
}