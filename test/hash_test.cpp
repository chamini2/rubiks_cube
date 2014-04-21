#include "hash_test.hpp"

HashTable* ht = new HashTable();
int elementos_prueba;

void popular(){
  std::queue<Cube*> cubes;
  Cube* cube = new Cube;
  
  cube->next_corners(&cubes);  
  elementos_prueba = cubes.size();
  int t  = cubes.size();
  for (int i = 0; i < t; ++i) {
    cube = cubes.front();
    cubes.pop();
    ht->insert(cube);
  }
  std::cout << "Insertados " << elementos_prueba << " cubos en la tabla de hash." << std::endl;
}

void probar(){
  std::queue<Cube*> cubes;
  Cube* cube = new Cube;

  cube->next_corners(&cubes);

  std::cout << "Se generaron los mismos cubos para probar si todos estan contenidos." << std::endl;
  std::cout << cubes.size() << " cubos generados para probar." << std::endl;
    
  int counter = 0;    
  int t = cubes.size();
  for (int i = 0; i < t; i++) {
    cube = cubes.front();
    cubes.pop();     
    if (ht->contains(cube))	  
      counter++;
    else
      std::cout << "Falta un cubo: " << cube->to_string() << std::endl;
  }
  
  std::cout << "De los generados hay " << counter << " cubos insertados." << std::endl;
  
  std::cout << "Probando si hay otros cubos insertados" << std::endl;
  for (int i = 0 ; i < 5 ; i ++)
    if (ht->contains(new Cube)){
      std::cout << "Encontrado cubo que no deberia estar." << std::endl;
      return;
    }
  std::cout << "Prueba terminada sin cubos que no deberian estar" << std::endl;
}
  
int main(int argc, char const *argv[])
{
  popular();
  probar();
  return 0;
}
