#include <cstdio>
#include <iomanip>
#include <map.hpp>
#include <map>
#include <string>
/*
** This is a minimal set of ANSI/VT100 color codes
*/
#define _END "\x1b[0m"
#define _BOLD "\x1b[1m"
#define _UNDER "\x1b[4m"
#define _REV "\x1b[7m"

/*
** Colors
*/
#define _GREY "\x1b[30m"
#define _RED "\x1b[31m"
#define _GREEN "\x1b[32m"
#define _YELLOW "\x1b[33m"
#define _BLUE "\x1b[34m"
#define _PURPLE "\x1b[35m"
#define _CYAN "\x1b[36m"
#define _WHITE "\x1b[37m"

/*
** Inverted, i.e. colored backgrounds
*/
#define _IGREY "\x1b[40m"
#define _IRED "\x1b[41m"
#define _IGREEN "\x1b[42m"
#define _IYELLOW "\x1b[43m"
#define _IBLUE "\x1b[44m"
#define _IPURPLE "\x1b[45m"
#define _ICYAN "\x1b[46m"
#define _IWHITE "\x1b[47m"

#ifndef STD
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class Key, class T>
void print(map<Key, T>& lst) {
  std::cout << "printing a map : \n";
  for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';
}

int main() {
  map<std::string, int> mymap;

  mymap.insert(pair<std::string, int>("1", 1));
  mymap.insert(pair<std::string, int>("xD", 123));
  mymap.insert(pair<std::string, int>("uch", 23));

  map<std::string, int> map2;

  swap(mymap, map2);
  mymap = map2;

  return 0;
}
