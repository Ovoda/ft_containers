#include <vector.hpp>
#include <vector>
#include <iostream>


int main () {
    std::vector<int> _m(12, 12);
    std::cout << _m.capacity() << std::endl;
	_m.resize(1);
    std::cout << _m.capacity() << std::endl;
	_m.resize(2);
    std::cout << _m.capacity() << std::endl;
    _m.resize(3);
    std::cout << _m.capacity() << std::endl;
    return (0);
}