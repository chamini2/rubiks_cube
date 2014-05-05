#include <algorithm>
#include <iostream>     // std::cout, std::cin, std::endl
#include <sstream>
#include <string>
#include <cstdlib>
#include <math.h>

std::string int_to_string(int number);
std::string array_to_string(int *array, int size);
void array_swap(int &a, int &b);
void swap_entire_array(int n, int *array, int low, int quan);
int* inv_array(int* array, int size);
void array_reverse(int* array, int size);
void subarray_reverse(int *array, int i, int j);
int factorial(int n);
int* inv_array(int* array, int size);
int cubie_to_pos(int cubie);
int cubie_to_orien(int cubie);
int orien_to_axis(int orien);
int cubie_to_axis(int cubie);
int cubie_to_edge_orien(int cubie, int index);
int edge_orien_to_axis(int orien, int index, int pos);

void print_array(int *array, int n);
// Node* make_root_node(Cube* cube);

void error(std::string message, int line, std::string file);
int lex_perm(int* array, int n, int k);
