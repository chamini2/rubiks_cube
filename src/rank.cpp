#include <algorithm>
#include "rank.hpp"

void aux_unrank(int n, int r, int *array, int edge) {
    if (n > edge) {
        array_swap(array[n-1], array[r % n]);
        aux_unrank(n-1, floor(r/n), array, edge);
    }
}

int *unrank(int n, int value, int k, int factor) {
    int *array = new int[n];
    bool *aux = new bool[n];
    int d, r, power = pow(factor, k);
    int edge = n-k, aux_i = 0;


    r = value / power;
    d = value % power;

    // Identity array
    for (int i = 0; i < n; ++i) {
        array[i] = i;
        aux[i] = true;
    }

    aux_unrank(n, r, array, edge);

    for (int i = n - 1; i >= edge; --i) {
        array[i] += orien_to_axis(d % factor);
        d = d / factor;
    }

    // fill incrementally the unchecked part
    for (int i = 0; i < n; ++i) {
        aux[cubie_to_pos(array[i])] = false;
    }

    aux_i = 0;
    for (int i = 0; i < n; ++i) {
        if (aux[i]) {
            array[aux_i] = i;
            aux_i++;
        }
    }
    std::sort(array, array+edge);

    delete[] aux;

    return array;
}

////////////////////////////////////////////////////////////////////////////////

int aux_rank(int n, int *array, int *inverse, int edge) {

    if (n == edge) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s + n * aux_rank(n-1, array, inverse, edge);
}

/*
 * Given a array with a k-permutation of n elements, returns an unique integer
 * for such permutation.
 *
 * For complete permutations, k must be equal to n.
 *
 * For k-permutations, it is assumed that the array contains the k elements in
 * rightmost k positions of the array. The contents of the rest are
 * irrelevant.
 */
int rank(int n, int *array, int k, int factor) {
    int *inverse;
    int *aux = new int[n];
    int value, orientation = 0;
    int edge = n-k;

    for (int i = 0; i < n; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, n);
    value = aux_rank(n, aux, inverse, edge);

    delete[] inverse;
    delete[] aux;

    value *= pow(factor,k);
    for (int i = n-k; i < n; ++i) {
        orientation = orientation * factor + cubie_to_orien(array[i]);
    }
    value += orientation;

    delete[] array;

    return value;
}
