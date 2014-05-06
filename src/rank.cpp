#include <algorithm>
#include "rank.hpp"

void aux_unrank(int n, int r, int *array, int low) {
    if (n > low) {
        array_swap(array[n-1], array[r % n]);
        aux_unrank(n-1, floor(r/n), array, low);
    }
}

int aux_rank(int n, int *array, int *inverse, int low);

int *unrank(int n, int value, int low, int quan, int factor) {
    int *array = new int[n];
    int d, r, power = pow(factor, quan);
    int upp = low + quan;
    int new_low = n - quan;

    r = value / power;
    d = value % power;

    // Identity array
    for (int i = 0; i < n; ++i) {
        array[i] = i;
    }

    if (low == 0 && quan == 6 && factor == 2) {
        int *array_aux = new int[12];

        aux_unrank(12, r, array, 6);

        for (int i = 0; i < 6; ++i) {
            array_aux[i+6] = array[i];
        }

        for (int i = 0; i < 6; ++i) {
            array_aux[i] = array[i+6];
        }

        delete[] array;

        for (int i = upp - 1; i >= low; --i) {
            array_aux[i] += edge_orien_to_axis(d % factor, i, array_aux[i]);
            d = d / factor;
        }

        return array_aux;
    } else {
        if (low == 0 && quan < n) {
            aux_unrank(n, r, array, new_low);
            swap_entire_array(n, array, new_low, quan);
        } else {
            aux_unrank(upp, r, array, low);
        }

        // std::cout << "(unrank) n = " << n << ", new_low = " << new_low ;
        int *inverse = inv_array(array, n);
        int *array_copy = new int[12];
        for (int i = 0; i < n; ++i) {
            array_copy[i] = array[i];
        }
        // std::cout << ", rank  = " << aux_rank(n, array_copy, inverse, new_low) << "\n";
        delete[] inverse;
        delete[] array_copy;


        for (int i = upp - 1; i >= low; --i) {
            if (factor == 3) {
                array[i] += orien_to_axis(d % factor);
            } else {
                array[i] += edge_orien_to_axis(d % factor, i, array[i]);
            }
            d = d / factor;
        }

        return array;
    }
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
    int new_low = n - quan;

    if (low == 0 && quan == 6 && factor == 2) {
        int *swapped = new int[12];

        for (int i = 0; i < 6; ++i) {
            swapped[i+6] = array[i];
        }
        for (int i = 0; i < 6; ++i) {
            swapped[i] = array[i+6];
        }

        for (int i = 0; i < n; ++i) {
            aux[i] = cubie_to_pos(swapped[i]);
        }

        inverse = inv_array(aux, 12);
        value = aux_rank(12, aux, inverse, 6);

        value *= pow(factor, quan);
        for (int i = 0; i < 6; ++i) {
            orientation = orientation * factor + cubie_to_edge_orien(array[i], i);
        }
        value += orientation;

        delete[] array;
        delete[] swapped;
        delete[] aux;
        delete[] inverse;


        return value;
    } else {
        for (int i = 0; i < n; ++i) {
            aux[i] = cubie_to_pos(array[i]);
        }

        if (low == 0 && quan < n) {
            swap_entire_array(n, aux, low, quan);
            inverse = inv_array(aux, n);
            value = aux_rank(n, aux, inverse, new_low);
        } else {
            inverse = inv_array(aux, n);
            value = aux_rank(upp, aux, inverse, low);
        }

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
}
