#include <math.h>
#include <iostream>
#include <fstream>
#include "../extra.hpp"
#include "../rank.hpp"

int main(int argc, char const *argv[]) {
    int n;
    int top;
    int *array, *nuevo;
    int variable;

    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cout << "NO ABRIO EL ARCHIVO\n";
        return -1;
    }

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

    array = new int[n];

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
        variable = rank(n, array, n, 3);
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
