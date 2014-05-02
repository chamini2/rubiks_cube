#include <queue>        // std::queue, std::push, std::pop, std::front
#include <tuple>
#include "extra.hpp"    // int_to_string
#include "rank.hpp"

std::string last_to_str(int last);
int str_to_last(std::string last);

class Cube {
/*
    We will begin by defining that a cube has the following faces and colors:
        front = white
        back  = yellow
        right = red
        left  = orange
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


    Orientations:
        LT = X
        FT = Y
        LF = Z

        F = XZ = A = 0
        L = YZ = B = 1
        T = XY = C = 2

    ////////////////////////////////////////

    Last:
        -  -> clockwise
        +  -> counter-clockwise
        +  -> hundred-eighty degrees

        0  -> f+
        1  -> f-
        2  -> f|
        3  -> b+
        4  -> b-
        5  -> b|
        6  -> r+
        7  -> r-
        8  -> r|
        9  -> l+
        10 -> l-
        11 -> l|
        12 -> t+
        13 -> t-
        14 -> t|
        15 -> d+
        16 -> d-
        17 -> d|

    C -> goal orientation for all corners and eight edges
    B -> goal orientation for other 4 edges
 */


    public:
        // Constructor
        Cube();
        Cube(int pdb);
        Cube(int corners, int edges, int last);
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

        int get_last();
        int* get_corners();
        int* get_edges();
        bool equals_corners(int *other);
        bool permutation_parity();
        bool corner_parity();
        bool valid();

    private:
        int *corners;
        int *edges;
        int last;

        int* switch_get(char chr);
        void switch_set(char chr, int* face);

        // getters and setters for the faces of the cube
        int* get_face(int *face);
        void set_face(int *face, int* poss);

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
