/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: frac1
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>

using namespace std;

int N;

int gcd(int x, int y) {
    if (x < y) return gcd(y, x);
    if (y == 0 || x == y) return x;
    if (!(x % y)) return y;
    return gcd(y, x % y);
}

class Frac {
public:
    int up, down;
    Frac(int _up, int _down) {
        int g = gcd(_up, _down);
        this->up = _up / g;
        this->down = _down / g;
    }
    bool operator<(const Frac& f) const {
        return this->up * f.down < f.up * this->down;
    }
};

set<Frac> fracSet;

int main() {
    ofstream fout ("frac1.out");
    ifstream fin ("frac1.in");

    fin >> N;

    fracSet.insert(Frac(0, 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            fracSet.insert(Frac(j, i));
        }
    }

    for (set<Frac>::iterator itr = fracSet.begin();
         itr != fracSet.end(); ++itr) {
        fout << (*itr).up << "/" << (*itr).down << endl;
    }

    return 0;
}

