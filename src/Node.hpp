#ifndef NODE_HPP
#define NODE_HPP

#include "Cube.hpp"

class Node {
    public:
        Node(Cube* cube, Cube* parent, int level, int action);

    private:
        Cube* cube;
        Cube* parent;
        int level;
        int action;
};

#endif
