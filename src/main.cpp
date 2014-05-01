#include "HashTable.hpp"

// std::tuple<void*, void*, void*> readPDBs();
void readPDBs ();

int main(int argc, char const *argv[]) {
    readPDBs();
    return 0;
}

// std::tuple<void*, void*, void*> readPDBs() {
void readPDBs() {
    FILE *file;
    // VARIABLES cpdb, e1pdb, e2pdb;
    int rank, temp = 1;
    uint8_t level;
    std::string *paths = new std::string[3];
    paths[0] = "../pdbs/cPDB.bin";
    paths[1] = "../pdbs/e1PDB.bin";
    paths[2] = "../pdbs/e2PDB.bin";


    for (int i = 0; i < 3; ++i) {
        file = fopen(paths[i].c_str(),"rb");

        if (file == NULL) {
            error("readPDBs | file '" + std::string(paths[i]) + "' did not open correctly", __LINE__, __FILE__);
            throw -1;
        }

        while (true) {
            if (temp == 0) {
                fclose(file);
                break;
            }

            temp = fread(&level, 1, 1, file);
            temp = fread(&rank , 4, 1, file);

            printf("%d %d\n", level, rank);
        }
    }

    delete[] paths;

    return;
}
