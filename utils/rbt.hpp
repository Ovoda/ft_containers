#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#include <iostream>
#include <node.hpp>
#include <string>

/// Red Black tree rules
// - Each node is either red or black.
// - All NIL nodes (figure 1) are considered black.
// - A red node does not have a red child.
// - Every path from a given node to any of its descendant NIL nodes goes
// through the same number of black nodes.

namespace ft {

template <class T>
class red_black_tree {
 public:
  red_black_tree() : _root(nullptr) {}

  ~red_black_tree() {}

  node<T> *root() const { return _root; }

  void insert(T content) { insert(_root, content, nullptr); }
  void insert(node<T> *root, T content, node<T> *parent) {
    if (_root == nullptr) {
      _root = new node<T>;
      _root->set_root(content);
    } else if (root->is_leaf() == true) {
      root->set_node(content, parent);
      check_node(root);
    } else if (content > root->get_content()) {
      insert(root->right(), content, root);
    } else {
      insert(root->left(), content, root);
    }
  }

  // uncle black (line)
  void fix_insertion3() {}

  void rotate(node<T> *current) {
    // save sibling
    node<T> *tmp = current->sibling();

    // reset grandparent
    current->grand_parent()->set_parent(current->parent());
    current->grand_parent()->unroot();
    current->grand_parent()->unleaf();
    current->grand_parent()->set_content(
        current->grand_parent()->get_content());
    current->grand_parent()->set_parent(current->grand_parent()->parent());
    _root = current->parent();

    // move saved sibling to grand parent on rotation side
    if (current->is_left_line()) {
      current->grand_parent()->set_left(tmp);
    } else if (current->is_right_line()) {
      current->grand_parent()->set_right(tmp);
    }

    // rotate grand parent to sibling and make parent root
    current->parent()->make_root();
    current->set_sibling(current->grand_parent());
  }

  // check last node
  void check_node(node<T> *last) {
    if (last == _root) {
      last->set_color(BLACK);
      return;
    } else if (last == _root->left() || last == _root->right()) {
      return;
    } else if (last->uncle() != _root && last->uncle()->get_color() == RED) {
      last->parent()->set_color(BLACK);
      last->uncle()->set_color(BLACK);
      last->grand_parent()->set_color(RED);
      check_node(last->grand_parent());
    }
    if (last->uncle() != _root && last->uncle()->get_color() == BLACK) {
      rotate(last);
    }
  }

  void print() { printFunc(_root, 0); }
  void printFunc(node<T> *root, int space) {
    if (root->is_leaf()) return;
    space += COUNT;
    // std::cout << *root << std::endl;
    printFunc(root->right(), space);
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) std::cout << " ";
    if (root->is_leaf()) {
      std::cout << "[]"
                << "\n";
    } else if (root->get_color() == RED) {
      std::cout << RED_CLR << root->get_content() << RESET << "\n";
    } else {
      std::cout << root->get_content() << "\n";
    }
    printFunc(root->left(), space);
    return;
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
    if (current->right()->is_leaf() == false) {
      traverse(current->right(), f);
    }
    (this->*f)(current);
    if (current->left()->is_leaf() == false) {
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
    if ((current->right()->is_leaf() == false &&
         current->get_color() + current->right()->get_color() > 1) ||
        (current->left()->is_leaf() == false &&
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