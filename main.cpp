/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/03/28 11:48:11 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.hpp>
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

using namespace NAMESPACE;

template <class T>
void print(vector<vector<T> >& lst) {
  for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end();
       it++) {
    for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end();
         it2++)
      std::cout << *it2 << ' ';
    std::cout << '\n';
  }
}

template <class T>
void print(vector<T>& lst) {
  for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
    std::cout << *it << ' ';
  std::cout << '\n';
}

int main() {
  vector<int>::size_type sz;

  vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i = 0; i < 100; ++i) {
    foo.push_back(i);
    if (sz != foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);  // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i = 0; i < 100; ++i) {
    bar.push_back(i);
    if (sz != bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  try {
    bar.reserve(bar.max_size() * 2);
  } catch (std::exception& e) {
    std::cout << e.what();
  }
  return 0;
}
