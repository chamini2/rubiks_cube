#include <iostream>
#include <fstream>
#include <string>
#include "../extra.hpp"
#include "../rank.hpp"

int main(int argc, char const *argv[]) {
    int n = 8, value;
    int *array;
    char cost[6], *temp;

    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cout << "NO ABRIÓ EL ARCHIVO\n";
        return -1;
    }

    while (true) {
        array = new int[n];
        for (int i = 0; i < n; ++i) {

            if (file.eof()) {
                file.close();
                return 0;
            }

            file >> array[i];
        }

        file.getline(cost, 5);
        temp = cost + 2;
        temp[strlen(temp) - 1] = '\0';

        value = rank(n, array, n, 3);
        std::cout << value << " " << temp << "\n";
    }

    delete[] array;

    return 0;
}
