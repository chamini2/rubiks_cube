#include "../rank.hpp"

int main(int argc, char const *argv[]) {
    int *array = new int[12];
    int i;

    array[0] = 0;
    array[1] = 9;
    array[2] = 4;
    array[3] = 3;
    array[4] = 10;
    array[5] = 1;
    array[6] = 5;
    array[7] = 6;
    array[8] = 2;
    array[9] = 8;
    array[10] = 7;
    array[11] = 11;

    print_array(array, 12);
    std::cout << "\n";

    i = rank(12, array, 6, 2);
    std::cout << i << "\n";

    array = unrank(12, i, 6, 2);

    print_array(array, 12);
    std::cout << "\n";

    delete[] array;
    return 0;
}
