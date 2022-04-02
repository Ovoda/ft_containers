#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <memory>

#define BLACK 0
#define RED 1

template <class T>
struct Node {
  T data;
  Node *right;
  Node *left;
  Node *parent;
  int color;
};

template <class T>
class red_black_tree {
 public:
  typedef Node<T> *node_ptr;
  typedef Node<T> node;
  typedef T data_type;

 private:
  node_ptr _root;
  node_ptr _TNULL;
  std::allocator<node> _alloc;

 public:
  red_black_tree() {
    node tmp;
    tmp.color = BLACK;
    tmp.left = NULL;
    tmp.right = NULL;
    _TNULL = _alloc.allocate(1);
    _alloc.construct(_TNULL, tmp);
    _root = _TNULL;
  }

  ~red_black_tree() {
    clear(_root);
    _alloc.destroy(_TNULL);
    _alloc.deallocate(_TNULL, 1);
  }

  void clear(node_ptr curr) {
    if (curr != NULL && curr != _TNULL) {
      clear(curr->left);
      clear(curr->right);
      _alloc.destroy(curr);
      _alloc.deallocate(curr, 1);
    }
  }

  void print2D() { print2DUtil(_root, 0); }

  void insert(data_type data) {
    node_ptr new_node;
    new_node = recursive_insert(data, _root, NULL);

    if (new_node->parent == NULL) {
      new_node->color = BLACK;
      return;
    }

    if (new_node->parent->parent == NULL) {
      return;
    }
    insertFix(new_node);
  }

  node_ptr find_node(node_ptr curr, data_type key) {
    if (curr->data == key || curr == _TNULL) {
      return (curr);
    }
    if (curr->data < key) {
      return (find_node(curr->right, key));
    }
    return (find_node(curr->left, key));
  }

  void delete_node(data_type key) { delete_node_helper(_root, key); }

 private:
  /* debug helper */

  void print2DUtil(node *curr, int space) {
    if (curr == _TNULL) return;
    space += 10;
    print2DUtil(curr->right, space);
    std::cout << std::endl;
    for (int i = 10; i < space; i++) std::cout << " ";
    if (curr->color == RED) {
      std::cout << "\033[1;31m " << curr->data << "\033[0m\n";
    } else {
      std::cout << curr->data << "\n";
    }
    print2DUtil(curr->left, space);
  }

  /* Node creation helpers*/

  node create_node(data_type data, node_ptr parent, node_ptr left,
                   node_ptr right, int color = RED) {
    node new_node;
    new_node.data = data;
    new_node.left = left;
    new_node.right = right;
    new_node.parent = parent;
    new_node.color = color;
    return (new_node);
  }

  node_ptr create_node_ptr(data_type data, node_ptr parent, node_ptr left,
                           node_ptr right, int color = RED) {
    node_ptr new_node;
    new_node = _alloc.allocate(1);
    _alloc.construct(new_node, create_node(data, parent, left, right, color));
    return (new_node);
  }

  /* Search helper*/

  node_ptr search_tree_helper(node_ptr curr, data_type key) {
    if (curr == _TNULL || key == curr->data) {
      return curr;
    }
    if (key < curr->data) {
      return (search_tree_helper(curr->left, key));
    }
    return (search_tree_helper(curr->right, key));
  }

  /* Insertion helpers */

  node_ptr recursive_insert(data_type data, node_ptr &curr, node_ptr parent) {
    if (curr == NULL || curr == _TNULL) {
      curr = create_node_ptr(data, parent, _TNULL, _TNULL);
      return curr;
    }
    if (data < curr->data) {
      return recursive_insert(data, curr->left, curr);
    } else if (data > curr->data) {
      return recursive_insert(data, curr->right, curr);
    }
    return NULL;
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

  void delete_node_helper(node_ptr curr, data_type key) {
    node_ptr node_to_delete = find_node(curr, key);

    if (node_to_delete == _TNULL) {
      std::cout << "Key not found" << std::endl;
      return;
    }

    node_ptr tmp_delete, node_anchor;
    int color_anchor = node_to_delete->color;
    if (node_to_delete->left == _TNULL) {
      node_anchor = node_to_delete->right;
      transplant(node_to_delete, node_to_delete->right);
    } else if (node_to_delete->right == _TNULL) {
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
    if (y->right != _TNULL) {
      y->right->parent = curr;
    }
    y->parent = curr->parent;
    if (curr->parent == NULL) {
      _root = y;
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
    if (y->left != _TNULL) {
      y->left->parent = curr;
    }
    y->parent = curr->parent;

    if (curr->parent == NULL) {
      _root = y;
    } else if (curr == curr->parent->left) {
      curr->parent->left = y;
    } else {
      curr->parent->right = y;
    }
    y->left = curr;
    curr->parent = y;
  }

  node_ptr minimum(node_ptr curr) {
    while (curr->left != _TNULL) {
      curr = curr->left;
    }
    return (curr);
  }
};

#endif