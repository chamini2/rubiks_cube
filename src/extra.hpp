#include <iostream>     // std::cout, std::cin, std::endl
#include <sstream>
#include <string>
#include <cstdlib>
#include <math.h>

std::string int_to_string(int number);
int factorial(int n);
int cubie_to_pos(int cubie);
int cubie_to_orien(int cubie);
int orien_to_axis(int orien);
void print_array(int *array, int n);
// Node* make_root_node(Cube* cube);

void error(std::string message, int line, std::string file);
