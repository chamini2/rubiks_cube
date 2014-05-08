#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Cube.hpp"

int8_t *cpdb;
int8_t *e1pdb;
int8_t *e2pdb;

Cube *goal_compare;

/*
 * Cantidad de movimientos por defecto a realizar para desordenar el cubo.
 * Si se pasa por parametros a main un numero entre 0 y 18 al procedimiento se
 * utilizara ese valor, de lo contrario se utilizara este.

 * El valor por defecto corresponde al ultimo valor en el que IDA* corre en
 * menos de un minuto sin utilizar heuristica.
 */
int PROBLEM_LEVELS = 6;

/*
 * Definicion para el valor de retorno de la funcion recursiva utilizado en IDA*:
 * Un par que contiene una cola de enteros para el plan de ejecucion, donde cada
 * entero representa un movimiento, y un entero para representar el valor t del
 * nivel que esta cubriendo el algoritmo en un momento dado.
 */
typedef std::pair <std::queue<std::string>*,int> Par;

/*
 * Funcion que carga la PDB en memoria y la almacena en una variable global,
 * para luego ser utilizada en la funcion h_value.
 * No implementada.
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
    int *edges2;
    int values[3]; // 0 corens | 1 edges1 | 2 edges2

    corners = c->get_corners();
    edges  = c->get_edges();
    edges2 = c->get_edges();

    int c_val = rank(8, corners, 0, 8, 3);
    int e1_val = rank(12, edges, 0, 6, 2);;
    int e2_val = rank(12, edges2, 6, 6, 2);;

    values[0] = cpdb[c_val];
    values[1] = e1pdb[e1_val];
    values[2] = e2pdb[e2_val];

    // std::max returns an iterator, thus the *.
    return *std::max_element(values, values+3);
}


/*
 * Funcion que retorna un Cube desordenado mediante <levels> movimientos random
 * sobre un cubo en su estado goal.
*/
Cube* make_root_node(int levels) {
    Cube *c = new Cube;
    int random_succesor, tmp;
    std::queue<Cube*> *succ;

    srand(time(NULL));
    std::string desorden = "";

    for (int i = 0; i < levels; i++) {
        succ = c->succ();
        random_succesor = rand() % succ->size();
        /* Se eliminan <random_sucessor> sucesores de la cola y se realiza
         * el movimiento correspondiente al sucesor que quede al principio
         * de la cola. */
        for (int j = 0; j < random_succesor - 1; j++) {
            delete(succ->front());
            succ->pop();
        }
        delete(c);
        c = succ->front();
        succ->pop();

        desorden.insert(0,pretty_last_to_str(c->get_last()));
        desorden.insert(0, " ");

        // Loop para liberar memoria de los que queda en succ
        tmp = succ->size();
        for (int j = 0; j < tmp ; j++) {
            delete(succ->front());
            succ->pop();
        }
        delete(succ);
    }

    std::cout << "Se utilizara como comienzo el cubo: " << c->to_string() << "\n";
    std::cout << "Los movimientos realizados para desordenar son: " << desorden << "\n";
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

    if (goal_compare->equals(c)) {
        return true;
    }

    return false;
}

/*
 * Funcion que retorna el plan de ejecucion una vez hallado el goal.
 * No implementada.
 */
std::queue<std::string>* extract_solution(Cube *n) {
    std::cout << "Encontre el goal.\n";
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
        std::cout << "Goal encontrado cuando t valia: " << t << "\n";
        par_retorno->first = plan;
        par_retorno->second = g;
        return par_retorno;
    }

    delete(par_retorno);

    return NULL;
}

Par* bounded_dfs(Cube*, int, int);

/*
 * Funcion que realiza la expansion del bounded en los sucesores del nodo n
 */
Par* avanzar_dfs(Cube* n, int g, int t) {
    Par* par_retorno = NULL;
    int new_t = std::numeric_limits<int>::max();    // Infinito
    std::queue<Cube*> *succ = n->succ();            // Lista de sucesores a expandir
    int succ_size = succ->size();
    int unused_size;

    for (int i = 0; i < succ_size; i++) {
        delete(par_retorno);
        par_retorno = bounded_dfs(succ->front(), g + 1 , t);

        delete(succ->front());
        succ->pop();

        if (par_retorno->first != NULL) {
            par_retorno->first->push(pretty_last_to_str(n->get_last()));
            unused_size = succ->size();

            for (int j = 0; j < unused_size; j++) {
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
    Par* par_retorno = chequear_cond_parada(n,g,t);

    //Hubo exito en las condiciones de parada
    if (par_retorno != NULL) {
        return par_retorno;
    }

    delete(par_retorno);
    return avanzar_dfs(n,g,t);
}

////////////////////////////////////////////////////////////////////////////////

/*
 *Funcion principal del algoritmo IDA*.
 */
std::queue<std::string>* IDA() {
    Cube* n = make_root_node(PROBLEM_LEVELS);
    int t = h_value(n);
    int max_int = std::numeric_limits<int>::max();  // Infinite.
    Par* pair;
    std::queue<std::string>* plan;

    while (t != max_int) {
        pair = bounded_dfs(n, 0, t);
        plan = pair->first;
        t = pair->second;

        // Se consugio una solucion
        if (pair->first != NULL) {
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

////////////////////////////////////////////////////////////////////////////////

/*
 * Validar parametro de entrada para cantidad de movimientos para desordenar.
 */
void validar_entrada(int argc, char const *argv[]) {
    if (argc > 1) {
        int argv_int = atoi(argv[1]);
        if (0 <= argv_int && argv_int < 18) {
            PROBLEM_LEVELS = argv_int;
        } else {
            std::cout << "Advertencia: "<< argv_int;
            std::cout << ": valor invalido para cantidad de movimientos para desordenar. ";
            std::cout << "Utilizando valor por defecto.\n";
        }
    }
}

int main(int argc, char const *argv[]) {
    goal_compare = new Cube;
    std::queue<std::string> *plan;

    validar_entrada(argc, argv);
    load_pdb("../pdbs/", 1);
    plan = IDA();

    //Se consigio una solucion
    if (plan != NULL) {
        std::cout << "Plan encontrado: \n";
        int plan_size = plan->size();
        //Mostrar plan encontrado.
        for (int i =  0; i < plan_size; i++) {
            std::cout << plan->front() << " ";
            plan->pop();
        }
        std::cout << "\n";
    } else {
    //No se consiguio solucion
        std::cout << "Plan no encontrado\n";
    }

    delete(plan);
    return 0;
}
