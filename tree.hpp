#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <memory>
#include <utils.hpp>

#define BLACK 0
#define RED 1

template <class T>
class Node {
 public:
  T data;
  Node *right;
  Node *left;
  Node *parent;
  int color;
  bool is_leaf;

  Node(T _data, Node *_right, Node *_left, Node *_parent, int _color,
       bool _is_leaf)
      : data(_data),
        right(_right),
        left(_left),
        parent(_parent),
        color(_color),
        is_leaf(_is_leaf) {}
  Node() {}
  ~Node() {}
};

template <class T>
Node<T> *minimum(Node<T> *curr) {
  while (curr->left != NULL && curr->left->is_leaf == false) {
    curr = curr->left;
  }
  return (curr);
}

template <class T>
Node<T> *maximum(Node<T> *curr) {
  while (curr->right->is_leaf == false) {
    curr = curr->right;
  }
  return (curr);
}

template <class T>
class red_black_tree {
 public:
  typedef Node<T> *node_ptr;
  typedef Node<T> node;
  typedef T data_type;
  int _size;
  node_ptr _leaf;

 private:
  node_ptr _root;
  node_ptr _end;
  std::allocator<node> _alloc;

 public:
  red_black_tree() {
    _size = 0;
    _leaf = create_leaf();
    _root = _leaf;
    _end = create_node_ptr(data_type(), _root, _root, _root, BLACK, true);
    _root->parent = _end;
  }

  ~red_black_tree() {
    clear(_root);
    if (_leaf) {
      _alloc.destroy(_leaf);
      _alloc.deallocate(_leaf, 1);
    }

    _alloc.destroy(_end);
    _alloc.deallocate(_end, 1);
  }

  size_t max_size() const { return _alloc.max_size(); }

  bool is_empty() const { return (_size == 0); }

  node_ptr begin() const {
    if (!_root || _size == 0) {
      return end();
    }
    return minimum(_root);
  }

  node_ptr end() const { return _end; }

  void clear(node_ptr curr) {
    if (curr == NULL || curr->is_leaf || _size <= 0) {
      return;
    }

    clear(curr->left);
    clear(curr->right);
    _alloc.destroy(curr);
    _alloc.deallocate(curr, 1);

    _size--;

    curr = NULL;
  }

  void clear() {
    clear(_root);
    _root = _leaf;
  }

  void print2D() { print2DUtil(_root, 0); }

  ft::pair<node_ptr, bool> insert(data_type data) {
    node_ptr new_node;
    new_node = recursive_insert(data, _root, _end);

    if (new_node == NULL) {
      return (ft::pair<node_ptr, bool>(new_node, false));
    }

    _size++;
    if (new_node->parent == _end) {
      new_node->color = BLACK;
      return (ft::pair<node_ptr, bool>(new_node, true));
    }

    if (new_node->parent->parent == _end) {
      return (ft::pair<node_ptr, bool>(new_node, true));
    }
    insertFix(new_node);
    reset_root();
    return (ft::pair<node_ptr, bool>(new_node, true));
  }

  node_ptr find_node(node_ptr curr, typename data_type::first_type key) const {
    if (curr->data.first == key || curr->is_leaf) {
      return (curr);
    }
    if (key < curr->data.first) {
      return (find_node(curr->left, key));
    } else if ((key > curr->data.first)) {
      return (find_node(curr->right, key));
    }
    return NULL;
  }

  node_ptr find_node(typename data_type::first_type key) const {
    return (find_node(_root, key));
  }
  void delete_node(typename data_type::first_type key) {
    delete_node_helper(_root, key);
  }

  void swap(red_black_tree &x) {
    size_t tmp_size = _size;
    _size = x._size;
    x._size = tmp_size;

    node_ptr tmp = _root;
    _root = x._root;
    x._root = tmp;

    tmp = _end;
    _end = x._end;
    x._end = tmp;

    if (_root) _root->parent = _end;
    if (x._root) x._root->parent = x._end;
  }

 private:
  /* debug helper */

  void print2DUtil(node *curr, int space) {
    if (curr->is_leaf) return;
    space += 10;
    print2DUtil(curr->right, space);
    std::cout << std::endl;
    for (int i = 10; i < space; i++) std::cout << " ";
    if (curr->color == RED) {
      std::cout << "\033[1;31m " << curr->data.first << "\033[0m\n";
    } else {
      std::cout << curr->data.first << "\n";
    }
    print2DUtil(curr->left, space);
  }

  /* Node creation helpers*/

  node create_node(data_type data, node_ptr parent, node_ptr left,
                   node_ptr right, int color, bool is_leaf) {
    node new_node(data, right, left, parent, color, is_leaf);
    return (new_node);
  }

  node_ptr create_leaf(data_type data = data_type(), node_ptr parent = NULL,
                       node_ptr left = NULL, node_ptr right = NULL,
                       int color = BLACK, bool is_leaf = true) {
    node_ptr new_node = _alloc.allocate(1);
    _alloc.construct(new_node,
                     create_node(data, parent, left, right, color, is_leaf));
    return (new_node);
  }

  node_ptr create_node_ptr(data_type data, node_ptr parent, node_ptr left,
                           node_ptr right, int color = RED,
                           bool is_leaf = false) {
    node_ptr new_node;
    new_node = _alloc.allocate(1);
    _alloc.construct(new_node,
                     create_node(data, parent, left, right, color, is_leaf));
    return (new_node);
  }

  /* Insertion helpers */

  node_ptr recursive_insert(data_type data, node_ptr &curr, node_ptr parent) {
    if (curr == NULL || curr->is_leaf) {
      curr = create_node_ptr(data, parent, _leaf, _leaf);
      return curr;
    }
    if (data.first < curr->data.first) {
      return recursive_insert(data, curr->left, curr);
    } else if (data.first > curr->data.first) {
      return recursive_insert(data, curr->right, curr);
    }
    return curr;
  }

  void insertFix(node_ptr curr) {
    node_ptr uncle;
    while (curr->parent->color == RED) {
      if (curr->parent == curr->parent->parent->right) {
        uncle = curr->parent->parent->left;
        if (uncle->color == RED) {
          uncle->color = BLACK;
          curr->parent->color = BLACK;
          curr->parent->parent->color = RED;
          curr = curr->parent->parent;
        } else {
          if (curr == curr->parent->left) {
            curr = curr->parent;
            right_rotate(curr);
          }
          curr->parent->color = BLACK;
          curr->parent->parent->color = RED;
          left_rotate(curr->parent->parent);
        }
      } else {
        uncle = curr->parent->parent->right;

        if (uncle->color == RED) {
          uncle->color = BLACK;
          curr->parent->color = BLACK;
          curr->parent->parent->color = RED;
          curr = curr->parent->parent;
        } else {
          if (curr == curr->parent->right) {
            curr = curr->parent;
            left_rotate(curr);
          }
          curr->parent->color = BLACK;
          curr->parent->parent->color = RED;
          right_rotate(curr->parent->parent);
        }
      }
      if (curr == _root) {
        break;
      }
    }
    _root->color = BLACK;
  }

  /* Deletion helpers */

  void delete_node_helper(node_ptr curr, typename data_type::first_type key) {
    node_ptr node_to_delete = find_node(curr, key);

    if (node_to_delete->is_leaf) {
      std::cout << "Key not found" << std::endl;
      return;
    }

    node_ptr tmp_delete, node_anchor;
    int color_anchor = node_to_delete->color;
    if (node_to_delete->left->is_leaf) {
      node_anchor = node_to_delete->right;
      transplant(node_to_delete, node_to_delete->right);
    } else if (node_to_delete->right->is_leaf) {
      node_anchor = node_to_delete->left;
      transplant(node_to_delete, node_to_delete->left);
    } else {
      tmp_delete = minimum(node_to_delete->right);
      color_anchor = tmp_delete->color;
      node_anchor = tmp_delete->right;
      if (tmp_delete->parent == node_to_delete) {
        node_anchor->parent = tmp_delete;
      } else {
        transplant(tmp_delete, tmp_delete->right);
        tmp_delete->right = node_to_delete->right;
        tmp_delete->right->parent = tmp_delete;
      }
      transplant(node_to_delete, tmp_delete);
      tmp_delete->left = node_to_delete->left;
      tmp_delete->left->parent = tmp_delete;
      tmp_delete->color = node_to_delete->color;
    }
    delete node_to_delete;
    if (color_anchor == BLACK) {
      delete_fix(node_anchor);
    }
    _size--;
    reset_root();
  }

  void delete_fix(node_ptr curr) {
    node_ptr sibling;
    while (curr != _root && curr->color == BLACK) {
      if (curr == curr->parent->left) {
        sibling = curr->parent->right;
        if (sibling->color == RED) {
          sibling->color = BLACK;
          curr->parent->color = RED;
          left_rotate(curr->parent);
          sibling = curr->parent->right;
        }
        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
          sibling->color = RED;
          curr = curr->parent;
        } else {
          if (sibling->right->color == BLACK) {
            sibling->left->color = BLACK;
            sibling->color = RED;
            right_rotate(sibling);
            sibling = curr->parent->right;
          }
          sibling->color = curr->parent->color;
          curr->parent->color = BLACK;
          sibling->right->color = BLACK;
          left_rotate(curr->parent);
          curr = _root;
        }
      } else {
        sibling = curr->parent->left;
        if (sibling->color == RED) {
          sibling->color = BLACK;
          curr->parent->color = RED;
          right_rotate(curr->parent);
          sibling = curr->parent->left;
        }
        if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
          sibling->color = RED;
          curr = curr->parent;
        } else {
          if (sibling->left->color == BLACK) {
            sibling->right->color = BLACK;
            sibling->color = RED;
            left_rotate(sibling);
            sibling = curr->parent->left;
          }
          sibling->color = curr->parent->color;
          curr->parent->color = BLACK;
          sibling->left->color = BLACK;
          right_rotate(curr);
          curr = _root;
        }
      }
    }
    curr->color = BLACK;
  }

  /* Rotation Helpers*/

  void transplant(node_ptr first, node_ptr second) {
    if (first->parent == NULL) {
      _root = second;
      _root->parent = _end;
    } else if (first == first->parent->left) {
      first->parent->left = second;
    } else {
      first->parent->right = second;
    }
    second->parent = first->parent;
  }

  void right_rotate(node_ptr curr) {
    node_ptr y = curr->left;
    curr->left = y->right;
    if (!y->right->is_leaf) {
      y->right->parent = curr;
    }
    y->parent = curr->parent;
    if (curr->parent == _end) {
      _root = y;
      _root->parent = _end;
    } else if (curr == curr->parent->right) {
      curr->parent->right = y;
    } else {
      curr->parent->left = y;
    }
    y->right = curr;
    curr->parent = y;
  }

  void left_rotate(node_ptr curr) {
    node_ptr y = curr->right;
    curr->right = y->left;
    if (!y->left->is_leaf) {
      y->left->parent = curr;
    }
    y->parent = curr->parent;

    if (curr->parent == _end) {
      _root = y;
      _root->parent = _end;
    } else if (curr == curr->parent->left) {
      curr->parent->left = y;
    } else {
      curr->parent->right = y;
    }
    y->left = curr;
    curr->parent = y;
  }

  void reset_root() {
    _alloc.destroy(_end);
    _alloc.deallocate(_end, 1);
    _end =
        create_node_ptr(maximum(_root)->data, _root, _root, _root, BLACK, true);
    _root->parent = _end;
  }
};

#endif