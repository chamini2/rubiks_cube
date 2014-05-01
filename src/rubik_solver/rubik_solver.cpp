#include "rubik_solver.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void load_pdb(){
  return;
}

int h_value(Cube* c){
  return 4;
}

bool is_goal(Cube *c){
  //Esta funcion podria tener una mejor implementacion
  if (c == NULL)
    return false;
  Cube *goal = new Cube; 
  if (goal->equals(c))
    return true;
  return false;
}

std::queue<int>* bounded_dfs(Cube* n, int g, int* t){  
  std::cout << "Current level for g = " << g << std::endl;
 
  if ((g + h_value(n)) > *t){
    *t = g + h_value(n);
    return NULL;    
  }
  
  std::queue<int> *plan = new std::queue<int>;

  if (is_goal(n)){
    //extract solution
    *t = g;
    int i;
    for (i = 0; i < 10 ; i++)   
      plan->push(i);
    return plan;
  }

  int new_t = std::numeric_limits<int>::max();

  std::queue<Cube*> *succ;
  succ = n->succ();
  
  int tmp;
  int succ_size = succ->size();
  for (tmp = 0; tmp < succ_size; tmp++){
    plan = bounded_dfs(succ->front(), g + 1 ,t);
    succ->pop();
    if (plan != NULL){
      new_t = std::min(new_t,*t);
      return plan;
    }
  }
  *t = new_t;
  return NULL;
}


Cube* generador_cubos_random(int levels){
  Cube *c = new Cube;
  int i;
  std::queue<Cube*> *succ;
  for (i = 0; i < levels; i++){
    succ = c->succ();
    int j;
    srand(time(NULL));
    int random_succesor = rand() % (succ->size() - 1);
    for (j = 0; j < random_succesor; j++){
      succ->pop();
    }
    c = succ->front();
  }
  std::cout << c->to_string() << std::endl;
  return c;
}

void IDA(std::queue<int>** plan){
  Cube* n = generador_cubos_random(10);
  int t = h_value(n); 
  int max_int = std::numeric_limits<int>::max();
  while (t != max_int) {
    *plan = bounded_dfs(n,0,&t);
    if (plan != NULL){
      return;
    }    
  }
}

int main(int argc, char const *argv[]) {
  load_pdb();

  std::queue<int> *plan;
  IDA(&plan);

  if (plan != NULL){
    std::cout << "Plan encontrado: " << std::endl;
    int i;    
    int plan_size = plan->size();
    for (i =  0; i < plan_size; i++){
      std::cout << plan->front() << " ";
      plan->pop();
    }
    std::cout << std::endl;
  }
  else {
    std::cout << "Plan no encontrado" << std::endl;
  }
  return 0;
}
