#include <iostream>
#include <limits>
#include <stdlib.h>     
#include <time.h>  
#include "../Cube.hpp"     

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
typedef std::pair <std::queue<std::string>*,int> Par;

void load_pdb(){
  /*
    Funcion que carga la PDB en memoria y la almacena en una variable global,
    para luego ser untilizada en la funcion h_value.
    No implementada.
   */
  return;
}

int h_value(Cube* c){
  /*
    Funcion heuristica.
    No implementada.
   */
  return 0;
}


Cube* make_root_node(int levels){
  /*
   Funcion que retorna un Cube desordenado mediante <levels> movimientos random
   sobre un cubo en su estado goal.
   */
  Cube *c = new Cube;
  int i;
  std::queue<Cube*> *succ;
  srand(time(NULL));
  std::string desorden = "";
  for (i = 0; i < levels; i++){
    succ = c->succ();
    int j;
    int random_succesor = rand() % succ->size();
    for (j = 0; j < random_succesor - 1; j++){
      /* Se eliminan <random_sucessor> sucesores de la cola y se realiza
	el movimiento correspondiente al sucesor que quede al principio
	de la cola.*/
      delete(succ->front());
      succ->pop();
    }
    delete(c);    
    c = succ->front();
    desorden.insert(0,pretty_last_to_str(c->get_last()));
    desorden.insert(0, " ");
    succ->pop();

    //Loop para liberar memoria de los que queda en succ
    int tmp = succ->size();
    for (j = 0; j < tmp ; j++){
      delete(succ->front());
      succ->pop();
    }
    delete(succ);
  }
  std::cout << "Se utilizara como comienzo el cubo: " << c->to_string() << std::endl;
  std::cout << "Los movimientos realizados para desordenar son: " << desorden << std::endl;
  c->reset_last();
  return c;
}

bool is_goal(Cube *c){
  /*
    Funcion que dado un Cube determina si este esta en su estado goal.
   */

  //Esta implementacion podria ser mas eficiente
  if (c == NULL)
    return false;
  Cube *goal = new Cube; 
  if (goal->equals(c)){
    delete(goal);
    return true;
  }
  delete(goal);
  return false;
}

std::queue<std::string>* extract_solution(Cube *n){
  /*
    Funcion que retorna el plan de ejecucion una vez hallado el goal.
    No implementada.
   */
  std::cout << "Encontre el goal." << std::endl;
  std::queue<std::string> *plan = new std::queue<std::string>; 
  plan->push(pretty_last_to_str(n->get_last()));
  return plan;
}

Par* chequear_cond_parada(Cube* n, int g, int t){
  /*
    Funcion que chequea si las condiciones de parada de la funcion bounded_dfs 
    se cumplen. Las condiciones son que el nivel actual del IDA* dado por t fue
    sobrepasado o que el goal ha sido encontrado.
   */
  Par* par_retorno = new Par;

  if ((g + h_value(n)) > t){
    par_retorno->first = NULL;
    par_retorno->second = g + h_value(n);
    return par_retorno;    
  }

  std::queue<std::string> *plan;
  if (is_goal(n)){
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


Par* avanzar_dfs(Cube* n, int g, int t){
  /*
    Funcion que realiza la expansion del bounded en los sucesores del nodo n
   */
  Par* par_retorno = NULL;

  std::queue<std::string> *plan;
  int new_t = std::numeric_limits<int>::max(); // Infinito

  std::queue<Cube*> *succ = n->succ(); // Lista de sucesores a expandir   
  int tmp;
  int succ_size = succ->size(); 

  for (tmp = 0; tmp < succ_size; tmp++){
    delete(par_retorno);
    par_retorno = bounded_dfs(succ->front(), g + 1 , t);
    delete(succ->front());
    succ->pop();
    if (par_retorno->first != NULL){
      par_retorno->first->push(pretty_last_to_str(n->get_last()));
      int unused_size = succ->size(); 
      int j;
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


Par* bounded_dfs(Cube* n, int g, int t){
  /*
    Funcion recursiva que realiza la busqueda del goal para el nivel dado por 
    <t> a partir del nodo <n> con costo <g>.
   */

  Par* par_retorno = chequear_cond_parada(n,g,t);
  if (par_retorno != NULL){
    //Hubo exito en las condiciones de parada
    return par_retorno;
  }
  delete(par_retorno);
  return avanzar_dfs(n,g,t);
}

std::queue<std::string>* IDA(){
  /*
    Funcion principal del algoritmo IDA*.
  */
  Cube* n = make_root_node(PROBLEM_LEVELS);
  int t = h_value(n);
  int max_int = std::numeric_limits<int>::max(); // Infinito.
  Par* pair;
  std::queue<std::string>* plan;
  while (t != max_int) {
    pair = bounded_dfs(n,0,t);
    plan = pair->first;
    t = pair->second;    
    if (pair->first != NULL){
      //Se consugio una solucion
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

void validar_entrada(int argc, char const *argv[]){
  /*
    Validar parametro de entrada para cantidad de movimientos para desordenar.
   */
  if (argc > 1){
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
  load_pdb();

  std::queue<std::string> *plan = IDA(); 

  if (plan != NULL){
    //Se consigio una solucion
    std::cout << "Plan encontrado: " << std::endl;
    int i;    
    int plan_size = plan->size();
    for (i =  0; i < plan_size; i++){ 
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
