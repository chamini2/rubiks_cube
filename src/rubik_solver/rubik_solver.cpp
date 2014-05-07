#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include "../Cube.hpp"

int8_t *cpdb;
int8_t *e1pdb;
int8_t *e2pdb;


/*
  Cantidad de movimientos por defecto a realizar para desordenar el cubo.
  Si se pasa por parametros a main un numero entre 0 y 18 al procedimiento se
  utilizara ese valor, de lo contrario se utilizara este.

  El valor por defecto corresponde al ultimo valor en el que IDA* corre en
  menos de un minuto sin utilizar heuristica.
 */
int PROBLEM_LEVELS = 6;

/*
  Definicion para el valor de retorno de la funcion recursiva utilizado en IDA*:
  Un par que contiene una cola de enteros para el plan de ejecucion, donde cada
  entero representa un movimiento, y un entero para representar el valor t del
  nivel que esta cubriendo el algoritmo en un momento dado.
 */
typedef std::pair <std::queue<int>*,int> Par;

/*
  Funcion que carga la PDB en memoria y la almacena en una variable global,
  para luego ser utilizada en la funcion h_value.
  No implementada.
 */
void load_pdb(std::string folder, int edges_type){
    int CORNERS_MAX = 264539520;
    int EDGES_MAX = 42577920; // 510935040 (edges of 7)
    FILE *file;
    int tmp;

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
    int values[3]; // 0 corens | 1 edges1 | 2 edges2

    int c_val = rank(8, corners, 0, 8, 3);
    int e1_val = rank(12, edges, 0, 6, 2);;
    int e2_val = rank(12, corners, 6, 6, 2);;

    values[0] = cpdb[c_val];
    values[1] = e1pdb[e1_val];
    values[2] = e2pdb[e2_val];

    // std::max returns an iterator, thus the *.
    return *std::max_element(values, values+3);
}


/*
  Funcion que retorna un Cube desordenado mediante <levels> movimientos random
  sobre un cubo en su estado goal.
*/
Cube* make_root_node(int levels) {
  Cube *c = new Cube;
  int i;
  std::queue<Cube*> *succ;
  for (i = 0; i < levels; i++) {
    succ = c->succ();
    int j;
    srand(time(NULL));
    int random_succesor = rand() % (succ->size() - 1);
    for (j = 0; j < random_succesor; j++) {
    /*
      Se eliminan <random_sucessor> sucesores de la cola y se realiza
      el movimiento correspondiente al sucesor que quede al principio
      de la cola.
     */
      delete(succ->front());
      succ->pop();
    }
    delete(c);
    c = succ->front();
    succ->pop();

    // Loop para liberar memoria de los que queda en succ
    int tmp = succ->size();
    for (j = 0; j < tmp ; j++) {
      delete(succ->front());
      succ->pop();
    }
    delete(succ);
  }
  std::cout << "Se utilizara como comienzo el cubo: " << c->to_string() << std::endl;
  c->reset_last();
  return c;
}

bool is_goal(Cube *c) {
  /*
    Funcion que dado un Cube determina si este esta en su estado goal.
   */

  // Esta implementacion podria ser mas eficiente
  if (c == NULL)
    return false;
  Cube *goal = new Cube;
  if (goal->equals(c)) {
    delete(goal);
    return true;
  }
  delete(goal);
  return false;
}

std::queue<int>* extract_solution(Cube *n) {
  /*
    Funcion que retorna el plan de ejecucion una vez hallado el goal.
    No implementada.
   */
  std::cout << "Encontre el goal." << std::endl;
  std::queue<int> *plan = new std::queue<int>;
  int i;
  for (i = 0; i < 10 ; i++)
    plan->push(i);
  return plan;
}

  /*
    Funcion que chequea si las condiciones de parada de la funcion bounded_dfs
    se cumplen. Las condiciones son que el nivel actual del IDA* dado por t fue
    sobrepasado o que el goal ha sido encontrado.
   */

Par* chequear_cond_parada(Cube* n, int g, int t) {
    Par* par_retorno = new Par;

    if ((g + h_value(n)) > t) {
        par_retorno->first = NULL;
        par_retorno->second = g + h_value(n);
        return par_retorno;
    }

    std::queue<int> *plan;
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

Par* bounded_dfs(Cube*, int, int);


Par* avanzar_dfs(Cube* n, int g, int t) {
  /*
    Funcion que realiza la expansion del bounded en los sucesores del nodo n
   */
  Par* par_retorno = NULL;

  std::queue<int> *plan;
  int new_t = std::numeric_limits<int>::max(); // Infinito

  std::queue<Cube*> *succ = n->succ(); // Lista de sucesores a expandir
  int tmp;
  int succ_size = succ->size();

  for (tmp = 0; tmp < succ_size; tmp++) {
    delete(par_retorno);
    par_retorno = bounded_dfs(succ->front(), g + 1 , t);
    delete(succ->front());
    succ->pop();

    if (par_retorno->first != NULL) {
      //Free memory and return
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
    Funcion recursiva que realiza la busqueda del goal para el nivel dado por
    <t> a partir del nodo <n> con costo <g>.
   */

Par* bounded_dfs(Cube* n, int g, int t) {
    Par* par_retorno = chequear_cond_parada(n,g,t);

    if (par_retorno != NULL) {
    //Hubo exito en las condiciones de parada
        return par_retorno;
    }

    delete(par_retorno);

    return avanzar_dfs(n,g,t);
}

////////////////////////////////////////////////////////////////////////////////

  /*
    Funcion principal del algoritmo IDA*.
  */

std::queue<int>* IDA() {
    Cube* n = make_root_node(PROBLEM_LEVELS);
    int t = h_value(n);
    int max_int = std::numeric_limits<int>::max();  // Infinite.
    Par* pair;

    std::queue<int>* plan;

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

////////////////////////////////////////////////////////////////////////////////

void validar_entrada(int argc, char const *argv[]) {
  /*
    Validar parametro de entrada para cantidad de movimientos para desordenar.
   */
  if (argc > 1) {
    int argv_int = atoi(argv[1]);
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
  validar_entrada(argc, argv);
  load_pdb("../pdbs/", 1);

  std::queue<int> *plan = IDA();

  if (plan != NULL) {
    //Se consigio una solucion
    std::cout << "Plan encontrado: " << std::endl;
    int i;
    int plan_size = plan->size();
    for (i =  0; i < plan_size; i++) {
      //Mostrar plan encontrado.
      std::cout << plan->front() << " ";
      plan->pop();
    }
    std::cout << std::endl;
  }
  else {
    //No se consigio solucion
    std::cout << "Plan no encontrado" << std::endl;
  }
  delete(plan);
  return 0;
}
