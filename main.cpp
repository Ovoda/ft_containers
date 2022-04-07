/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/04/07 23:25:56 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.hpp>
#include <map>

#ifndef STD
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class Key, class T>
void print(map<Key, T>& lst) {
  for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';
}

int main() {
  map<char, int> mymap;
  map<char, int>::iterator it;

  // insert some values:
  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;
  mymap['d'] = 40;
  mymap['e'] = 50;
  mymap['f'] = 60;

  it = mymap.find('b');
  std::cout << "found b\n";
  mymap.erase(it);  // erasing by iterator
  std::cout << "erase iterator to b\n";
  mymap.erase('c');  // erasing by key
  std::cout << "erase by key 'c'\n";
  it = mymap.find('e');
  std::cout << "erase by range 'e' to end\n";
  mymap.erase(it, mymap.end());  // erasing by range

  std::cout << " display :\n";
  // show content:
  for (it = mymap.begin(); it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
