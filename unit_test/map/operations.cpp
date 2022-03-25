#include "header.hpp"

int
main (void)
{
  /* Testing find() */
  {
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find ('b');
    if (it != mymap.end ())
      mymap.erase (it);

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find ('a')->second << '\n';
    std::cout << "c => " << mymap.find ('c')->second << '\n';
    std::cout << "d => " << mymap.find ('d')->second << '\n';
  }
  /* Testing count() */
  {
    NS::map<char, int> mymap;
    char c;

    mymap['a'] = 101;
    mymap['c'] = 202;
    mymap['f'] = 303;

    for (c = 'a'; c < 'h'; c++)
      {
        std::cout << c;
        if (mymap.count (c) > 0)
          std::cout << " is an element of mymap.\n";
        else
          std::cout << " is not an element of mymap.\n";
      }
  }
  /* Testing lower_bound() */
  {
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound ('b'); // itlow points to b
    itup = mymap.upper_bound ('d');  // itup points to e (not d!)

    mymap.erase (itlow, itup); // erases [itlow,itup)

    // print content:
    for (NS::map<char, int>::iterator it = mymap.begin (); it != mymap.end ();
         ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  /* Testing upper_bound() */
  {
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound ('b'); // itlow points to b
    itup = mymap.upper_bound ('d');  // itup points to e (not d!)

    mymap.erase (itlow, itup); // erases [itlow,itup)

    // print content:
    for (NS::map<char, int>::iterator it = mymap.begin (); it != mymap.end ();
         ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  /* Testing equal_range() */
  {
    NS::map<char, int> mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator>
        ret;
    ret = mymap.equal_range ('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
  }

  return (0);
}