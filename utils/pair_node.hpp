#if !defined(FT_PAIR_NODE)
#define FT_PAIR_NODE

#include <iostream>
#include <std_lib.hpp>

namespace ft {

template <class T1, class T2>
class node {
 public:
  node(ft::pair<T1, T2> src) : _pair(src), _right(nullptr), _left(nullptr) {}
  node(T1 key, T2 value)
      : _pair(ft::pair<T1, T2>(key, value)), _right(nullptr), _left(nullptr) {}

  ~node(){};

  ft::pair<T1, T2> pair() { return _pair; }
  node<T1, T2> *right() { return _right; }
  node<T1, T2> *left() { return _left; }

  void insert(ft::pair<T1, T2> new_pair, node<T1, T2> *current) {
    if (current == nullptr) {
      current = new node<T1, T2>(new_pair);
      return;
    } else if (current->_left == nullptr && new_pair < current->pair()) {
      current->_left = new node<T1, T2>(new_pair);
      return;
    } else if (current->_right == nullptr && new_pair > current->pair()) {
      current->_right = new node<T1, T2>(new_pair);
      return;
    } else if (current->_left != nullptr && new_pair < current->pair()) {
      insert(new_pair, current->_left);
    } else if (current->_right != nullptr && new_pair > current->pair()) {
      insert(new_pair, current->_right);
    }
  }

  void search(T1 key) {
    if (current->_left == nullptr && new_pair < current->pair()) {
      current->_left = new node<T1, T2>(new_pair);
      return;
    } else if (current->_right == nullptr && new_pair > current->pair()) {
      current->_right = new node<T1, T2>(new_pair);
      return;
    } else if (current->_left != nullptr && new_pair < current->pair()) {
      insert(new_pair, current->_left);
    } else if (current->_right != nullptr && new_pair > current->pair()) {
      insert(new_pair, current->_right);
    }
  }

 private:
  ft::pair<T1, T2> _pair;
  node *_right;
  node *_left;
};

template <class T1, class T2>
std::ostream &operator<<(std::ostream &o, ft::node<T1, T2> current) {
  o << current.pair().first << " :: " << current.pair().second;
  return (o);
}

}  // namespace ft

#endif  // FT_PAIR_NODE
