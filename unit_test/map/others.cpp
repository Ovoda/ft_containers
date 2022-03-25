#include "header.hpp"

bool
fncomp (char lhs, char rhs)
{
  return lhs < rhs;
}

struct classcomp
{
  bool
  operator() (const char &lhs, const char &rhs) const
  {
    return lhs < rhs;
  }
};

int
main (void)
{
  /* Testing constructor */
  {

    NS::map<char, int> first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    NS::map<char, int> second (first.begin (), first.end ());

    NS::map<char, int> third (second);

    NS::map<char, int, classcomp> fourth; // class as Compare

    bool (*fn_pt) (char, char) = fncomp;
    NS::map<char, int, bool (*) (char, char)> fifth (
        fn_pt); // function pointer as Compare
  }
  /* Testing operator=() */
  {
    NS::map<char, int> first;
    NS::map<char, int> second;

    first['x'] = 8;
    first['y'] = 16;
    first['z'] = 32;

    second = first;                // second now contains 3 ints
    first = NS::map<char, int> (); // and first is now empty

    std::cout << "Size of first: " << first.size () << '\n';
    std::cout << "Size of second: " << second.size () << '\n';
  }
  /* Testing operator[]() */
  {
    NS::map<char, std::string> mymap;

    mymap['a'] = "an element";
    mymap['b'] = "another element";
    mymap['c'] = mymap['b'];

    std::cout << "mymap['a'] is " << mymap['a'] << '\n';
    std::cout << "mymap['b'] is " << mymap['b'] << '\n';
    std::cout << "mymap['c'] is " << mymap['c'] << '\n';
    std::cout << "mymap['d'] is " << mymap['d'] << '\n';

    std::cout << "mymap now contains " << mymap.size () << " elements.\n";
  }
  /* Testing key_comp() */
  {
    NS::map<char, int> mymap;

    NS::map<char, int>::key_compare mycomp = mymap.key_comp ();

    mymap['a'] = 100;
    mymap['b'] = 200;
    mymap['c'] = 300;

    std::cout << "mymap contains:\n";

    char highest = mymap.rbegin ()->first; // key value of last element

    NS::map<char, int>::iterator it = mymap.begin ();
    do
      {
        std::cout << it->first << " => " << it->second << '\n';
      }
    while (mycomp ((*it++).first, highest));

    std::cout << '\n';
  }
  /* Testing value_comp() */
  {
    NS::map<char, int> mymap;

    mymap['x'] = 1001;
    mymap['y'] = 2002;
    mymap['z'] = 3003;

    std::cout << "mymap contains:\n";

    NS::pair<char, int> highest = *mymap.rbegin (); // last element

    NS::map<char, int>::iterator it = mymap.begin ();
    do
      {
        std::cout << it->first << " => " << it->second << '\n';
      }
    while (mymap.value_comp () (*it++, highest));
  }
  /* Testing get_allocator() */
  {
    int psize;
    NS::map<char, int> mymap;
    NS::pair<const char, int> *p;

    // allocate an array of 5 elements using mymap's allocator:
    p = mymap.get_allocator ().allocate (5);

    // assign some values to array
    psize = sizeof (NS::map<char, int>::value_type) * 5;

    std::cout << "The allocated array has a size of " << psize << " bytes.\n";

    mymap.get_allocator ().deallocate (p, 5);
  }

  return (0);
}