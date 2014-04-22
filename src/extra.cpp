#include <cstdlib>
#include "extra.hpp"

std::string int_to_string(int number) {
    std::stringstream ss;    // create a stringstream
    ss << number;            // add number to the stream
    return ss.str();         // return a string with the contents of the stream
}

int aux_factorial(int accum, int n) {
    if (n < 0) throw -1;
    if (n == 0) return 1;
    if (n == 1) return accum;
    return aux_factorial(accum * n, n-1);
}

int factorial(int n) {
    return aux_factorial(1,n);
}


// Node* make_root_node(Cube* cube) {
//     Node* node = new Node(cube, NULL, 0, 0);  // action y level 0 porque es root

//     return node;
// }
