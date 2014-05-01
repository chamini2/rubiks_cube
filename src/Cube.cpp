#include <algorithm>
#include "Cube.hpp"

Cube::Cube() {
    corners = new int[8];
    edges   = new int[12];

    corners[0] =   0;  // white  - blue  - orange
    corners[1] =   1;  // white  - blue  - red
    corners[2] =   2;  // yellow - blue  - red
    corners[3] =   3;  // yellow - blue  - orange
    corners[4] =   4;  // white  - green - orange
    corners[5] =   5;  // white  - green - red
    corners[6] =   6;  // yellow - green - red
    corners[7] =   7;  // yellow - green - orange

    edges[0]   =   0;  // blue   - white
    edges[1]   = 101;  // blue   - red
    edges[2]   =   2;  // blue   - yellow
    edges[3]   = 103;  // blue   - orange
    edges[4]   =   4;  // white  - orange
    edges[5]   =   5;  // white  - red
    edges[6]   =   6;  // yellow - red
    edges[7]   =   7;  // yellow - orange
    edges[8]   =   8;  // white  - green
    edges[9]   = 109;  // green  - red
    edges[10]  =  10;  // yellow - green
    edges[11]  = 111;  // green  - orange

    last = -1;
}

Cube::Cube(int corners, int edges, int last) {
    this->corners = unrank(8, corners);
    this->edges = unrank(12, edges);
    this->last = last;
}

void Cube::reset_last() {
    this->last = -1;
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

    face[0] = corners[0];
    face[1] = corners[3];
    face[2] = corners[2];
    face[3] = corners[1];

    face[4] = edges[2];
    face[5] = edges[1];
    face[6] = edges[0];
    face[7] = edges[3];

    return face;
}

void Cube::set_top(int *face) {
    corners[0] = face[0];
    corners[3] = face[1];
    corners[2] = face[2];
    corners[1] = face[3];

    edges[2]   = face[4];
    edges[1]   = face[5];
    edges[0]   = face[6];
    edges[3]   = face[7];
}

////////////////////////////////////////

int* Cube::get_down() {
    int* face = new int[8];

    face[0] = corners[7];
    face[1] = corners[4];
    face[2] = corners[5];
    face[3] = corners[6];

    face[4] = edges[8];
    face[5] = edges[9];
    face[6] = edges[10];
    face[7] = edges[11];

    return face;
}

void Cube::set_down(int *face) {
    corners[7] = face[0];
    corners[4] = face[1];
    corners[5] = face[2];
    corners[6] = face[3];

    edges[8]   = face[4];
    edges[9]   = face[5];
    edges[10]  = face[6];
    edges[11]  = face[7];
}

////////////////////////////////////////////////////////////////////////////////

int rotate_cubie(int cubie, char face) {
    int axis = cubie_to_orien(cubie);
    cubie = cubie_to_pos(cubie);
    int swapping[] = { 0, 0, 0};

    switch (face) {
        case 'f':
        case 'b':
            swapping[0] =   0;
            swapping[1] = 200;
            swapping[2] = 100;
            break;
        case 'r':
        case 'l':
            swapping[0] = 200;
            swapping[1] = 100;
            swapping[2] =   0;
            break;
        case 't':
        case 'd':
            swapping[0] = 100;
            swapping[1] =   0;
            swapping[2] = 200;
            break;
        default:
            std::string err_msg = "rotate_cubie | face = ";
            err_msg += face;
            error(err_msg, __LINE__, __FILE__);
            throw -1;
    }

    return cubie + swapping[axis];
}

////////////////////////////////////////////////////////////////////////////////

void Cube::clock(char face) {
    int* before;
    int after[8];
    std::string str = "-";

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

    last = str_to_last(face + str);
    delete[] before;
}

void Cube::counter(char face) {
    int* before;
    int after[8];
    std::string str = "+";

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

    last = str_to_last(face + str);
    delete[] before;
}

void Cube::hundred(char face) {
    int* before;
    int after[8];
    std::string str = "|";

    before = switch_get(face);

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

    switch_set(face, after);

    last = str_to_last(face + str);
    delete[] before;
}

////////////////////////////////////////////////////////////////////////////////

std::queue<Cube*>* Cube::succ() {
    std::queue<Cube*> *queue = new std::queue<Cube*>;
    Cube* cube;
    std::string last_str = last_to_str(last);
    char faces[] = {'f', 'b', 'r', 'l', 't', 'd'};

    for (int i = 0; i < 6; i += 2) {
        if (faces[i+1] != last_str.front()) {
            cube = this->clone();
            cube->clock(faces[i+1]);
            queue->push(cube);

            cube = this->clone();
            cube->counter(faces[i+1]);
            queue->push(cube);

            cube = this->clone();
            cube->hundred(faces[i+1]);
            queue->push(cube);

            if (faces[i] != last_str.front()) {
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

int Cube::get_last() {
    return last;
}

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

int tp(int n, int *P) {
    int p = 0;
    char v[n];
    int j=n;

    for(int i = 0; i < n; ++i) {
        v[i] = 0;
    }

    while(j--) {
        if(v[j]) {
            ++p;
        } else {
            int x = j;
            do {
                x = P[x];
                v[x] = 1;
            } while (x!=j);
        }
    }

    return p&1;
}

int Cube::sum_of_face(char face) {
    int n, h, v, sum = 0;
    int *handle = switch_get(face);

    switch(face) {
        case 'f':
        case 'b':
            n = 0;
            v = 2;
            h = 1;
            break;
        case 'r':
        case 'l':
            n = 1;
            v = 2;
            h = 0;
            break;
        case 't':
        case 'd':
            n = 2;
            v = 1;
            h = 0;
            break;
    }

    for (int i = 0; i < 4; ++i) {
        if (cubie_to_orien(handle[i]) == n) {
            sum += 0;
        } else if (i % 2 == 0) {
            if(cubie_to_orien(handle[i]) == v) {
                sum += 1;
            } else {
                sum += 2;
            }
        } else if (i % 2 != 0) {
            if(cubie_to_orien(handle[i]) == v) {
                sum += 2;
            } else {
                sum += 1;
            }
        }
    }

    delete[] handle;
    return sum;
}

bool Cube::corner_parity() {
    char faces[] = { 'f', 'b', 'r', 'l', 't', 'd' };
    int sum;
    bool isEven = true;

    for (int i = 0; i < 6; i+=2) {
        sum = 0;
        sum = sum_of_face(faces[i]);
        sum += sum_of_face(faces[i+1]);
        isEven = sum % 3 == 0 && isEven;
    }

    return isEven;
}

bool Cube::permutation_parity() {
    int array[20];

    for (int i = 0; i < 8; ++i) {
        array[i] = cubie_to_pos(corners[i]);
    }

    for (int i = 0; i < 12; ++i) {
        array[i+8] = cubie_to_pos(edges[i])+8;
    }

    return tp(20, array) == 0;
}

bool Cube::valid() {
    return corner_parity();
}


std::string last_to_str(int last) {
    std::string str;
    char faces[] = { 'f', 'b', 'r', 'l', 't', 'd' };

    switch (last % 3) {
        case 0:
            str = "+";
            break;
        case 1:
            str = "-";
            break;
        case 2:
            str = "|";
            break;
        case -1:
            return "  ";
        default:
            error("last_to_str | last % 3 = " + int_to_string(last % 3), __LINE__, __FILE__);
            throw -1;
    }

    return faces[last / 3] + str;
}

int str_to_last(std::string last) {
    int val;

    switch (last.front()) {
        case 'f':
            val = 0;
            break;
        case 'b':
            val = 3;
            break;
        case 'r':
            val = 6;
            break;
        case 'l':
            val = 9;
            break;
        case 't':
            val = 12;
            break;
        case 'd':
            val = 15;
            break;
        default:
            error("str_to_last | last.front() = " + last, __LINE__, __FILE__);
            throw -1;
    }

    switch (last.back()) {
        case '+':
            return val + 0;
        case '-':
            return val + 1;
        case '|':
            return val + 2;
        default:
            error("str_to_last | last.back() = " + last, __LINE__, __FILE__);
            throw -1;
    }
}
