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

    // The set of edges is divided in two sets:

    // A set of 7 edges with 12!/5! * 2^7 possible elements
    edges[0]   =   0;  // blue   - white
    edges[1]   = 101;  // blue   - red
    edges[2]   =   2;  // blue   - yellow
    edges[3]   = 103;  // blue   - orange
    edges[4]   =   4;  // white  - orange
    edges[5]   =   5;  // white  - red
    edges[6]   =   6;  // yellow - red

    // A set of 5 edges with 12!/7! * 2^7 possible elements
    edges[7]   =   7;  // yellow - orange
    edges[8]   =   8;  // white  - green
    edges[9]   = 109;  // green  - red
    edges[10]  =  10;  // yellow - green
    edges[11]  = 111;  // green  - orange

    last = -1;
}

Cube::Cube(int pdb) {

    corners = new int[8];
    edges   = new int[12];

    corners[0] = 0;  // white  - blue  - orange
    corners[1] = 1;  // white  - blue  - red
    corners[2] = 2;  // yellow - blue  - red
    corners[3] = 3;  // yellow - blue  - orange
    corners[4] = 4;  // white  - green - orange
    corners[5] = 5;  // white  - green - red
    corners[6] = 6;  // yellow - green - red
    corners[7] = 7;  // yellow - green - orange


    // The set of edges is divided in two sets:

    switch (pdb) {
        case 1:
            // A set of 7 edges with 12!/5! * 2^7 possible elements
            edges[0]  =   0;  // blue   - white
            edges[1]  = 101;  // blue   - red
            edges[2]  =   2;  // blue   - yellow
            edges[3]  = 103;  // blue   - orange
            edges[4]  =   4;  // white  - orange
            edges[5]  =   5;  // white  - red
            edges[6]  =   6;  // yellow - red

            // These elements are filled with -1 given that their values are
            // irrelevant
            edges[7]  = -1;  // yellow - orange
            edges[8]  = -1;  // white  - green
            edges[9]  = -1;  // green  - red
            edges[10] = -1;  // yellow - green
            edges[11] = -1;  // green  - orange

            break;
        case 2:
            // These elements are filled with -1 given that their values are
            // irrelevant
            edges[0]  = -1;  // blue   - white
            edges[1]  = -1;  // blue   - red
            edges[2]  = -1;  // blue   - yellow
            edges[3]  = -1;  // blue   - orange
            edges[4]  = -1;  // white  - orange
            edges[5]  = -1;  // white  - red
            edges[6]  = -1;  // yellow - red

            // A set of 5 edges with 12!/7! * 2^7 possible elements
            edges[7]  =   7;  // yellow - orange
            edges[8]  =   8;  // white  - green
            edges[9]  = 109;  // green  - red
            edges[10] =  10;  // yellow - green
            edges[11] = 111;  // green  - orange

            break;
        default:
            std::string err_msg = "Cube not initialized ";
            error(err_msg, __LINE__, __FILE__);
            throw -1;
    }

    last = -1;
}

Cube::Cube(int corners, int edges, int last) {
    this->corners = unrank(8, corners, 8, 3);
    this->edges = unrank(12, edges, 7, 2);
    this->last = last;
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

int* Cube::get_face(int *face) {
    int *face_res = new int[8];
    int orien_aux[8];
    int corners_pos[8];
    int edges_pos[12];
    int *corners_inv;
    int *edges_inv;

    // gets all positions
    for (int i = 0; i < 8; ++i) {
        corners_pos[i] = cubie_to_pos(corners[i]);
    }
    for (int i = 0; i < 12; ++i) {
        edges_pos[i] = cubie_to_pos(edges[i]);
    }
    corners_inv = inv_array(corners_pos, 8);
    edges_inv   = inv_array(edges_pos, 12);

    // gets all orientations
    for (int i = 0; i < 4; ++i) {
        orien_aux[i] = cubie_to_axis(corners[corners_inv[face[i]]]);
    }
    for (int i = 4; i < 8; ++i) {
        orien_aux[i] = cubie_to_axis(edges[edges_inv[face[i]]]);
    }

    // returns positions and orientations together
    face_res[0] = corners_inv[face[0]] + orien_aux[0];
    face_res[1] = corners_inv[face[1]] + orien_aux[1];
    face_res[2] = corners_inv[face[2]] + orien_aux[2];
    face_res[3] = corners_inv[face[3]] + orien_aux[3];

    face_res[4] = edges_inv[face[4]] + orien_aux[4];
    face_res[5] = edges_inv[face[5]] + orien_aux[5];
    face_res[6] = edges_inv[face[6]] + orien_aux[6];
    face_res[7] = edges_inv[face[7]] + orien_aux[7];

    delete[] corners_inv;
    delete[] edges_inv;

    return face_res;
}

void Cube::set_face(int* face, int* poss) {
    int pos_aux[8], orien_aux[8];

    for (int i = 0; i < 8; ++i) {
        pos_aux[i]   = cubie_to_pos(face[i]);
        orien_aux[i] = cubie_to_axis(face[i]);
    }

    corners[pos_aux[0]] = poss[0] + orien_aux[0];
    corners[pos_aux[1]] = poss[1] + orien_aux[1];
    corners[pos_aux[2]] = poss[2] + orien_aux[2];
    corners[pos_aux[3]] = poss[3] + orien_aux[3];

    edges[pos_aux[4]]   = poss[4] + orien_aux[4];
    edges[pos_aux[5]]   = poss[5] + orien_aux[5];
    edges[pos_aux[6]]   = poss[6] + orien_aux[6];
    edges[pos_aux[7]]   = poss[7] + orien_aux[7];
}

////////////////////////////////////////////////////////////////////////////////

int* Cube::get_front() {
    int face[8] = { 0, 1, 5, 4,     // corners
                    0, 5, 8, 4 };   // edges
    return get_face(face);
}

void Cube::set_front(int *face) {
    int positions[8] = { 0, 1, 5, 4,    // corners
                         0, 5, 8, 4 };  // edges
    set_face(face, positions);
}

////////////////////////////////////////

int* Cube::get_back() {
    int face[8] = {2, 3, 7, 6,      // corners
                   2, 7, 10, 6 };   // edges
    return get_face(face);
}

void Cube::set_back(int *face) {
    int positions[8] = { 2, 3, 7, 6,    // corners
                         2, 7, 10, 6 }; // edges
    set_face(face, positions);
}

////////////////////////////////////////

int* Cube::get_right() {
    int face[8] = { 1, 2, 6, 5,     // corners
                    1, 6, 9, 5 };   // edges
    return get_face(face);
}

void Cube::set_right(int *face) {
    int positions[8] = { 1, 2, 6, 5,    // corners
                         1, 6, 9, 5 };  // edges
    set_face(face, positions);
}

////////////////////////////////////////

int* Cube::get_left() {
    int face[8] = { 3, 0, 4, 7,     // corners
                    3, 4, 11, 7 };  // edges
    return get_face(face);
}

void Cube::set_left(int *face) {
    int positions[8] = { 3, 0, 4, 7,    // corners
                         3, 4, 11, 7 }; // edges
    set_face(face, positions);
}

////////////////////////////////////////

int* Cube::get_top() {
    int face[8] = { 0, 3, 2, 1,     // corners
                    2, 1, 0, 3 };   // edges
    return get_face(face);
}

void Cube::set_top(int *face) {
    int positions[8] = { 0, 3, 2, 1,    // corners
                         2, 1, 0, 3 };  // edges
    set_face(face, positions);
}

////////////////////////////////////////

int* Cube::get_down() {
    int face[8] = { 7, 4, 5, 6,     // corners
                    8, 9, 10, 11 }; // edges
    return get_face(face);
}

void Cube::set_down(int *face) {
    int positions[8] = { 7, 4, 5, 6,    // corners
                         8, 9, 10, 11 };// edges
    set_face(face, positions);
}

////////////////////////////////////////////////////////////////////////////////

int rotate_cubie(int cubie, char face) {
    if (cubie >= 0) {
        int orien = cubie_to_orien(cubie);
        int swapping[] = { 0, 0, 0 };

        cubie = cubie_to_pos(cubie);

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

        return cubie + swapping[orien];
    } else {
        return cubie;
    }
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
        if (this->corners[i] < 100) {
            str += "   " + int_to_string(this->corners[i]);
        } else {
            str += " " + int_to_string(this->corners[i]);
        }
    }

    return str;
}

std::string Cube::edges_to_string() {
    std::string str = "";

    for (int i = 0; i < 12; ++i) {
        if (this->edges[i] < 10) {
            str += "   " + int_to_string(this->edges[i]);
        } else if (this->edges[i] < 100) {
            str += "  " + int_to_string(this->edges[i]);
        } else {
            str += " " + int_to_string(this->edges[i]);
        }
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

int* Cube::get_edges() {
    int *array = new int[12];
    std::copy(this->edges, this->edges+12, array);

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
    int n, v, sum = 0;
    int *handle = switch_get(face);

    switch(face) {
        case 'f':
        case 'b':
            n = 0;
            v = 2;
            break;
        case 'r':
        case 'l':
            n = 1;
            v = 2;
            break;
        case 't':
        case 'd':
            n = 2;
            v = 1;
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
