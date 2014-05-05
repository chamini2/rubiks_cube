#include <math.h>
#include <iostream>
#include "../extra.hpp"
#include "../rank.hpp"
#include "../Set.hpp"

int main(int argc, char const *argv[]) {
    Cube* cube = new Cube;
    int *corners;
    int *edges;
    int *unrank_e;
    int *unrank_c;
    int info_edge;
    int info_corner;

    cube->clock('f');
    cube->counter('d');
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
