#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../HashTable.hpp"

int main(int argc, char const *argv[]) {
    std::ifstream file("../pdbs/cPDB.txt");
    int rank, yeses = 0, noes = 0;
    Cube *cube;

    if (!file.is_open()) {
        std::cout << "NO ABRIÓ EL ARCHIVO\n";
        return -1;
    }

    while (true) {

        if (file.eof()) {
            file.close();
            break;
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

    std::cout << yeses << " " << noes << " " << ((float) noes/(yeses+noes)) << "\n";
}


