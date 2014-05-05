#include <fstream>
#include "../Set.hpp"

void aux_unrank(int n, int r, int *array, int low);
int aux_rank(int n, int *array, int *inverse, int low);

int main(int argc, char const *argv[]) {
    int *array;
    int r;

    for (int k = 0; k < 665280; ++k) {
        for (int i = 0; i < 12; ++i) {
            array[i] = i;
        }
        array = unrank(12, k, 6, 6, 2);
        print_array(array, 12);
        std::cout << std::flush;
        r = rank(12, array, 6, 6, 2);

        std::cout << "k = " << k << ", r = " << r;
    }

    return 0;
}
