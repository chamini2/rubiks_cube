#include "Set.hpp"

int CORNERS_MAX = 264539520;
int EDGES_MAX = 42577920; // 510935040 (edges of 7)

int8_t** readPDBs(std::string folder);
// void readPDBs(std::string folder);

int main(int argc, char const *argv[]) {
    int8_t **pdbs = readPDBs("../pdbs/");

    // for (int i = 0; i < CORNERS_MAX; ++i) {
    //     std::cout << pdbs[0][i];
    // }
    // for (int i = 0; i < EDGES_MAX; ++i) {
    //     std::cout << pdbs[1][i];
    // }
    // for (int i = 0; i < EDGES_MAX; ++i) {
    //     std::cout << pdbs[2][i];
    // }

    // print_array(pdbs[0], CORNERS_MAX);
    // print_array(pdbs[1], EDGES_MAX);
    // print_array(pdbs[2], EDGES_MAX);
    return 0;
}

int8_t** readPDBs(std::string folder) {
    FILE *file;
    int8_t *cpdb, *e1pdb, *e2pdb;
    int temp;
    std::string *paths = new std::string[3];
    int8_t **pdbs;
    int sizes[3] = { CORNERS_MAX, EDGES_MAX, EDGES_MAX };

    paths[0] = folder + "cPDB.bin";
    paths[1] = folder + "e1PDB.bin";
    paths[2] = folder + "e2PDB.bin";

    pdbs = new int8_t*[3];

    cpdb  = new int8_t[CORNERS_MAX];
    e1pdb = new int8_t[EDGES_MAX];
    e2pdb = new int8_t[EDGES_MAX];

    pdbs[0] = cpdb;
    pdbs[1] = e1pdb;
    pdbs[2] = e2pdb;

    int8_t a;
    int b;
    file = fopen(paths[0].c_str(),"rb");
    if (file == NULL) {
        error("readPDBs | file '" + std::string(paths[0]) + "' did not open correctly", __LINE__, __FILE__);
        throw -1;
    }

    fread(cpdb, sizeof(int8_t), CORNERS_MAX, file);

    for (int i = 0; i < sizes[0]; ++i) {
        // temp = fread(&a, 1, 1, file);
        a = cpdb[i];
        if (a != 127) {
            printf("%d\n", a);
        }
    }
    fclose(file);

    // for (int i = 0; i < 3; ++i) {
    //     file = fopen(paths[i].c_str(),"rb");

    //     if (file == NULL) {
    //         error("readPDBs | file '" + std::string(paths[i]) + "' did not open correctly", __LINE__, __FILE__);
    //         throw -1;
    //     }

    //     temp = fread(pdbs[i], 1, sizes[i], file);

    //     // read error or reached EOF
    //     if (temp != sizes[i]) {
    //         error("readPDBs | file '" + std::string(paths[i]) + "' was not read correctly", __LINE__, __FILE__);
    //         throw -1;
    //     }

    //     fclose(file);
    // }

    delete[] paths;

    return pdbs;
}
