#if !defined(FT_NODE_HPP)
#define FT_NODE_HPP

#include <sstream>

#define RED 1
#define BLACK 0
#define RIGHT 1
#define LEFT 0

#define COUNT 10
#define RESET "\033[0m"
#define BLACK_CLR "\033[30m"          /* Black */
#define RED_CLR "\033[31m"            /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

#define SSTR(x)                                                              \
  static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)) \
      .str()

namespace ft {

template <class T>
class node {
 public:
  node()
      : _is_leaf(true),
        _color(BLACK),
        _is_root(false),
        _right_child(nullptr),
        _left_child(nullptr),
        _parent(nullptr) {}
  node(node<T> &src) { this = src; }
  ~node() {}

  node<T> *operator=(node<T> &rhs) {
    if (this != &rhs) {
      _color = rhs._color;
      _is_root = rhs._is_root;
      _parent = rhs._parent;
      _content = rhs._content;
      _is_leaf = rhs._is_leaf;
      _left_child = rhs._left_child;
      _right_child = rhs._right_child;
    }
    return (this);
  }

  int get_color() const { return _color; }
  T get_content() const { return _content; }
  void set_content(T content) { _content = content; }
  bool is_leaf() const { return (this == nullptr ? true : _is_leaf); }
  bool is_root() const { return (this == nullptr ? true : _is_root); }

  void make_leaf() { _is_leaf = true; }
  void unleaf() { _is_leaf = false; }

  void set_node(T content, node<T> *parent) {
    _is_leaf = false;
    _right_child = new node<T>;
    _left_child = new node<T>;
    _content = content;
    _parent = parent;
    _color = RED;
    _is_root = false;
  }
  void set_root(T content) {
    _is_leaf = false;
    _right_child = new node<T>;
    _left_child = new node<T>;
    _content = content;
    _parent = nullptr;
    _color = BLACK;
    _is_root = true;
  }
  void set_color(int color) { _color = color; }
  void make_root() { _is_root = true; }
  void unroot() { _is_root = false; }

  node<T> *right(void) const { return _right_child; }
  node<T> *left(void) const { return _left_child; }

  node<T> *set_right(node<T> *right) {
    _right_child = right;
    return _right_child;
  }

  node<T> *set_left(node<T> *left) {
    _left_child = left;
    return _left_child;
  }

  node<T> *parent(void) const { return _parent; }
  node<T> *sibling() {
    if (is_root()) {
      return nullptr;
    }
    return (parent()->right() == this ? parent()->left() : parent()->right());
  }
  node<T> *uncle() {
    return (parent() == nullptr || parent()->sibling() == nullptr
                ? nullptr
                : parent()->sibling());
  }
  node<T> *grand_parent() { return (parent()->parent()); }

  void set_parent(node<T> *parent) { _parent = parent; }
  void set_sibling(node<T> *sibling) {
    if (!is_root()) {
      parent()->right() == this ? parent()->set_left(sibling)
                                : parent()->set_right(sibling);
    }
  }

  void set_uncle(node<T> *uncle) { parent()->set_sibling(uncle); }

  bool is_line() { return (is_right_line() || is_left_line()); }
  int direction() const { return (this == parent()->right() ? RIGHT : LEFT); }
  bool is_left_line() {
    return (direction() == parent()->direction() &&
            parent()->direction() == LEFT);
  }
  bool is_right_line() {
    return (direction() == parent()->direction() &&
            parent()->direction() == RIGHT);
  }

 private:
  bool _is_leaf;
  int _color;
  T _content;
  node<T> *_right_child;
  node<T> *_left_child;
  node<T> *_parent;
  bool _is_root;
};

template <class T>
std::ostream &operator<<(std::ostream &o, node<T> &node) {
  o << "node " << RED_CLR << &node << RESET << "(" << node.get_content()
    << "), " << GREEN << " parent: "
    << (node.is_root() ? "R" : (SSTR(node.parent()->get_content()))) << RESET
    << "," << BLUE << " childs: "
    << (node.left()->is_leaf() == false ? SSTR(node.left()->get_content())
                                        : "leaf")
    << " | "
    << (node.right()->is_leaf() == false
            ? SSTR(node.right()->get_content()) + "\t"
            : "leaf")
    << RESET << CYAN << "\t sibling: "
    << (node.sibling()->is_leaf() == false
            ? SSTR(node.sibling()->get_content()) + "\t"
            : "leaf")
    << YELLOW << " uncle: "
    << (node.uncle()->is_leaf() == false
            ? SSTR(node.uncle()->get_content()) + "\t"
            : "leaf")
    << RESET;
  return o;
}

}  // namespace ft

#endif  // FT_NODE_HPP
