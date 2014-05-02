#include <math.h>
#include <iostream>
#include "../extra.hpp"
#include "../rank.hpp"
#include "../Set.hpp"

int main(int argc, char const *argv[]) {
//     int size = 4;
//     int k = 4;
//     int *array = new int[size];
//     int *rankeable = new int[size];

//     // for (int i = 2; i < size; ++i) {
//     //     array[i] = i;
//     // }

//     // for (int i = 0; i < 2; ++i) {
//     //     array[i] = 0;
//     // }

//     for (int i = 0; i < size; ++i) {
//         array[i] = i;
//         rankeable[i] = 0;
//     }

//     for (int i = 0; i < k; ++i) {
//         rankeable[size- k + i] = array[i];
//     }

//     std::cout << array_to_string(rankeable, size) << " ";
//     std::cout << rank2(rankeable, size, k) << "\n";

//     int output;
//     for (int i = 0; i < 24 - 1; ++i) {
//         output = lex_perm(array, size, k);
//         for (int i = 0; i < k; ++i) {
//             rankeable[size- k + i] = array[i];
//         }
//         std::cout << array_to_string(rankeable, size) << " ";
//         std::cout << rank2(rankeable, size, k) << "\n";

//     }

//     return 0;
    Cube* cube = new Cube;
    int *corners;
    int *edges;
    int *unrank_e;
    int *unrank_c;
    int info_edge;
    int info_corner;

    cube->hundred('b');

    edges = cube->get_edges();
    corners = cube->get_corners();

    std::cout << array_to_string(edges, 12) << "\n";

    for (int i = 0; i < 5; ++i) {
        edges[i] = 0;
    }


    std::cout << "Edges: " << array_to_string(edges, 12) << "\n";
    std::cout << "Corners" << array_to_string(corners, 8) << "\n";

    info_edge = rank(12, edges, 7, 2);
    info_corner = rank(8, corners, 8, 3);

    std::cout << "Rank edges: " << info_edge << "\n";
    std::cout << "Rank corners: " << info_corner << "\n";

    unrank_e = unrank(12, info_edge, 7, 2);
    unrank_c = unrank(8, info_corner, 8, 3);

    std::cout << "Unranked edges: " <<  array_to_string(unrank_e, 12) << "\n";
    std::cout << "Unranked corners: " <<  array_to_string(unrank_c, 8) << "\n";
}
