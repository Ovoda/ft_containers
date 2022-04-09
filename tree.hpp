#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <tree_iterator.hpp>
#include <typeinfo>
#include <utils.hpp>

namespace ft {

template <class T, class Compare = less<T> >
class red_black_tree {
 public:
  typedef Node<T> *node_ptr;
  typedef Node<T> node;
  typedef tree_iterator<T> iterator;
  typedef const_tree_iterator<T> const_iterator;
  typedef T data_type;
  typedef Compare key_compare;

 public:
  red_black_tree(const key_compare &comp = key_compare())
      : _root(NULL), _size(0), _comp(comp) {
    _end = _malloc_node();
    _end->parent = _root;
    _end->right = _root;
    _end->left = _root;
  }

  ~red_black_tree() {
    clear();
    _free_node(_end);
  }

  red_black_tree &operator=(const red_black_tree &src) {
    if (this != &src) {
      _alloc = src._alloc;
      _comp = src._comp;
      clear();
      const_iterator it = src.begin();
      for (; it != src.end(); it++) {
        insert(*it);
      }
    }
    return *this;
  }

  bool empty() const { return (_size == 0); }
  size_t size() const { return _size; }
  size_t max_size() const { return _alloc.max_size(); }

  iterator begin() {
    if (!_root) {
      return end();
    }
    return iterator(minimum(_root));
  }
  const_iterator begin() const {
    if (!_root) {
      return end();
    }
    return const_iterator(minimum(_root));
  }

  iterator end() { return iterator(_end); }
  const_iterator end() const { return const_iterator(_end); }

  node_ptr searchTree(data_type k) const {
    node_ptr found = searchTreeHelper(this->_root, k);
    if (!found) {
      return _end;
    }
    return found;
  }

  node_ptr count(data_type k) const {
    node_ptr found = searchTreeHelper(_root, k);
    if (!found) {
      return NULL;
    }
    return found;
  }

  void swap(red_black_tree &x) {
    node_ptr tmp = _root;
    _root = x._root;
    x._root = tmp;

    size_t size_tmp = _size;
    _size = x._size;
    x._size = size_tmp;

    tmp = _end;
    _end = x._end;
    x._end = tmp;
  }

  void leftRotate(node_ptr x) {
    node_ptr y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _end) {
      _root = y;
      _root->parent = _end;
      _end->right = _root;
      _end->left = _root;
      _end->parent = _root;

    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(node_ptr x) {
    node_ptr y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == _end) {
      _root = y;
      _root->parent = _end;
      _end->right = _root;
      _end->left = _root;
      _end->parent = _root;

    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  pair<iterator, bool> insert(const data_type &key) {
    node_ptr node = _malloc_node(key, NULL, NULL, NULL, 1);

    node_ptr y = NULL;
    node_ptr x = _root;

    while (x != NULL) {
      y = x;
      if (_comp(node->data, x->data)) {
        x = x->left;
      } else if (_comp(x->data, node->data)) {
        x = x->right;
      } else {
        _free_node(node);
        return (pair<iterator, bool>(iterator(x), false));
      }
    }

    _size++;
    node->parent = y;
    if (y == NULL) {
      _root = node;
      _root->parent = _end;
      _end->right = _root;
      _end->left = _root;
      _end->parent = _root;
    } else if (_comp(node->data, y->data)) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == _end) {
      node->color = 0;
      return (pair<iterator, bool>(iterator(node), true));
    }

    if (node->parent->parent == _end) {
      return (pair<iterator, bool>(iterator(node), true));
    }

    insertFix(node);
    return (pair<iterator, bool>(iterator(node), true));
  }

  node_ptr get_root() { return this->_root; }

  bool deleteNode(data_type data) { return (deleteNodeHelper(_root, data)); }

  void print_helper(node_ptr curr, int space) {
    if (curr == NULL) return;

    space += 10;

    print_helper(curr->right, space);

    std::cout << std::endl;
    for (int i = 10; i < space; i++) std::cout << " ";
    if (curr->color) {
      std::cout << "\033[1;31m";
    }
    std::cout << curr->data << "\033[0m\n" << std::endl;
    print_helper(curr->left, space);
  }

  void print() { print_helper(_root, 0); }
  void clear() { clear_helper(_root); }

 private:
  node_ptr _root;
  node_ptr _end;
  size_t _size;
  std::allocator<Node<T> > _alloc;
  key_compare _comp;

  void _free_node(node_ptr curr) {
    _alloc.destroy(curr);
    _alloc.deallocate(curr, 1);
    curr = NULL;
  }

  node_ptr _malloc_node(data_type data = data_type(), node_ptr parent = NULL,
                        node_ptr left = NULL, node_ptr right = NULL,
                        int color = 0) {
    node_ptr new_node;
    new_node = _alloc.allocate(1);
    _alloc.construct(new_node, node(data, parent, left, right, color));
    return new_node;
  }

  node_ptr searchTreeHelper(node_ptr node, data_type key) const {
    if (node == NULL) {
      return node;
    }
    if (_comp(key, node->data)) {
      return searchTreeHelper(node->left, key);
    } else if (_comp(node->data, key)) {
      return searchTreeHelper(node->right, key);
    }
    return node;
  }

  void deleteFix(node_ptr x) {
    node_ptr s;
    while (x != _root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if ((s->left->color == 0 || !s->left) &&
            (s->right->color == 0 || !s->right)) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = _root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (!s->right || s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = _root;
        }
      }
    }
    if (x) x->color = 0;
    _alloc.destroy(_end);
    data_type data = (_root ? maximum(_root)->data : data_type());
    _alloc.construct(_end, node(data, _root, _root, _root, 0));
  }

  void replace(node_ptr first, node_ptr second) {
    if (first->parent == _end) {
      _root = second;
      if (_root) {
        _root->parent = _end;
        _end->right = _root;
        _end->left = _root;
        _end->parent = _root;
      }
    } else if (first == first->parent->left) {
      first->parent->left = second;
    } else {
      first->parent->right = second;
    }
    if (second) second->parent = first->parent;
  }

  bool deleteNodeHelper(node_ptr node, data_type key) {
    node_ptr z = searchTreeHelper(node, key);
    node_ptr x, y;

    if (z == _end || z == NULL) {
      return false;
    }

    _size--;
    y = z;
    int y_original_color = y->color;
    if (z->left == NULL) {
      x = z->right;
      replace(z, z->right);
    } else if (z->right == NULL) {
      x = z->left;
      replace(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;

      if (y->parent == z) {
        if (x) x->parent = y;
      } else {
        replace(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      replace(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    _free_node(z);
    if (x && y_original_color == 0) {
      deleteFix(x);
    }
    return true;
  }

  void insertFix(node_ptr k) {
    node_ptr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u && u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u && u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == _root) {
        break;
      }
    }
    _root->color = 0;
    _alloc.destroy(_end);
    _alloc.construct(_end, node(maximum(_root)->data, _root, _root, _root, 0));
  }

  void clear_helper(node_ptr &curr) {
    if (!curr) return;

    clear_helper(curr->left);
    clear_helper(curr->right);
    _free_node(curr);
    _size--;
    curr = NULL;
  }
};
}  // namespace ft

#endif