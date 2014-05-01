#include "rubik_solver.hpp"

void load_pdb(){
  return;
}

int h_value(Cube* c){
  return 4;
}

int g_value(Cube* c){
  return 1;
}

std::queue<int>* bounded_dfs(Cube* n, int g, int* t){  
  return new std::queue<int>;
}

void IDA(std::queue<int>* plan){
  Cube* n;
  int t = h_value(n); 
  int max_int = std::numeric_limits<int>::max();
  while (t != max_int) {
    plan = bounded_dfs(n,0,&t);
    if (plan != NULL){
      return;
    }    
  }
}

int main(int argc, char const *argv[]) {
  load_pdb();

  std::queue<int> *plan;
  IDA(plan);

  if (plan != NULL){
    std::cout << "Plan encontrado" << std::endl;
  }
  else {
    std::cout << "Plan no encontrado" << std::endl;
  }
  return 0;
}
