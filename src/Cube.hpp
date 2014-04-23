#include <queue>        // std::queue, std::push, std::pop, std::front
#include <tuple>
#include "extra.hpp"    // int_to_string

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

        T = XY = A
        L = YZ = B
        F = XZ = C

////////////////////////////////////////

    cubie    X  orientation
    |_|_|_| |_| |_|_|_|_|
     A B C        0 - 7

    C -> goal orientation for all corners and eight edges

 */


    public:
        // Constructor
        Cube();
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

        int* get_corners();
        bool equals_corners(int *other);

    private:
        uint8_t *corners;
        uint8_t *edges;
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

        std::string color_face(int* face, char chr);
};
#endif
