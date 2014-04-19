#include <iostream>     // std::cout, std::cin, std::endl
#include <queue>        // std::queue, std::push, std::pop, std::front
#include <string>       // std::string, std:to_string

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
     _____
    |_|_|_|
    |_|F|_|
    |_|_|_|

    Y
    |
    |____X
    /
   /
  Z

 */
public:
    // Constructor
    Cube();
    // Destructor
    ~Cube();

    Cube* clone();

    std::string to_string();

    int compare(Cube other);

    // operations on the "cube"
    int* front();
    void set_front(int*);
    int* back();
    void set_back(int*);
    int* right();
    void set_right(int*);
    int* left();
    void set_left(int*);
    int* top();
    void set_top(int*);
    int* down();
    void set_down(int*);

    void clock(char);
    void counter(char);
    void hundred(char);

    // for the PDB
    void next_corners(std::queue<Cube*>*);

private:
    int *corners;
    int *edges;
    char last;

    int* switch_get(char);
    void switch_set(char, int*);

};

Cube::Cube() {

    corners = new int [8];
    edges   = new int [12];

    corners[0] = 0; // white  - blue  - orange
    corners[1] = 1; // white  - blue  - red
    corners[2] = 2; // yellow - blue  - red
    corners[3] = 3; // yellow - blue  - orange
    corners[4] = 4; // white  - green - orange
    corners[5] = 5; // white  - green - red
    corners[6] = 6; // yellow - green - red
    corners[7] = 7; // yellow - green - orange

    edges[0]  = 0;  // blue   - white
    edges[1]  = 1;  // blue   - red
    edges[2]  = 2;  // blue   - yellow
    edges[3]  = 3;  // blue   - orange
    edges[4]  = 4;  // white  - orange
    edges[5]  = 5;  // white  - red
    edges[6]  = 6;  // yellow - red
    edges[7]  = 7;  // yellow - orange
    edges[8]  = 8;  // white  - green
    edges[9]  = 9;  // green  - red
    edges[10] = 10; // yellow - green
    edges[11] = 11; // green  - orange

    last = ' ';
}

Cube::~Cube() {
    delete[] corners;
    delete[] edges;
}

Cube::Cube* Cube::clone() {

    Cube* copy = new Cube;

    for (int i = 0; i < 8; ++i) {
        copy->corners[i] = this->corners[i];
    }

    for (int i = 0; i < 12; ++i) {
        copy->edges[i] = this->edges[i];
    }

    copy->last = this->last;

    return copy;
}

////////////////////////////////////////////////////////////////////////////////

int* Cube::front() {
    int* face = new int [8];

    face[0] = corners[0];
    face[1] = corners[1];
    face[2] = corners[5];
    face[3] = corners[4];

    face[4] = edges[0];
    face[5] = edges[5];
    face[6] = edges[8];
    face[7] = edges[4];

    return face;
}

void Cube::set_front(int *face) {
    corners[0] = face[0];
    corners[1] = face[1];
    corners[5] = face[2];
    corners[4] = face[3];

    edges[0]   = face[4];
    edges[5]   = face[5];
    edges[8]   = face[6];
    edges[4]   = face[7];
}

////////////////////////////////////////

int* Cube::back() {
    int* face = new int [8];

    face[0] = corners[2];
    face[1] = corners[3];
    face[2] = corners[7];
    face[3] = corners[6];

    face[4] = edges[2];
    face[5] = edges[7];
    face[6] = edges[10];
    face[7] = edges[6];

    return face;
}

void Cube::set_back(int *face) {
    corners[2] = face[0];
    corners[3] = face[1];
    corners[7] = face[2];
    corners[6] = face[3];

    edges[2]   = face[4];
    edges[7]   = face[5];
    edges[10]  = face[6];
    edges[6]   = face[7];
}

////////////////////////////////////////

int* Cube::right() {
    int* face = new int [8];

    face[0] = corners[1];
    face[1] = corners[2];
    face[2] = corners[6];
    face[3] = corners[5];

    face[4] = edges[1];
    face[5] = edges[6];
    face[6] = edges[9];
    face[7] = edges[5];

    return face;
}

void Cube::set_right(int *face) {
    corners[1] = face[0];
    corners[2] = face[1];
    corners[6] = face[2];
    corners[5] = face[3];

    edges[1]   = face[4];
    edges[6]   = face[5];
    edges[9]   = face[6];
    edges[5]   = face[7];
}

////////////////////////////////////////

int* Cube::left() {
    int* face = new int [8];

    face[0] = corners[3];
    face[1] = corners[0];
    face[2] = corners[4];
    face[3] = corners[7];

    face[4] = edges[3];
    face[5] = edges[4];
    face[6] = edges[11];
    face[7] = edges[7];

    return face;
}

void Cube::set_left(int *face) {
    corners[3] = face[0];
    corners[0] = face[1];
    corners[4] = face[2];
    corners[7] = face[3];

    edges[3]   = face[4];
    edges[4]   = face[5];
    edges[11]  = face[6];
    edges[7]   = face[7];
}

////////////////////////////////////////

int* Cube::top() {
    int* face = new int [8];

    face[0] = corners[3];
    face[1] = corners[2];
    face[2] = corners[1];
    face[3] = corners[0];

    face[4] = edges[2];
    face[5] = edges[1];
    face[6] = edges[0];
    face[7] = edges[3];

    return face;
}

void Cube::set_top(int *face) {
    corners[3] = face[0];
    corners[2] = face[1];
    corners[1] = face[2];
    corners[0] = face[3];

    edges[2]   = face[4];
    edges[1]   = face[5];
    edges[0]   = face[6];
    edges[3]   = face[7];
}

////////////////////////////////////////

int* Cube::down() {
    int* face = new int [8];

    face[0] = corners[4];
    face[1] = corners[5];
    face[2] = corners[6];
    face[3] = corners[7];

    face[4] = edges[8];
    face[5] = edges[9];
    face[6] = edges[10];
    face[7] = edges[11];

    return face;
}

void Cube::set_down(int *face) {
    corners[4] = face[0];
    corners[5] = face[1];
    corners[6] = face[2];
    corners[7] = face[3];

    edges[8]   = face[4];
    edges[9]   = face[5];
    edges[10]  = face[6];
    edges[11]  = face[7];
}

////////////////////////////////////////////////////////////////////////////////

void Cube::clock(char chr) {
    int* before;
    int after[8];

    before = switch_get(chr);

    // corners
    after[0] = before[3];
    after[1] = before[0];
    after[2] = before[1];
    after[3] = before[2];

    //edges
    after[4] = before[7];
    after[5] = before[4];
    after[6] = before[5];
    after[7] = before[6];

    switch_set(chr, after);

    last = chr;
    delete[] before;

}

void Cube::counter(char chr) {
    int* before;
    int after[8];

    before = switch_get(chr);

    // corners
    after[0] = before[1];
    after[1] = before[2];
    after[2] = before[3];
    after[3] = before[0];

    //edges
    after[4] = before[5];
    after[5] = before[6];
    after[6] = before[7];
    after[7] = before[4];

    switch_set(chr, after);

    last = chr;
    delete[] before;

}

void Cube::hundred(char chr) {
    int* before;
    int after[8];

    before = switch_get(chr);

    // corners
    after[0] = before[2];
    after[1] = before[3];
    after[2] = before[0];
    after[3] = before[1];

    //edges
    after[4] = before[6];
    after[5] = before[7];
    after[6] = before[4];
    after[7] = before[5];

    switch_set(chr, after);

    last = chr;
    delete[] before;

}

////////////////////////////////////////////////////////////////////////////////

void Cube::next_corners(std::queue<Cube*> *cubes) {
    Cube* cube;

    if (last != 'f' && last != 'b') {
        cube = this->clone();
        cube->clock('f');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('f');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('f');
        cubes->push(cube);
    }

    if (last != 'b') {
        cube = this->clone();
        cube->clock('b');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('b');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('b');
        cubes->push(cube);
    }

    if (last != 'r' && last != 'l') {
        cube = this->clone();
        cube->clock('r');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('r');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('r');
        cubes->push(cube);
    }

    if (last != 'l') {
        cube = this->clone();
        cube->clock('l');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('l');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('l');
        cubes->push(cube);
    }

    if (last != 't' && last != 'd') {
        cube = this->clone();
        cube->clock('t');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('t');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('t');
        cubes->push(cube);
    }

    if (last != 'd') {
        cube = this->clone();
        cube->clock('d');
        cubes->push(cube);

        cube = this->clone();
        cube->counter('d');
        cubes->push(cube);

        cube = this->clone();
        cube->hundred('d');
        cubes->push(cube);
    }

}

////////////////////////////////////////////////////////////////////////////////

int* Cube::switch_get(char chr) {

    switch (chr) {
        case 'f':
            return this->front();
        case 'b':
            return this->back();
        case 'r':
            return this->right();
        case 'l':
            return this->left();
        case 't':
            return this->top();
        case 'd':
            return this->down();
        default:
            throw -1;
    }
}

void Cube::switch_set(char chr, int* face) {

    switch (chr) {
        case 'f':
            return this->set_front(face);
        case 'b':
            return this->set_back(face);
        case 'r':
            return this->set_right(face);
        case 'l':
            return this->set_left(face);
        case 't':
            return this->set_top(face);
        case 'd':
            return this->set_down(face);
        default:
            throw -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string Cube::to_string() {
    std::string str = "corners\t";
    // std::cout << "corners\t";

    for (int i = 0; i < 8; ++i) {
        str += " " + std::to_string(this->corners[i]);
        // std::cout << " " << this->corners[i];
    }

    str += "\nedges\t";
    // std::cout << "\nedges\t";

    for (int i = 0; i < 12; ++i) {
        str += " " + std::to_string(this->edges[i]);
        // std::cout << " " << this->edges[i];
    }

    std::cout << std::endl << "---------------" << std::endl;

    return str + "\n";
    // return "";
}

int main(int argc, char const *argv[])
{
    std::queue<Cube*> cubes;
    Cube* cube = new Cube;

    cube->next_corners(&cubes);

    std::cout << "LEVEL 0\n" << cube->to_string() << "LEVEL 1\n";

    for (int i = 0; i < cubes.size(); ++i) {
        cube = cubes.front();
        cubes.pop();
        std::cout << cube->to_string();
    }

    return 0;
}
