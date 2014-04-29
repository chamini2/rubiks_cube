#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
// #include "../HashTable.hpp"

int tp(int n, int *P) {
    int p = 0;
    char v[n];
    int j=n;

    for(int i = 0; i < n; ++i) {
        v[i] = 0;
    }

    while(j--) {
        if(v[j]) {
            ++p;
        } else {
            int x = j;
            do {
                x = P[x];
                v[x] = 1;
            } while (x!=j);
        }
    }

    return p&1;
}

int main(int argc, char const *argv[]) {
    int array[] = {1 ,3 ,4 ,2 ,5 ,8 ,7 ,12 ,6 ,9 ,10 ,0 ,11 ,17 ,15 ,18 ,13 ,14 ,19 ,16 };
    int array2[] = {0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19};

    std::cout << tp(20, array) << "\n";
    std::cout << tp(20, array2) << "\n";
}


