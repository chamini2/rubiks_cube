#include <math.h>
#include <iostream>
#include <fstream>
#include "extra.hpp"

void array_swap(int &a, int &b);
void print_array(int *array, int n);
int rank(int n, int *array);
int* unrank(int n, int r);
int* inv_array(int* array, int size);

int main(int argc, char const *argv[]) {
    int n;
    int top;
    int *array, *nuevo;
    int variable;

    std::ifstream file("input.txt");

    if (argc == 3) {
        n = atoi(argv[1]);
        top = atoi(argv[2]);
    } else if (argc == 2) {
        n = atoi(argv[1]);
        top = factorial(n) - 1;
    } else {
        n = 8;
        top = factorial(n) - 1;
    }

    // std::cout << "n: (" << n << ") top: (" << top << ")\n";

    array = new int[8];
    // for (int i = 0; i < top; ++i)
    for (;;) {
        // std::cout << i << ": ";
        // array = unrank(n , i);

        for (int i = 0; i < n; ++i) {

            if (file.eof()) {
                file.close();
                return 0;
            }

            file >> array[i];
        }

        print_array(array, n);
        variable = rank(n, array);
        std::cout << " " << variable << "  ";

        nuevo = unrank(n, variable);
        print_array(nuevo, n);

        variable = 1;
        for (int i = 0; i < n; ++i)
        {
            if (array[i] != nuevo[i]) {
                variable = 0;
            }
        }

        if (variable) {
            std::cout << "iguales\n";
        } else {
            std::cout << "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
        }

        delete[] nuevo;
    }
    delete[] array;

    return 0;
}

void array_swap(int &a, int &b) {
    int temp;
    temp = b;
    b = a;
    a = temp;
}

void print_array(int *array, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
}

////////////////////////////////////////

int orien_to_axis(int orien) {
    return 32 * pow(2,orien);
}


void aux_unrank(int n, int r, int *array) {
    if (n > 0) {
        array_swap(array[n-1], array[r % n]);
        aux_unrank(n-1, floor(r/n), array);
    }
}

int *unrank(int size, int value) {
    int *array = new int[size];
    int d, r, power = pow(3, 8);

    r = value / power;
    d = value % power;

    // Identity array
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }

    aux_unrank(size, r, array);

    for (int i = size - 1; i >= 0; --i) {
        array[i] += orien_to_axis(d % 3);
        d = d / 3;
    }

    return array;
}

////////////////////////////////////////

int aux_rank(int n, int *array, int *inverse) {
    if (n == 1) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s + n * aux_rank(n-1, array, inverse);
}

int rank(int n, int *array) {
    int *inverse;
    int *aux = new int[n];
    int value, accum = 0;

    for (int i = 0; i < n; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, n);
    value = aux_rank(n, aux, inverse);

    delete[] inverse;
    delete[] aux;

    value *= pow(3,8);
    for (int i = 0; i < n; ++i) {
        accum = accum * 3 + cubie_to_orien(array[i]);
    }
    value += accum;

    return value;
}

////////////////////////////////////////

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (int i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
}
