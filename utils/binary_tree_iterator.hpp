#ifndef BINARY_TREE_ITERATOR_HPP
#define BINARY_TREE_ITERATOR_HPP

#include <iterator.hpp>

namespace ft {

template<class T>
class tree_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
    public:
    typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
    typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::reference node_reference;
    typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::pointer node_pointer;
    typedef typename iterator<ft::bidirectional_iterator_tag, T>::reference reference;
    typedef typename iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
    typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::difference_type difference_type;
    typedef typename iterator<ft::bidirectional_iterator_tag, node<T>>::iterator_category iterator_category;

    tree_iterator() : _ptr(nullptr) {}
    tree_iterator(const tree_iterator<T>& src) {
        *this = src;
    }
    tree_iterator(const node_pointer ptr) : _ptr(ptr){}
    ~tree_iterator() {}

    tree_iterator<T> &operator=(const tree_iterator<T> &src) {
        if (*this != src) {
            _ptr = src._ptr;
        }
        return (*this);
    }

    bool operator==(const tree_iterator<T> &b) {
        return (_ptr == b._ptr);
    }

    bool operator!=(const tree_iterator<T> &b) {
        return (!operator==(b));
    }

    reference operator*() const {
        return ;
    }

    pointer operator->() {
        return &(operator*());
    }

    private:
        node_pointer _ptr;
};

}
#endif