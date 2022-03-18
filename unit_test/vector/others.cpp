#include "header.hpp"

int
main (void)
{
  /* Testing constructor() */
  {
    NS::vector<int> first;
    NS::vector<int> second (4, 100);
    NS::vector<int> third (second.begin (), second.end ());
    NS::vector<int> fourth (third);

    int myints[] = { 16, 2, 77, 29 };
    NS::vector<int> fifth (myints, myints + sizeof (myints) / sizeof (int));

    std::cout << "The contents of fifth are:";
    for (NS::vector<int>::iterator it = fifth.begin (); it != fifth.end ();
         ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  /* Testing operator= */
  {
    NS::vector<int> foo (3, 0);
    NS::vector<int> bar (5, 0);

    bar = foo;
    foo = NS::vector<int> ();

    std::cout << "Size of foo: " << int (foo.size ()) << '\n';
    std::cout << "Size of bar: " << int (bar.size ()) << '\n';
  }

  /* Testing relationnal operators */
  {
    NS::vector<int> myvector;
    int *p;
    unsigned int i;

    p = myvector.get_allocator ().allocate (5);

    for (i = 0; i < 5; i++)
      myvector.get_allocator ().construct (&p[i], i);

    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++)
      std::cout << ' ' << p[i];
    std::cout << '\n';

    for (i = 0; i < 5; i++)
      myvector.get_allocator ().destroy (&p[i]);
    myvector.get_allocator ().deallocate (p, 5);
  }

  /* Testing get_allocator() */
  {
    NS::vector<int> myvector;
    int *p;
    unsigned int i;

    p = myvector.get_allocator ().allocate (5);

    for (i = 0; i < 5; i++)
      myvector.get_allocator ().construct (&p[i], i);

    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++)
      std::cout << ' ' << p[i];
    std::cout << '\n';

    for (i = 0; i < 5; i++)
      myvector.get_allocator ().destroy (&p[i]);
    myvector.get_allocator ().deallocate (p, 5);
  }

  /* Testing swap */
  {
    NS::vector<int> foo (3, 100);
    NS::vector<int> bar (5, 200);

    foo.swap (bar);

    std::cout << "foo contains:";
    for (NS::vector<int>::iterator it = foo.begin (); it != foo.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "bar contains:";
    for (NS::vector<int>::iterator it = bar.begin (); it != bar.end (); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  return (0);
}