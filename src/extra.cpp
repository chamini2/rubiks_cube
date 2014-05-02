#include "extra.hpp"

std::string int_to_string(int number) {
    std::stringstream ss;    // create a stringstream
    ss << number;            // add number to the stream
    return ss.str();         // return a string with the contents of the stream
}

std::string array_to_string(int *array, int size) {
    std::string str = "";

    for (int i = 0; i < size; ++i) {
        str += " " + std::to_string(array[i]);
    }

    return str;
}

void array_swap(int &a, int &b) {
    int temp;
    temp = b;
    b = a;
    a = temp;
}

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (int i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
}


void array_reverse(int* array, int size) {
    int temp;

    for (int i = 0; i < size/2; ++i) {
        temp = array[i];
        array[i] = array[size-i-1];
        array[size-i-1] = temp;
    }
}

void subarray_reverse(int *array, int i, int j) {
    int temp;
    while (i < j) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i += 1;
        j -= 1;
    }
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

/* Generates next permutation in lexicographical order */

void next_perm(int* array, int size) {
    for (int i = size-2; i >= 0; --i) {
        /* code */
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

int lex_perm(int* array, int n, int k) {
    int edge = k-1, j = k, i;

    while (j < n && array[edge] >= array[j]) {
        ++j;
    }

    if (j < n) {
        array_swap(array[edge], array[j]);
    }
    else {
        subarray_reverse(array, k, n-1);
        i = edge - 1;

        while (i > 0 && array[i] >= array[i + 1]) {
            --i;
        }

        if (i < 0) {
            return 0;
        }

        j = n - 1;

        while (j > i && array[i] >= array[j]) {
            --j;
        }

        array_swap(array[i], array[j]);
        subarray_reverse(array, i+1, n-1);
    }
    return 1;
}
