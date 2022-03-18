#include "header.hpp"

int
main (void)
{
  /* Testing assign() */
  {
    NS::vector<int> first;
    NS::vector<int> second;
    NS::vector<int> third;

    first.assign (7, 100);

    NS::vector<int>::iterator it;
    it = first.begin () + 1;

    second.assign (it, first.end () - 1);

    int myints[] = { 1776, 7, 4 };
    third.assign (myints, myints + 3);

    std::cout << "Size of first: " << int (first.size ()) << '\n';
    std::cout << "Size of second: " << int (second.size ()) << '\n';
    std::cout << "Size of third: " << int (third.size ()) << '\n';
  }

  /* testing resize() */
  {
    NS::vector<int> myvector;

    for (int i = 1; i < 10; i++)
      myvector.push_back (i);

    myvector.resize (5);
    myvector.resize (8, 100);
    myvector.resize (12);

    std::cout << "myvector contains:";
    for (size_t i = 0; i < myvector.size (); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  /* Testing pop_back() */
  {
    NS::vector<int> myvector;
    int sum (0);
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    while (!myvector.empty ())
      {
        sum += myvector.back ();
        myvector.pop_back ();
      }

    std::cout << "The elements of myvector add up to " << sum << '\n';
  }

  /* Testing insert*/
  {
    NS::vector<int> myvector (3, 100);
    NS::vector<int>::iterator it;

    it = myvector.begin ();
    it = myvector.insert (it, 200);

    myvector.insert (it, 2, 300);

    it = myvector.begin ();

    NS::vector<int> anothervector (2, 400);
    myvector.insert (it + 2, anothervector.begin (), anothervector.end ());

    int myarray[] = { 501, 502, 503 };
    myvector.insert (myvector.begin (), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin (); it < myvector.end (); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  /* Testing erase() */
  {
    NS::vector<int> myvector;

    for (int i = 1; i <= 10; i++)
      myvector.push_back (i);
    myvector.erase (myvector.begin () + 5);
    myvector.erase (myvector.begin (), myvector.begin () + 3);
    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size (); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  /* Testing swap() */
  {
    NS::vector<int> foo (3, 100);
    NS::vector<int> bar (5, 200);

    foo.swap (bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size (); i++)
      std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size (); i++)
      std::cout << ' ' << bar[i];
    std::cout << '\n';
  }

  /* Testing clear() */
  {
    NS::vector<int> myvector;
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size (); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';

    myvector.clear ();
    myvector.push_back (1101);
    myvector.push_back (2202);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size (); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  return 0;
}