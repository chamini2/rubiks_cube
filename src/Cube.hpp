#include <queue>        // std::queue, std::push, std::pop, std::front
#include <tuple>
#include "extra.hpp"    // int_to_string
#include "rank.hpp"

#ifndef CUBE_H
#define CUBE_H

class Cube {
/*
    Vamos a definir que un cubo tiene las siguientes caras,
    que comienzan de los colores:
        front = white
        back  = yellow
        left  = orange
        right = red
        top   = blue
        down  = green

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


    LTF:
        LT = X
        FT = Y
        LF = Z

        T = XY = C
        L = YZ = B
        F = XZ = A

////////////////////////////////////////

 */


    public:
        // Constructor
        Cube();
        Cube(int corners, int edges, char last);
        ~Cube();
        Cube* clone();

        std::string to_string();
        std::string corners_to_string();
        std::string edges_to_string();
        std::string printable();

        bool equals(Cube* other);

        // operations on the cube
        void clock(char face);
        void counter(char face);
        void hundred(char face);

        std::queue<Cube*>* succ();

        char get_last();
        int* get_corners();
        bool equals_corners(int *other);
        bool permutation_parity();
        bool corner_parity();
        bool valid();

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
        int sum_of_face(char face);


        std::string color_face(int* face, char chr);
};
#endif
