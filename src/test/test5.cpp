#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../HashTable.hpp"

int main(int argc, char const *argv[]) {
    std::ifstream file("../pdbs/cPDB.txt");
    int rank, yeses = 0, noes = 0, first = -1, level;
    Cube *cube;
    char path[12];

    if (!file.is_open()) {
        std::cout << "NO ABRIÓ EL ARCHIVO\n";
        return -1;
    }

    while (true) {

        if (file.eof()) {
            file.close();
            break;
        }

        file >> level;
        file >> rank;
        file.getline(path,10);

        cube = new Cube(rank, 0 , ' ');
        if (cube->valid()) {
            yeses++;
        } else {
            noes++;
            if (first == -1) {
                first = rank;
                std::cout << "FIRST: " << first << " at " << level << " -> " << cube->corners_to_string() << " path:" << path << "\n";
            }
        }

        delete cube;
    }

    std::cout << yeses << " " << noes << " " << ((float) noes/(yeses+noes)) << "\n";
}


