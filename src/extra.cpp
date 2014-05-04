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

int cubie_to_edge_orien(int cubie, int index) {
    int orien = cubie_to_orien(cubie);  // 0 || 1 || 2

    switch (index) {
        case 0:
        case 2:
        case 8:
        case 10:
            if (orien == 0) {
                return 0;
            } else if (orien == 1) {
                return 0;
            } else {
                return 1;
            }
        case 1:
        case 3:
        case 9:
        case 11:
            if (orien == 1) {
                return 0;
            } else if (orien == 0) {
                return 0;
            } else {
                return 1;
            }
        case 4:
        case 5:
        case 6:
        case 7:
            if (orien == 0) {
                return 0;
            } else if (orien == 2) {
                return 0;
            } else {
                return 1;
            }
        default:
            error("ahora lo ponemos", __LINE__, __FILE__);
            throw -1;
    }
}

int edge_orien_to_axis(int orien, int index, int pos) {

    switch (index) {
        case 0:
        case 2:
        case 8:
        case 10:
            switch (pos) {
                case 0:
                case 2:
                case 8:
                case 10:
                    if (orien == 0) {
                        return 0;
                    } else {
                        return 200;
                    }
                case 1:
                case 3:
                case 9:
                case 11:
                    if (orien == 0) {
                        return 100;
                    } else {
                        return 200;
                    }
                case 4:
                case 5:
                case 6:
                case 7:
                    if (orien == 0) {
                        return 0;
                    } else {
                        return 100;
                    }
                default:
                    error("MAL EN anillo 0 2 8 10", __LINE__, __FILE__);
                    throw -1;
            }

        case 1:
        case 3:
        case 9:
        case 11:
            switch (pos) {
                case 0:
                case 2:
                case 8:
                case 10:
                    if (orien == 0) {
                        return 0;
                    } else {
                        return 200;
                    }
                case 1:
                case 3:
                case 9:
                case 11:
                    if (orien == 0) {
                        return 100;
                    } else {
                        return 200;
                    }
                case 4:
                case 5:
                case 6:
                case 7:
                    if (orien == 0) {
                        return 100;
                    } else {
                        return 0;
                    }
                default:
                    error("MAL EN anillo 1 3 9 11", __LINE__, __FILE__);
                    throw -1;
            }

        case 4:
        case 5:
        case 6:
        case 7:
            switch (pos) {
                case 0:
                case 2:
                case 8:
                case 10:
                    if (orien == 0) {
                        return 0;
                    } else {
                        return 200;
                    }
                case 1:
                case 3:
                case 9:
                case 11:
                    if (orien == 0) {
                        return 200;
                    } else {
                        return 100;
                    }
                case 4:
                case 5:
                case 6:
                case 7:
                    if (orien == 0) {
                        return 0;
                    } else {
                        return 100;
                    }
                default:
                    error("MAL EN anillo 4 5 6 7", __LINE__, __FILE__);
                    throw -1;
            }

        default:
            error("ahora lo ponemos", __LINE__, __FILE__);
            throw -1;
    }
}

////////////////////////////////////////

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
