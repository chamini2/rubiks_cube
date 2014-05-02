#include "rank.hpp"

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
    int edge = n-k-1;

    for (int i = 0; i < n; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, n);
    value = aux_rank(n, aux, inverse, edge);

    delete[] inverse;
    delete[] aux;

    value *= pow(factor,n);
    for (int i = n-k; i < n; ++i) {
        orientation = orientation * factor + cubie_to_orien(array[i]);
    }
    value += orientation;

    delete[] array;

    return value;
}
