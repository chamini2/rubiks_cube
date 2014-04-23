#include <algorithm>
#include "Cube.hpp"

Cube::Cube() {
    corners = new uint8_t[8];
    edges   = new uint8_t[12];

    corners[0] = 32; // white  - blue  - orange
    corners[1] = 33; // white  - blue  - red
    corners[2] = 34; // yellow - blue  - red
    corners[3] = 35; // yellow - blue  - orange
    corners[4] = 36; // white  - green - orange
    corners[5] = 37; // white  - green - red
    corners[6] = 38; // yellow - green - red
    corners[7] = 39; // yellow - green - orange

    edges[0]   = 32; // blue   - white
    edges[1]   = 65; // blue   - red
    edges[2]   = 34; // blue   - yellow
    edges[3]   = 67; // blue   - orange
    edges[4]   = 36; // white  - orange
    edges[5]   = 37; // white  - red
    edges[6]   = 38; // yellow - red
    edges[7]   = 39; // yellow - orange
    edges[8]   = 40; // white  - green
    edges[9]   = 73; // green  - red
    edges[10]  = 42; // yellow - green
    edges[11]  = 75; // green  - orange

    last = ' ';
}

Cube::~Cube() {
  delete[] corners;
  delete[] edges;
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

bool Cube::equals(Cube* other) {
    for (int i = 0; i < 8; ++i) {
        if (this->corners[i] != other->corners[i])
            return false;
    }

    for (int i = 0; i < 12; ++i) {
        if (this->edges[i] != other->edges[i])
            return false;
    }

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

int rotate_cubie(int cubie, char face) {
    int axis = cubie_to_orien(cubie);
    cubie = cubie_to_pos(cubie);

    switch (face) {
        // Axis C
        case 'f':
        case 'b':
            switch (axis) {
                case 0:
                    return cubie + 32;
                case 1:
                    return cubie + 128;
                case 2:
                    return cubie + 64;
                default:
                    std::string err_msg = "rotate_cubie | axis = ";
                    err_msg +=  axis;
                    error(err_msg, __LINE__, __FILE__);
                    throw -1;
            }
        // Axis B
        case 'r':
        case 'l':
            switch (axis) {
                case 0:
                    return cubie + 128;
                case 1:
                    return cubie + 64;
                case 2:
                    return cubie + 32;
                default:
                    std::string err_msg = "rotate_cubie | axis = ";
                    err_msg += axis;
                    error(err_msg, __LINE__, __FILE__);
                    throw -1;
            }
        // Axis A
        case 't':
        case 'd':
            switch (axis) {
                case 0:
                    return cubie + 64;
                case 1:
                    return cubie + 32;
                case 2:
                    return cubie + 128;
                default:
                    std::string err_msg = "rotate_cubie | axis = ";
                    err_msg += axis;
                    error(err_msg, __LINE__, __FILE__);
                    throw -1;
            }
        default:
            std::string err_msg = "rotate_cubie | face = ";
            err_msg += face;
            error(err_msg, __LINE__, __FILE__);
            throw -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Cube::clock(char face) {
    int* before;
    int after[8];

    before = switch_get(face);

    // corners
    after[0] = rotate_cubie(before[3], face);
    after[1] = rotate_cubie(before[0], face);
    after[2] = rotate_cubie(before[1], face);
    after[3] = rotate_cubie(before[2], face);

    // edges
    after[4] = rotate_cubie(before[7], face);
    after[5] = rotate_cubie(before[4], face);
    after[6] = rotate_cubie(before[5], face);
    after[7] = rotate_cubie(before[6], face);

    switch_set(face, after);

    last = face;
    delete[] before;
}

void Cube::counter(char face) {
    int* before;
    int after[8];

    before = switch_get(face);

    // corners
    after[0] = rotate_cubie(before[1], face);
    after[1] = rotate_cubie(before[2], face);
    after[2] = rotate_cubie(before[3], face);
    after[3] = rotate_cubie(before[0], face);

    // edges
    after[4] = rotate_cubie(before[5], face);
    after[5] = rotate_cubie(before[6], face);
    after[6] = rotate_cubie(before[7], face);
    after[7] = rotate_cubie(before[4], face);

    switch_set(face, after);

    last = face;
    delete[] before;
}

void Cube::hundred(char face) {
    int* before;
    int after[8];

    before = switch_get(face);

    // corners
    after[0] = rotate_cubie(before[2], face);
    after[1] = rotate_cubie(before[3], face);
    after[2] = rotate_cubie(before[0], face);
    after[3] = rotate_cubie(before[1], face);

    // edges
    after[4] = rotate_cubie(before[6], face);
    after[5] = rotate_cubie(before[7], face);
    after[6] = rotate_cubie(before[4], face);
    after[7] = rotate_cubie(before[5], face);

    switch_set(face, after);

    last = face;
    delete[] before;
}

////////////////////////////////////////////////////////////////////////////////

std::queue<Cube*>* Cube::succ() {
    std::queue<Cube*> *queue = new std::queue<Cube*>;
    Cube* cube;
    char faces[] = {'f', 'b', 'r', 'l', 't', 'd'};

    for (int i = 0; i < 6; i += 2) {
        if (faces[i+1] != last) {
            cube = this->clone();
            cube->clock(faces[i+1]);
            queue->push(cube);

            cube = this->clone();
            cube->counter(faces[i+1]);
            queue->push(cube);

            cube = this->clone();
            cube->hundred(faces[i+1]);
            queue->push(cube);

            if (faces[i] != last) {
                cube = this->clone();
                cube->clock(faces[i]);
                queue->push(cube);

                cube = this->clone();
                cube->counter(faces[i]);
                queue->push(cube);

                cube = this->clone();
                cube->hundred(faces[i]);
                queue->push(cube);
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
            std::string err_msg = "switch_get | chr = ";
            err_msg += chr;
            error(err_msg, __LINE__, __FILE__);
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
            std::string err_msg = "switch_get | chr = ";
            err_msg += chr;
            error(err_msg, __LINE__, __FILE__);
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

////////////////////////////////////////

int* Cube::get_corners() {
    int *array = new int[8];
    std::copy(this->corners, this->corners+8, array);

    return array;
}

bool Cube::equals_corners(int *other) {
    for (int i = 0; i < 8; ++i) {
        if (corners[i] != other[i]) {
            return false;
        }
    }
    return true;
}
