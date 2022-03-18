#include "header.hpp"

int
main (void)
{
  /* Testing begin() */
  {
    NS::vector<int> myvector;
    for (int i = 1; i <= 5; i++)
      myvector.push_back (i);

    std::cout << "myvector contains:";
    for (NS::vector<int>::iterator it = myvector.begin ();
         it != myvector.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  /* Testing end() */
  {
    NS::vector<int> myvector;
    for (int i = 1; i <= 5; i++)
      myvector.push_back (i);

    std::cout << "myvector contains:";
    for (NS::vector<int>::iterator it = myvector.begin ();
         it != myvector.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  /* Testing rbegin() */
  {
    NS::vector<int> myvector (5); // 5 default-constructed ints

    int i = 0;

    NS::vector<int>::reverse_iterator rit = myvector.rbegin ();
    for (; rit != myvector.rend (); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (NS::vector<int>::iterator it = myvector.begin ();
         it != myvector.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  /* Testing rend() */
  {
    NS::vector<int> myvector (5); // 5 default-constructed ints

    NS::vector<int>::reverse_iterator rit = myvector.rbegin ();

    int i = 0;
    for (rit = myvector.rbegin (); rit != myvector.rend (); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (NS::vector<int>::iterator it = myvector.begin ();
         it != myvector.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  return (0);
}