#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "pdb.hpp"

int8_t *cpdb;
int8_t *e1pdb;
int8_t *e2pdb;

Cube rubik;
std::vector<int> path;

int NUMBER_OF_MOVES = 50;

/*
 * Definicion para el valor de retorno de la funcion recursiva utilizado en IDA*:
 * Un par que contiene una cola de enteros para el plan de ejecucion, donde cada
 * entero representa un movimiento, y un entero para representar el valor t del
 * nivel que esta cubriendo el algoritmo en un momento dado.
 */
typedef std::pair <std::queue<std::string>*,int> Par;
Cube *goal_compare;

void gen_random_cube(int moves);
void load_pdb(std::string folder, int edges_type);
int h_value(Cube * c);
void make_root_node(int moves);
bool is_goal(Cube *c);
Par* bounded_dfs(Cube*, int, int);
bool IDA();
void validate_args(int argc, char const *argv[]);
bool get_option();


int main(int argc, char const *argv[]) {
    bool option;
    bool sol;
    int tmp;

    do {
        option = get_option();
    } while (!option);

    goal_compare = new Cube;
    load_pdb("../pdbs/", 1);
    std::cout << " loaded the PDBs...\n";

    sol = IDA();

    if (sol) {
        std::cout << "path found: \n";
        while (path.size() > 0) {
            tmp = path.back();
            path.pop_back();
            std::cout << pretty_last_to_str(tmp) << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "no path found. :(\n";
    }
    return 0;
}

/*
 * Funcion que carga la PDB en memoria y la almacena en una variable global,
 * para luego ser utilizada en la funcion h_value.
 */
 void load_pdb(std::string folder, int edges_type){
     int CORNERS_MAX = 264539520;
     int EDGES_MAX = 42577920; // 510935040 (edges of 7)
     FILE *file;

     // the default behaviour is edges_type == 1 (42577920)
     if (edges_type == 2) {
         EDGES_MAX = 510935040;
     }

     cpdb  = new int8_t[CORNERS_MAX];
     e1pdb = new int8_t[EDGES_MAX];
     e2pdb = new int8_t[EDGES_MAX];

     file = fopen(std::string(folder + "cPDB.bin").c_str(), "rb");
     if (file == NULL) {
         error("readPDBs | file 'cPDB.bin' did not open correctly", __LINE__, __FILE__);
         throw -1;
     }
     fread(cpdb, sizeof(int8_t), CORNERS_MAX, file);
     fclose(file);

     file = fopen(std::string(folder + "e1PDB.bin").c_str(), "rb");
     if (file == NULL) {
         error("readPDBs | file 'e1PDB.bin' did not open correctly", __LINE__, __FILE__);
         throw -1;
     }
     fread(e1pdb, sizeof(int8_t), EDGES_MAX, file);
     fclose(file);

     file = fopen(std::string(folder + "e2PDB.bin").c_str(), "rb");
     if (file == NULL) {
         error("readPDBs | file 'e2PDB.bin' did not open correctly", __LINE__, __FILE__);
         throw -1;
     }
     fread(e2pdb, sizeof(int8_t), EDGES_MAX, file);
     fclose(file);
}

int h_value(Cube * c) {
    int *corners;
    int *edges;
    int values[3]; // 0 corners | 1 edges1 | 2 edges2

    corners = c->get_corners();
    edges = c->get_edges();

    int c_val  = rank(8, corners, 0, 8, 3);
    int e1_val = rank(12, edges, 0, 6, 2);
    int e2_val = rank(12, edges, 6, 6, 2);

    values[0] = cpdb[c_val];
    values[1] = e1pdb[e1_val];
    values[2] = e2pdb[e2_val];

    std::cout << " - " << values[0] << " - " << values[1] << " - " << values[2] << "\n";

    // std::max returns an iterator, thus the *.
    int value = *std::max_element(values, values+3);

    if (value == 127) {
        error("Why would 127 appear?", __LINE__, __FILE__);
        throw -1;
    }

    return value;
}

/*
 * Funcion que dado un Cube determina si este esta en su estado goal.
 */
bool is_goal(Cube *c) {
    if (c == NULL) {
        return false;
    }

    if (goal_compare->equals(c)) {
        return true;
    }

    return false;
}

/*
 * Funcion recursiva que realiza la busqueda del goal para el nivel dado por
 * <t> a partir del nodo <n> con costo <g>.
 */
std::pair<int,bool> bounded_dfs(int g, int t) {
    int h = h_value(&rubik);
    if( g + h > t ) return std::make_pair(g + h, false);
    if( h == 0 ) return std::make_pair(g, true);

    int new_t = std::numeric_limits<int>::max();

    for (int i = 0; i < 18; ++i) {
        if (applicable(i, path.back())) {
            rubik.apply(i);
            path.push_back(i);
            std::pair<int,bool> r = bounded_dfs(g+1, t);
            rubik.apply_inverse(i);

            // consiguió solución
            if (r.second) return r;

            path.pop_back();
            new_t = r.first < new_t ? r.first : new_t;
        }
    }
    return std::make_pair(new_t, false);
}

/*
 * Funcion principal del algoritmo IDA*.
 */
bool IDA() {
    make_root_node(NUMBER_OF_MOVES);
    int t = h_value(&rubik);
    int max_int = std::numeric_limits<int>::max();  // Infinite.
    std::pair<int, bool> pair;

    while (t != max_int) {
        pair = bounded_dfs(0, t);
        t = pair.first;

        // consiguió solución
        if ( pair.second ) {
            return true;
        }
    }

    return false;
}

bool get_option() {
    std::cout << "Welcome to yet another Rubik's cube solver\n";
    std::cout << "Select an option:\n";
    std::cout << "  1) Generate corners PDB (about 30 minutes)\n";
    std::cout << "  2) Generate 1st edges PDB (about 15 minutes)\n";
    std::cout << "  3) Generate 2nd edges PDB (about 15 minutes).\n";
    std::cout << "  4) Solve Rubik's cube for random instance.\n";

    int option;
    std::cin >> option;

    switch (option) {
        case(1):
            std::cout << "Generating corners PDB...\n";
            get_pdb(1);
            std::cout << "All done!\n";
            exit(0);
        case(2):
            std::cout << "Generating 1st edges PDB...\n";
            get_pdb(2);
            std::cout << "All done!\n";
            exit(0);
        case(3):
            std::cout << "Generating 2nd edges PDB...\n";
            get_pdb(3);
            std::cout << "All done!\n";
            exit(0);
        case(4):
            std::cout << "Proceeding with cube solving...";
            return true;
        default:
            return false;
    }
}

void make_root_node(int moves) {
    gen_random_cube(moves);
}

void gen_random_cube(int moves) {
    char faces[] = {'f', 'b', 'r', 'l', 't', 'd'};

    srand(time(NULL));

    for (int i = 0; i < moves; ++i) {
        int faceIndex = rand() % 6;
        int facelet = rand() % 3;

        switch(facelet) {
            case 0:
                rubik.clock(faces[faceIndex]);
                std::cout << faces[faceIndex] << "- " << std::flush;
                break;
            case 1:
                rubik.counter(faces[faceIndex]);
                std::cout << faces[faceIndex] << "+ " << std::flush;
                break;
            case 2:
                rubik.hundred(faces[faceIndex]);
                std::cout << faces[faceIndex] << "++ " << std::flush;
                break;
        }
    }

    rubik.reset_last();
    std::cout << "\n";
}
