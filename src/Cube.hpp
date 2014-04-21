#include <iostream>     // std::cout, std::cin, std::endl
#include <queue>        // std::queue, std::push, std::pop, std::front
#include "extra.hpp"    // int_to_string
#ifndef CUBE_H
#define CUBE_H
class Cube {
/*
    Vamos a definir que un cubo tiene las siguientes caras,
    que comienzan de los colores:
    front  = white
    back   = yellow
    left   = orange
    right  = red
    top    = blue
    down   = green

           ____________
          /   /   /   /\
         /___/___/___/  \
        /   / T /   /\  /\
      L/___/___/___/  \/  \B
      /   /   /   /\  /\  /\
     /___/___/___/  \/  \/  \
     \   \   \   \  /\R /\  /
      \___\___\___\/  \/  \/
       \   \ F \   \  /\  /
        \___\___\___\/  \/D
         \   \   \   \  /
          \___\___\___\/

 */

  public:
      // Constructor
      Cube();

      Cube* clone();

      std::string to_string();
      std::string printable();

      bool equals(Cube* other);

      // operations on the cube
      void clock(char chr);
      void counter(char chr);
      void hundred(char chr);

      // for the PDB
      void next_corners(std::queue<Cube*>*);

  private:
      int *corners;
      int *edges;
      char last;

      int* switch_get(char chr);
      void switch_set(char chr, int* face);

      // getters and setters for the faces of the cube
      int* get_front();
      void set_front(int* face);
      int* get_back();
      void set_back(int* face);
      int* get_right();
      void set_right(int* face);
      int* get_left();
      void set_left(int* face);
      int* get_top();
      void set_top(int* face);
      int* get_down();
      void set_down(int* face);
};
#endif

