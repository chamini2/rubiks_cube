#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include "../Cube.hpp"

int CORNERS_MAX = 264539520;
int EDGES_MAX = 42577920; // 510935040 (edges of 7)

int8_t *CPDB;
int8_t *E1PDB;
int8_t *E2PDB;

/*
 * Cantidad de movimientos por defecto a realizar para desordenar el cubo.
 * Si se pasa por parametros a main un numero entre 0 y 18 al procedimiento se
 * utilizara ese valor, de lo contrario se utilizara este.
 *
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
typedef std::pair <std::queue<int>*,int> Par;

/*
 * Funcion que carga la PDB en memoria y la almacena en una variable global,
 * para luego ser utilizada en la funcion h_value.
 * No implementada.
 */
void load_pdb(std::string folder, int edges_type){
    FILE *file;
    int tmp;

    // the default behaviour is edges_type == 1 (42577920)
    if (edges_type == 2) {
        EDGES_MAX = 510935040;
    }

    CPDB  = new int8_t[CORNERS_MAX];
    E1PDB = new int8_t[EDGES_MAX];
    E2PDB = new int8_t[EDGES_MAX];

    file = fopen(folder + "cPDB.bin", "rb");
    if (file == NULL) {
        error("readPDBs | file 'cPDB.bin' did not open correctly", __LINE__, __FILE__);
        throw -1;
    }
    fread(cpdb, sizeof(int8_t), CORNERS_MAX, file);
    fclose(file);

    file = fopen(folder + "e1PDB.bin", "rb");
    if (file == NULL) {
        error("readPDBs | file 'e1PDB.bin' did not open correctly", __LINE__, __FILE__);
        throw -1;
    }
    fread(cpdb, sizeof(int8_t), EDGES_MAX, file);
    fclose(file);

    file = fopen(folder + "e2PDB.bin", "rb");
    if (file == NULL) {
        error("readPDBs | file 'e2PDB.bin' did not open correctly", __LINE__, __FILE__);
        throw -1;
    }
    fread(cpdb, sizeof(int8_t), EDGES_MAX, file);
    fclose(file);

    return;
}

/*
 * Funcion heurística.
 * No implementada.
 */
int h_value(Cube* c){
    return 0;
}

/*
 * Funcion que retorna un Cube desordenado mediante <levels> movimientos random
 * sobre un cubo en su estado goal.
 */
Cube* make_root_node(int levels){
    Cube *cube = new Cube;
    int i;
    std::queue<Cube*> *succ;
    int tmp, j, random_succesor;

    for (i = 0; i < levels; i++){
        succ = cube->succ();
        srand(time(NULL));
        random_succesor = rand() % (succ->size() - 1);

        /*
         * Se eliminan <random_sucessor> sucesores de la cola y se realiza
         * el movimiento correspondiente al sucesor que quede al principio
         * de la cola.
         */
        for (j = 0; j < random_succesor; j++){
            delete(succ->front());
            succ->pop();
        }

        delete(cube);
        c = succ->front();
        succ->pop();

        //Loop para liberar memoria de los que queda en succ
        tmp = succ->size();
        for (j = 0; j < tmp ; j++){
            delete(succ->front());
            succ->pop();
        }

        delete(succ);
    }

    std::cout << "Se utilizara como comienzo el cubo: " << c->to_string() << "\n";
    cube->reset_last();
    return cube;
}

/*
 * Funcion que dado un Cube determina si este esta en su estado goal.
 */
// Esta implementacion podria ser mas eficiente
///////////////////////////////////////////////// RESPUESTA:
// La única manera que se me ocurre (trivial al menos) es teniendo el Cube a
// comparar (goal) en memoria siempre (variable global),
// para no hacer 'new' cada vez
bool is_goal(Cube *c){
    Cube *goal = new Cube;

    if (c == NULL) {
        return false;
    }

    if (goal->equals(c)){
        delete(goal);
        return true;
    }

    delete(goal);
    return false;
}

/*
 * Funcion que retorna el plan de ejecucion una vez hallado el goal.
 * No implementada.
 */
std::queue<int>* extract_solution(Cube *n){
    std::cout << "Goal found.\n";
    std::queue<int> *plan = new std::queue<int>;
    int i;

    for (i = 0; i < 10 ; i++) {
        plan->push(i);
    }

    return plan;
}

/*
 * Funcion que chequea si las condiciones de parada de la funcion bounded_dfs
 * se cumplen. Las condiciones son que el nivel actual del IDA* dado por t fue
 * sobrepasado o que el goal ha sido encontrado.
 */
Par* chequear_cond_parada(Cube* n, int g, int t){
    Par* par_retorno = new Par;

    if ((g + h_value(n)) > t){
        par_retorno->first = NULL;
        par_retorno->second = g + h_value(n);
        return par_retorno;
    }

    std::queue<int> *plan;
    if (is_goal(n)){
        plan = extract_solution(n);
        std::cout << "Goal found with t = " << t << "\n";
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
Par* avanzar_dfs(Cube* n, int g, int t){
    Par* par_retorno = NULL;

    std::queue<int> *plan;
    int new_t = std::numeric_limits<int>::max(); // Infinito
    int j, tmp, unused_size;
    std::queue<Cube*> *succ = n->succ(); // Lista de sucesores a expandir
    int succ_size = succ->size();

    for (tmp = 0; tmp < succ_size; tmp++){
        delete(par_retorno);
        par_retorno = bounded_dfs(succ->front(), g + 1 , t);
        delete(succ->front());
        succ->pop();

        // Free memory and return
        if (par_retorno->first != NULL){
            unused_size = succ->size();
            for (j = 0; j < unused_size; j++){
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
Par* bounded_dfs(Cube* n, int g, int t){
    Par* par_retorno = chequear_cond_parada(n,g,t);

    //Hubo exito en las condiciones de parada
    if (par_retorno != NULL){
        return par_retorno;
    }

    delete(par_retorno);
    return avanzar_dfs(n,g,t);
}

/*
 * Funcion principal del algoritmo IDA*.
 */
std::queue<int>* IDA(){
    Cube* n = make_root_node(PROBLEM_LEVELS);
    int t = h_value(n);
    int max_int = std::numeric_limits<int>::max(); // Infinito.
    Par* pair;
    std::queue<int>* plan;

    while (t != max_int) {
        pair = bounded_dfs(n,0,t);
        plan = pair->first;
        t = pair->second;

        //Se consugio una solucion
        if (pair->first != NULL){
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
void validar_entrada(int argc, char const *argv[]){
    int argv_int = atoi(argv[1]);
    if (argc > 1){
        if (0 <= argv_int && argv_int < 18)
            PROBLEM_LEVELS = argv_int;
        else{
            std::cout << "Advertencia: "<< argv_int;
            std::cout << ": valor invalido para cantidad de movimientos para desordenar. ";
            std::cout << "Utilizando valor por defecto." << std::endl;
        }
    }
}

int main(int argc, char const *argv[]) {
    int plan_size, i;
    validar_entrada(argc, argv);
    load_pdb();

    std::queue<int> *plan = IDA();

    // Se consigio una solucion
    if (plan != NULL){
        std::cout << "Plan encontrado: " << std::endl;
        plan_size = plan->size();

        // Mostrar plan encontrado.
        for (i =  0; i < plan_size; i++){
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
