/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: transform
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
char origin_pattern[20][20];
char target_pattern[20][20];
char transform_pattern[20][20];

bool check_equal() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (target_pattern[i][j] != transform_pattern[i][j]) {
                return false;
            }
        }
    }
    return true;
}

struct Pos {
    float x;
    float y;
};

struct Pos transform_90(Pos origin_pos) {
    Pos ret;
    ret.x = origin_pos.y;
    ret.y = -origin_pos.x;
    return ret;
}

struct Pos transform_180(Pos origin_pos) {
    Pos ret;
    ret.x = -origin_pos.x;
    ret.y = -origin_pos.y;
    return ret;
}

struct Pos transform_270(Pos origin_pos) {
    Pos ret;
    ret.x = -origin_pos.y;
    ret.y = origin_pos.x;
    return ret;
}

struct Pos reflection(Pos origin_pos) {
    Pos ret;
    ret.x = -origin_pos.x;
    ret.y = origin_pos.y;
    return ret;
}

void transform_by_id(int id) {
    float origin_val = (float)(N - 1) / 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Pos origin_pos;
            origin_pos.y = origin_val - (float)i;
            origin_pos.x = (float)j - origin_val;
            Pos target_pos;
            if (id == 1) target_pos = transform_90(origin_pos);
            else if (id == 2) target_pos = transform_180(origin_pos);
            else if (id == 3) target_pos = transform_270(origin_pos);
            else if (id == 4) target_pos = reflection(origin_pos);
            else if (id == 5) target_pos = transform_90(reflection(origin_pos));
            else if (id == 6) target_pos = transform_180(reflection(origin_pos));
            else if (id == 7) target_pos = transform_270(reflection(origin_pos));
            else if (id == 8) target_pos = origin_pos;
            transform_pattern[int(origin_val - target_pos.y)]
                             [int(target_pos.x + origin_val)] = origin_pattern[i][j];
        }
    }
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> origin_pattern[i];
    }
    for (int i = 0; i < N; i++) {
        fin >> target_pattern[i];
    }

    for (int i = 1; i <= 8; i++) {
        transform_by_id(i);
        if (check_equal()) {
            if (i <= 4) fout << i;
            else if (i <= 7) fout << 5;
            else fout << 6;
            fout << endl;
            return 0;
        }
    }
    fout << 7 << endl;

    return 0;
}

