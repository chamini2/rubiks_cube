#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "pdb.hpp"

int8_t *cpdb;
int8_t *e1pdb;
int8_t *e2pdb;

/*
 * Definicion para el valor de retorno de la funcion recursiva utilizado en IDA*:
 * Un par que contiene una cola de enteros para el plan de ejecucion, donde cada
 * entero representa un movimiento, y un entero para representar el valor t del
 * nivel que esta cubriendo el algoritmo en un momento dado.
 */
typedef std::pair <std::queue<std::string>*, int> Par;

Cube* gen_random_cube(int moves);
void load_pdb(std::string folder, int edges_type);
int h_value(Cube * c);
Cube* make_root_node(int moves);
Cube* make_leveled_node(int moves);
bool is_goal(Cube *c);
std::queue<std::string>* extract_solution(Cube *n);
Par* chequear_cond_parada(Cube* n, int g, int t);
Par* bounded_dfs(Cube*, int, int);
Par* avanzar_dfs(Cube* n, int g, int t);
std::queue<std::string>* IDA();
void validar_entrada(int argc, char const *argv[]);
bool get_option();

int NUMBER_OF_MOVES = 50;



int main(int argc, char const *argv[]) {
    bool option = get_option();

    while (!option) {
        option = get_option();
    }

    // validar_entrada(argc, argv);
    load_pdb("../pdbs/", 1);

    std::queue<std::string> *plan = IDA();

    if (plan != NULL) {
        // Solution found
        std::cout << "Plan encontrado: " << std::endl;
        int i;
        int plan_size = plan->size();

        for (i =  0; i < plan_size; i++) {
            // Shows found plan
            std::cout << plan->front() << " ";
            plan->pop();
        }
        std::cout << std::endl;
    } else {
        // No se consigio solucion
        std::cout << "Plan no encontrado" << std::endl;
    }

    delete(plan);
    return 0;
}


Cube* gen_random_cube(int moves) {
    char faces[] = {'f', 'b', 'r', 'l', 't', 'd'};
    Cube *cube = new Cube;

    for (int i = 0; i < moves; ++i) {
        int faceIndex = rand() % 6;
        int facelet = rand() % 3;

        switch(facelet) {
            case(0):
                cube->clock(faces[faceIndex]);
                break;
            case(1):
                cube->counter(faces[faceIndex]);
                break;
            case(2):
                cube->hundred(faces[faceIndex]);
                break;
        }
    }

    cube->reset_last();

    return cube;
}

/*
 * Funcion que carga la PDB en memoria y la almacena en una variable global,
 * para luego ser utilizada en la funcion h_value.
 */

void load_pdb(std::string folder, int edges_type) {
    int CORNERS_MAX = 264539520;
    int EDGES_MAX = 42577920;  // 510935040 (edges of 7)
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
    int *edges2;
    int values[3];  // 0 corens | 1 edges1 | 2 edges2
    int h;

    corners = c->get_corners();
    edges  = c->get_edges();
    edges2 = c->get_edges();

    int c_val = rank(8, corners, 0, 8, 3);
    int e1_val = rank(12, edges, 0, 6, 2);
    int e2_val = rank(12, edges2, 6, 6, 2);

    values[0] = cpdb[c_val];
    values[1] = e1pdb[e1_val];
    values[2] = e2pdb[e2_val];

    // std::max returns an iterator, thus the *.
    h = *std::max_element(values, values+3);

    return h;
}


Cube* make_root_node(int moves) {
    Cube *c = gen_random_cube(moves);

    return c;
}

/*
Funcion que retorna un Cube desordenado mediante <levels> movimientos random
sobre un cubo en su estado goal.
*/

Cube* make_leveled_node(int levels) {
    Cube* c = new Cube;
    int random_succesor, tmp;
    std::queue<Cube*> *succ;

    srand(time(NULL));
    std::string desorden = "";


    for (int i = 0; i < levels; i++) {
        succ = c->succ();
        random_succesor = rand() % succ->size();

        /*
        Se eliminan <random_sucessor> sucesores de la cola y se realiza
        el movimiento correspondiente al sucesor que quede al principio
        de la cola.
        */
        for (int j = 0; j < random_succesor - 1; j++) {
            delete(succ->front());
            succ->pop();
        }

        delete(c);
        c = succ->front();
        succ->pop();

        desorden.insert(0, pretty_last_to_str(c->get_last()));
        desorden.insert(0, " ");

        // Loop para liberar memoria de los que queda en succ
        tmp = succ->size();
        for (int j = 0; j < tmp ; j++) {
            delete(succ->front());
            succ->pop();
        }
        delete(succ);
    }

    std::cout << "Se utilizara como comienzo el cubo: " << c->to_string();
    std::cout << std::endl;
    std::cout << "Los movimientos realizados para desordenar son: " << desorden;
    std::cout << std::endl;

    c->reset_last();
    return c;
}

/*
 * Funcion que dado un Cube determina si este esta en su estado goal.
 */
bool is_goal(Cube *c) {
    if (c == NULL) {
        return false;
    }

    Cube *goal = new Cube;

    if (goal->equals(c)) {
        delete(goal);
        return true;
    }

    delete(goal);
    return false;
}

/*
 * Funcion que retorna el plan de ejecucion una vez hallado el goal.
 */

std::queue<std::string>* extract_solution(Cube *n) {
    std::cout << "Encontre el goal." << std::endl;
    std::queue<std::string> *plan = new std::queue<std::string>;
    plan->push(pretty_last_to_str(n->get_last()));
    return plan;
}

/*
 * Funcion que chequea si las condiciones de parada de la funcion bounded_dfs
 * se cumplen. Las condiciones son que el nivel actual del IDA* dado por t fue
 * sobrepasado o que el goal ha sido encontrado.
 */

Par* chequear_cond_parada(Cube* n, int g, int t) {
    Par* par_retorno = new Par;

    if ((g + h_value(n)) > t) {
        par_retorno->first = NULL;
        par_retorno->second = g + h_value(n);
        return par_retorno;
    }

    std::queue<std::string> *plan;

    if (is_goal(n)) {
        plan = extract_solution(n);
        std::cout << "Goal encontrado cuando t valia: " << t << std::endl;
        par_retorno->first = plan;
        par_retorno->second = g;
        return par_retorno;
    }

    delete(par_retorno);

    return NULL;
}

/*
 * Funcion que realiza la expansion del bounded en los sucesores del nodo n
 */

Par* avanzar_dfs(Cube* n, int g, int t) {
    Par* par_retorno = NULL;
    int new_t = std::numeric_limits<int>::max();  // Infinito

    std::queue<Cube*> *succ = n->succ();  // Lista de sucesores a expandir
    int tmp;
    int succ_size = succ->size();

    for (tmp = 0; tmp < succ_size; tmp++) {
        delete(par_retorno);
        par_retorno = bounded_dfs(succ->front(), g + 1 , t);
        delete(succ->front());
        succ->pop();

        if (par_retorno->first != NULL) {
            par_retorno->first->push(pretty_last_to_str(n->get_last()));
            int unused_size = succ->size();
            int j;

            for (j = 0; j < unused_size; j++) {
                delete(succ->front());
                succ->pop();
            }

            delete(succ);

            return par_retorno;
        }
        new_t = std::min(new_t, par_retorno->second);
    }

    par_retorno->first = NULL;
    par_retorno->second = new_t;
    delete(succ);
    return par_retorno;
}

/*
 * Funcion recursiva que realiza la busqueda del goal para el nivel dado por
 * <t> a partir del nodo <n> con costo <g>.
 */

Par* bounded_dfs(Cube* n, int g, int t) {
    Par* par_retorno = chequear_cond_parada(n, g, t);

    if (par_retorno != NULL) {
        // Hubo exito en las condiciones de parada
        return par_retorno;
    }

    delete(par_retorno);

    return avanzar_dfs(n, g, t);
}

/*
 * Funcion principal del algoritmo IDA*.
 */

std::queue<std::string>* IDA() {

    Cube* n = make_root_node(NUMBER_OF_MOVES);

    int t = h_value(n);
    int max_int = std::numeric_limits<int>::max();  // Infinite.
    Par* pair;
    std::queue<std::string>* plan;

    while (t != max_int) {
        pair = bounded_dfs(n, 0, t);
        plan = pair->first;
        t = pair->second;

        if (pair->first != NULL) {
    // Se consugio una solucion
            delete(n);
            delete(pair);

            return plan;
        }

        delete(pair);
    }

    delete(n);
    delete(pair);
    return NULL;
}

/*
 * Validar parametro de entrada para cantidad de movimientos para desordenar.
 */

void validar_entrada(int argc, char const *argv[]) {
    if (argc > 1) {
        int argv_int = atoi(argv[1]);

        if (0 <= argv_int && argv_int < 18) {
            NUMBER_OF_MOVES = argv_int;
        } else {
            std::cout << "Advertencia: "<< argv_int;
            std::cout << ": valor invalido para cantidad de movimientos";
            std::cout << " para desordenar. ";
            std::cout << "Utilizando valor por defecto." << std::endl;
        }
    }
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
            return true;
        case(2):
            std::cout << "Generating 1st edges PDB...\n";
            get_pdb(2);
            return true;
        case(3):
            std::cout << "Generating 2nd edges PDB...\n";
            get_pdb(3);
            return true;
        case(4):
            std::cout << "Proceeding with cube solving...\n";
            return true;
        default:
            return false;
    }
}