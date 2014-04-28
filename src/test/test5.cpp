#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../HashTable.hpp"

int main(int argc, char const *argv[]) {
    std::ifstream file("cPDB.txt");
    int rank, yeses = 0, noes = 0;
    int *array;
    Cube *cube;

    if (!file.is_open()) {
        std::cout << "NO ABRIÓ EL ARCHIVO\n";
        return -1;
    }

    while (true) {

        if (file.eof()) {
            file.close();
            return 0;
        }

        file >> rank;
        file >> rank;
        cube = new Cube(rank, 0 , ' ');
        if (cube->valid()) {
            yeses++;
        } else {
            noes++;
        }
    }

    std::cout << yeses << " " << noes << " " << noes/(yeses+noes) << "\n";
}


