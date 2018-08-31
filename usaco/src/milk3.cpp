/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: milk3
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

int AVol, BVol, CVol;
// A-B:0, A-C:1, B-A:2, B-C:3, C-A:4, C-B:5
int visited[21][21][21][6];
class State {
public:
    int A, B, C;
    State(int _A, int _B, int _C): A(_A), B(_B), C(_C) {}
};
queue<State> bfsQ;
set<int> result;

void BFS() {
    bfsQ.push(State(0, 0, CVol));
    while (!bfsQ.empty()) {
        State s = bfsQ.front();
        bfsQ.pop();
        // initial state is a trivial solution
        if (s.A == 0) {
            result.insert(s.C);
        }

            if (!visited[s.A][s.B][s.C][0]) {
                int delta = s.A < BVol - s.B ? s.A : BVol - s.B;
                if (delta)
                    bfsQ.push(State(s.A - delta, s.B + delta, s.C));
            }
            if (!visited[s.A][s.B][s.C][1]) {
                int delta = s.A < CVol - s.C ? s.A : CVol - s.C;
                if (delta)
                    bfsQ.push(State(s.A - delta, s.B, s.C + delta));
            }
            if (!visited[s.A][s.B][s.C][2]) {
                int delta = s.B < AVol - s.A ? s.B : AVol - s.A;
                if (delta)
                    bfsQ.push(State(s.A + delta, s.B - delta, s.C));
            }
            if (!visited[s.A][s.B][s.C][3]) {
                int delta = s.B < CVol - s.C ? s.B : CVol - s.C;
                if (delta)
                    bfsQ.push(State(s.A, s.B - delta, s.C + delta));
            }
            if (!visited[s.A][s.B][s.C][4]) {
                int delta = s.C < AVol - s.A ? s.C : AVol - s.A;
                if (delta)
                    bfsQ.push(State(s.A + delta, s.B, s.C - delta));
            }
            if (!visited[s.A][s.B][s.C][5]) {
                int delta = s.C < BVol - s.B ? s.C : BVol - s.B;
                if (delta)
                    bfsQ.push(State(s.A, s.B + delta, s.C - delta));
            }

        for (int i = 0; i < 6; i++) {
            visited[s.A][s.B][s.C][i] = 1;
        }
    }
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");

    fin >> AVol >> BVol >> CVol;
    BFS();
    int mark = 0;
    for (set<int>::iterator it = result.begin(); it != result.end(); ++it) {
        if (mark) fout << " ";
        fout << *it;
        mark++;
    }
    fout << endl;

    return 0;
}

