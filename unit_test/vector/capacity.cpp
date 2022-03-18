#include "header.hpp"

int
main (void)
{
  /* Testing size() */
  {
    NS::vector<int> myints;
    std::cout << "0. size: " << myints.size () << '\n';

    for (int i = 0; i < 10; i++)
      myints.push_back (i);
    std::cout << "1. size: " << myints.size () << '\n';

    myints.insert (myints.end (), 10, 100);
    std::cout << "2. size: " << myints.size () << '\n';

    myints.pop_back ();
    std::cout << "3. size: " << myints.size () << '\n';
  }

  /* Testing max_size() */
  {
    NS::vector<int> myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++)
      myvector.push_back (i);

    std::cout << "size: " << myvector.size () << "\n";
    std::cout << "capacity: " << myvector.capacity () << "\n";
    std::cout << "max_size: " << myvector.max_size () << "\n";
  }

  /* Testing resize() */
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

  /* Testing capacity() */
  {
    NS::vector<int> myvector;

    for (int i = 0; i < 100; i++)
      myvector.push_back (i);

    std::cout << "size: " << (int)myvector.size () << '\n';
    std::cout << "capacity: " << (int)myvector.capacity () << '\n';
    std::cout << "max_size: " << (int)myvector.max_size () << '\n';
  }

  /* Testing empty */
  {
    NS::vector<int> myvector;
    int sum (0);

    for (int i = 1; i <= 10; i++)
      myvector.push_back (i);

    while (!myvector.empty ())
      {
        sum += myvector.back ();
        myvector.pop_back ();
      }

    std::cout << "total: " << sum << '\n';
  }

  /* Testing reserve() */
  {
    NS::vector<int>::size_type sz;

    NS::vector<int> foo;
    sz = foo.capacity ();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i)
      {
        foo.push_back (i);
        if (sz != foo.capacity ())
          {
            sz = foo.capacity ();
            std::cout << "capacity changed: " << sz << '\n';
          }
      }

    NS::vector<int> bar;
    sz = bar.capacity ();
    bar.reserve (100); // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 100; ++i)
      {
        bar.push_back (i);
        if (sz != bar.capacity ())
          {
            sz = bar.capacity ();
            std::cout << "capacity changed: " << sz << '\n';
          }
      }
  }

  return (0);
}