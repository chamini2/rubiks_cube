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

////////////////////////////////////////

int cubie_to_pos(int cubie) {
    if (000 <= cubie && cubie < 100) {
        return cubie - 000;
    } else if (100 <= cubie && cubie < 200) {
        return cubie - 100;
    } else if (200 <= cubie) {
        return cubie - 200;
    }

    error("cubie_to_pos | cubie = " + int_to_string(cubie), __LINE__, __FILE__);
    throw -1;
}

int cubie_to_orien(int cubie) {
    if (000 <= cubie && cubie < 100) {
        // axis C
        return 0;
    } else if (100 <= cubie && cubie < 200) {
        // axis B
        return 1;
    } else if (200 <= cubie) {
        // axis A
        return 2;
    }

    error("cubie_to_orien | cubie = " + int_to_string(cubie), __LINE__, __FILE__);
    throw -1;
}

int orien_to_axis(int orien) {
    return 100*orien;
}

void print_array(int *array, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
}


// Node* make_root_node(Cube* cube) {
//     Node* node = new Node(cube, NULL, 0, 0);  // action y level 0 porque es root

//     return node;
// }

////////////////////////////////////////////////////////////////////////////////

void error(std::string message, int line, std::string file) {
    std::cout << message << " at line " << line << " in file '" << file << "'\n";
    exit(-1);
}