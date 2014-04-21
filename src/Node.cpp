#include "Node.hpp"

// Constructores de nodos

Node::Node(Cube* cube, Cube* parent, int level, int action) {
    this->cube = cube;
    this->level = level;
    this->action = action;
}
