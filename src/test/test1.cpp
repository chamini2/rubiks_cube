#include <math.h>
#include <iostream>
#include "../extra.hpp"
#include "../rank.hpp"

////////////////////////////////////////////////////////////////////////////////

int aux_rank2(int n, int edge, int *array, int *inverse) {
    if (n == edge) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s + n * aux_rank2(n-1, edge, array, inverse);
}


/*
 * Given a array with a k-permutation of n elements, returns an unique integer
 * for such permutation.
 *
 * For complete permutations, k must be equal to n.
 *
 * For k-permutations, it is assumed that the array contains the k elements in
 * last k positions of the array and the contents of the rest are irrelevant.
 */

int rank2(int *array, int size, int k) {
    int *inverse;
    int *aux = new int[size];
    int value;
    int edge = size-k-1;
    // int orientation = 0;

    for (int i = 0; i < size; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, size);
    value = aux_rank2(size, edge, aux, inverse);

    delete[] inverse;
    delete[] aux;

    // value *= pow(3,8);
    // for (int i = 0; i < size; ++i) {
    //     orientation = orientation * 3 + cubie_to_orien(array[i]);
    // }
    // value += orientation;

    // delete[] array;

    return value;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
    int size = 4;
    int k = 4;
    int *array = new int[size];
    int *rankeable = new int[size];

    // for (int i = 2; i < size; ++i) {
    //     array[i] = i;
    // }

    // for (int i = 0; i < 2; ++i) {
    //     array[i] = 0;
    // }

    for (int i = 0; i < size; ++i) {
        array[i] = i;
        rankeable[i] = 0;
    }

    for (int i = 0; i < k; ++i) {
        rankeable[size- k + i] = array[i];
    }

    std::cout << array_to_string(rankeable, size) << " ";
    std::cout << rank2(rankeable, size, k) << "\n";

    int output;
    for (int i = 0; i < 24 - 1; ++i) {
        output = lex_perm(array, size, k);
        for (int i = 0; i < k; ++i) {
            rankeable[size- k + i] = array[i];
        }
        std::cout << array_to_string(rankeable, size) << " ";
        std::cout << rank2(rankeable, size, k) << "\n";

    }

    return 0;
}
