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

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (int i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
}

////////////////////////////////////////

int cubie_to_pos(int cubie) {
    return cubie % 100;
}

int cubie_to_orien(int cubie) {
    return cubie / 100;
}

int orien_to_axis(int orien) {
    return orien * 100;
}

int cubie_to_axis(int cubie) {
    return orien_to_axis(cubie_to_orien(cubie));
}

void print_array(int *array, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
}

////////////////////////////////////////////////////////////////////////////////

void error(std::string message, int line, std::string file) {
    std::cout << message << " at line " << line << " in file '" << file << "'\n";
    exit(-1);
}
