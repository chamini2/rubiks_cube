#include "Cube.hpp"

Cube::Cube() {
    corners = new int[8];
    edges   = new int[12];

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

Cube* Cube::clone() {
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

// Change this operator depending on PDB or IDA*
bool Cube::equals(Cube* other) {
    // for corners PDB
    for (int i = 0; i < 8; ++i) {
        if (this->corners[i] != other->corners[i])
            return false;
    }

    // for (int i = 0; i < 12; ++i) {
    //     if (this->edges[i] != other->edges[i])
    //         return false;
    // }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

int* Cube::get_front() {
    int* face = new int[8];

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

int* Cube::get_back() {
    int* face = new int[8];

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

int* Cube::get_right() {
    int* face = new int[8];

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

int* Cube::get_left() {
    int* face = new int[8];

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

int* Cube::get_top() {
    int* face = new int[8];

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

int* Cube::get_down() {
    int* face = new int[8];

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

    // edges
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

    // edges
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

    // edges
    after[4] = before[6];
    after[5] = before[7];
    after[6] = before[4];
    after[7] = before[5];

    switch_set(chr, after);

    last = chr;
    delete[] before;
}

////////////////////////////////////////////////////////////////////////////////

void Cube::next_corners(std::queue<std::tuple<Cube*,int>> *cubes, int level) {
Cube* cube;     char faces[] = {'f','b','r','l','t','d'};

    for (int i = 0; i < 6; i += 2) {
        if (faces[i+1] != last) {

            cube = this->clone();
            cube->clock(faces[i+1]);
            cubes->push(std::make_tuple(cube,level+1));

            cube = this->clone();
            cube->counter(faces[i+1]);
            cubes->push(std::make_tuple(cube,level+1));

            cube = this->clone();
            cube->hundred(faces[i+1]);
            cubes->push(std::make_tuple(cube,level+1));

            if (faces[i] != last) {

                cube = this->clone();
                cube->clock(faces[i]);
                cubes->push(std::make_tuple(cube,level+1));

                cube = this->clone();
                cube->counter(faces[i]);
                cubes->push(std::make_tuple(cube,level+1));

                cube = this->clone();
                cube->hundred(faces[i]);
                cubes->push(std::make_tuple(cube,level+1));
            }
        }
    }
}

/*
 *  Dejo succ_cornes muy parecido a next_corners hasta que borremos el
 *  otro.
 */

std::queue<Cube*> Cube::succ_corners() {
    std::queue<Cube*> queue;
    Cube* cube;
    char faces[] = {'f', 'b', 'r', 'l', 't', 'd'};

    for (int i = 0; i < 6; i += 2) {
        if (faces[i+1] != last) {
            cube = this->clone();
            cube->clock(faces[i+1]);
            queue.push(cube);

            cube = this->clone();
            cube->counter(faces[i+1]);
            queue.push(cube);

            cube = this->clone();
            cube->hundred(faces[i+1]);
            queue.push(cube);

            if (faces[i] != last) {
                cube = this->clone();
                cube->clock(faces[i]);
                queue.push(cube);

                cube = this->clone();
                cube->counter(faces[i]);
                queue.push(cube);

                cube = this->clone();
                cube->hundred(faces[i]);
                queue.push(cube);
            }
        }
    }
    return queue;
}

///////////////////////////////////////////////////////////////////////////////

int* Cube::switch_get(char chr) {
    switch (chr) {
        case 'f':
            return this->get_front();
        case 'b':
            return this->get_back();
        case 'r':
            return this->get_right();
        case 'l':
            return this->get_left();
        case 't':
            return this->get_top();
        case 'd':
            return this->get_down();
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
    return this->corners_to_string() + this->edges_to_string();
}

std::string Cube::corners_to_string() {
    std::string str = "";

    for (int i = 0; i < 8; ++i) {
        str += " " + int_to_string(this->corners[i]);
    }

    return str;
}

std::string Cube::edges_to_string() {
    std::string str = "";

    for (int i = 0; i < 12; ++i) {
        str += " " + int_to_string(this->edges[i]);
    }

    return str;
}

std::string Cube::printable() {
    std::string str = "corners\t";

    for (int i = 0; i < 8; ++i) {
        str += " " + int_to_string(this->corners[i]);
    }

    str += "\nedges\t";

    for (int i = 0; i < 12; ++i) {
        str += " " + int_to_string(this->edges[i]);
    }

    return str + "\n";
}
