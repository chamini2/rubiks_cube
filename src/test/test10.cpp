#include <fstream>
#include "../Set.hpp"

void aux_unrank(int n, int r, int *array, int low);
int aux_rank(int n, int *array, int *inverse, int low);

int main(int argc, char const *argv[]) {
    int *array;
    int aux[12], inverse[12];
    int r = 0;

    for (int k = 0; k < 42577920; ++k) {

        for (int i = 0; i < 12; ++i) {
            aux[i] = i;
        }

        array = unrank(12, k, 0, 6, 2);
        // aux_unrank(12, k, aux, 6);
        // swap_entire_array(12, aux, 6, 6);

        std::cout << "k = " << k << " | ";
        print_array(array, 12);
        r = rank(12, array, 0, 6, 2);
        std::cout << " | r = " << r << (r == k ? " +" : " *****") << "\n";
    }

    return 0;
}
