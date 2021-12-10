#if !defined(FT_NODE_HPP)
#define FT_NODE_HPP

#include <sstream>

#define RED 1
#define BLACK 0
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
      : _is_filled(false),
        _color(RED),
        _is_root(false),
        _right_child(nullptr),
        _left_child(nullptr),
        _parent(nullptr) {}
  node(T i, node<T> *parent)
      : _is_filled(false),
        _is_root(false),
        _color(RED),
        _content(i),
        _right_child(nullptr),
        _left_child(nullptr) {}
  ~node() {}

  int get_color() const { return _color; }
  T get_content() const { return _content; }
  bool is_filled() const { return _is_filled; }
  bool is_root() const { return _is_root; }

  void set_node(T content, node<T> *parent) {
    fill();
    _right_child = new node<T>;
    _left_child = new node<T>;
    _content = content;
    _parent = parent;
  }
  void set_color(int color) { _color = color; }
  void fill() { _is_filled = true; }
  void become_root() { _is_root = true; }

  node<T> *right(void) const { return _right_child; }
  node<T> *left(void) const { return _left_child; }
  node<T> *parent(void) const { return _parent; }
  node<T> *sibling() const {
    if (is_root()) {
      return this;
    }

    if (parent()->right() == this) {
      return (parent()->left());
    }
    return (parent()->right());
  }
  node<T> *uncle() const {
    if (is_root()) return this;
    return (parent()->sibling());
  }

 private:
  bool _is_filled;
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
    << (node.left()->is_filled() ? SSTR(node.left()->get_content()) : "leave")
    << " | "
    << (node.right()->is_filled() ? SSTR(node.right()->get_content()) + "\t"
                                  : "leave")
    << RESET << CYAN << "\t sibling: "
    << (node.sibling()->is_filled() ? SSTR(node.sibling()->get_content()) + "\t"
                                    : "leave")
    << YELLOW << " uncle: "
    << (node.uncle()->is_filled() ? SSTR(node.uncle()->get_content()) + "\t"
                                  : "leave")
    << RESET;
  return o;
}

}  // namespace ft

#endif  // FT_NODE_HPP
