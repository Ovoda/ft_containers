#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#include <iostream>
#include <node.hpp>
#include <string>

namespace ft {

template <class T>
class red_black_tree {
 public:
  red_black_tree() {
    _root = new node<T>;
    _root->become_root();
    _root->set_color(BLACK);
  }
  ~red_black_tree() {}

  node<T> *root() const { return _root; }

  void insert(T content) { insert(_root, content, nullptr); }
  void insert(node<T> *root, T content, node<T> *parent) {
    if (root->is_filled() == false) {
      root->set_node(content, parent);
      root->fill();
    } else if (root->get_content() > content) {
      insert(root->right(), content, root);
    } else {
      insert(root->left(), content, root);
    }
  }

  void print() { printFunc(_root, 0); }
  void printFunc(node<T> *root, int space) {
    if (root == NULL) return;
    space += COUNT;
    printFunc(root->right(), space);
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) std::cout << " ";
    if (!root->is_filled()) {
      std::cout << "[]"
                << "\n";
    } else if (root->get_color() == RED) {
      std::cout << RED_CLR << root->get_content() << RESET << "\n";
    } else {
      std::cout << root->get_content() << "\n";
    }

    printFunc(root->left(), space);
  }
  int print_node(node<T> *current) {
    std::cout << *current << std::endl;
    return 0;
  }

  bool check_tree() {
    return (check_root_color() &&
            traverse(_root, &red_black_tree::check_red_instances));
  }

  bool traverse(node<T> *current, int (red_black_tree::*f)(node<T> *current)) {
    if (current->right()->is_filled() == true) {
      traverse(current->right(), f);
    }
    (this->*f)(current);
    if (current->left()->is_filled() == true) {
      traverse(current->left(), f);
    }
    return true;
  }

 private:
  bool check_root_color() {
    if (_root->get_color() != BLACK) {
      std::cout << "Root isn't BLACK" << std::endl;
      return (false);
    }
    return (true);
  }

  int check_red_instances(node<T> *current) {
    if ((current->right()->is_filled() &&
         current->get_color() + current->right()->get_color() > 1) ||
        (current->left()->is_filled() &&
         current->get_color() + current->left()->get_color() > 1)) {
      std::cout << "double red on " << current->get_content() << std::endl;
      return (0);
    }
    return (1);
  }

  node<T> *_root;
};
}  // namespace ft

#endif