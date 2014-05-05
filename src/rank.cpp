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
        if (factor == 3) {
            array[i] += orien_to_axis(d % factor);
        } else {
            array[i] += edge_orien_to_axis(d % factor, i, array[i]);
        }
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

int aux_rank(int n, int *array, int *inverse, int low) {

    if (n == low) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s + n * aux_rank(n-1, array, inverse, low);
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
int rank(int n, int *array, int low, int quan, int factor) {
    int *inverse;
    int *aux = new int[n];
    int value, orientation = 0;
    int upp = quan + low;
    // int edge = n - k;

    for (int i = 0; i < n; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, n);
    value = aux_rank(upp, aux, inverse, low);

    delete[] inverse;
    delete[] aux;

    value *= pow(factor, quan);
    for (int i = low; i < upp; ++i) {
        if (factor == 3) {
            orientation = orientation * factor + cubie_to_orien(array[i]);
        } else {
            orientation = orientation * factor + cubie_to_edge_orien(array[i], i);
        }
    }
    value += orientation;

    delete[] array;

    return value;
}
