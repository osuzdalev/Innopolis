#include <iostream>
#include "node.h"

template<typename T, typename I>
I find5(I first, I beyond, T val) {
    I p = first;
    while (p != beyond && *p != val) {
        p++;
    }
    return p;
};

int main() {
    NODE* list = new NODE(1);
    list->add(new NODE(2));
    list->add(new NODE(5));
    list->add(new NODE(3));
    list->add(new NODE(7));
    list->add(new NODE(4));

    std::cout << *(find5(NODE::iterator(list), NODE::iterator(nullptr), 7));
    return 0;
}