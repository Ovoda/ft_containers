#ifndef NODE_HPP
#define NODE_HPP
namespace ft {

template <class T>
struct Node {
  T data;
  Node *parent;
  Node *left;
  Node *right;
  int color;

  Node(T _data, Node *_parent, Node *_left, Node *_right, int _color)
      : data(_data),
        parent(_parent),
        left(_left),
        right(_right),
        color(_color) {}
};

template <class T>
Node<T> *minimum(Node<T> *node) {
  while (node && node->left != NULL) {
    node = node->left;
  }
  return node;
}

template <class T>
Node<T> *maximum(Node<T> *node) {
  while (node && node->right != NULL) {
    node = node->right;
  }
  return node;
}

}  // namespace ft
#endif