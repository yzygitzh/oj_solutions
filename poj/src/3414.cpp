/*
 * POJ 3414 - Pots
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int A, B, C;
int visited[110][110];

class Action {
public:
    string actionType;
    int subject;
    Action(string _actionType, int _subject)
        :actionType(_actionType), subject(_subject) {}
};

class State {
public:
    int vol1, vol2, steps;
    State(int _vol1, int _vol2, int _steps)
        :vol1(_vol1), vol2(_vol2), steps(_steps) {}
};

vector<Action> bfs() {
    memset(visited, 0, sizeof(visited));
    visited[0][0] = 1;
    queue<pair<vector<Action>, State> > bfsQ;
    bfsQ.push(make_pair(vector<Action>(), State(0, 0, 0)));
    while (!bfsQ.empty()) {
        vector<Action> actionSeq = bfsQ.front().first;
        int vol1 = bfsQ.front().second.vol1;
        int vol2 = bfsQ.front().second.vol2;
        int steps = bfsQ.front().second.steps;
        bfsQ.pop();
        if (vol1 == C || vol2 == C) return actionSeq;
        // FILL
        if (!visited[A][vol2]) {
            visited[A][vol2] = 1;
            bfsQ.push(make_pair(actionSeq, State(A, vol2, steps + 1)));
            bfsQ.back().first.push_back(Action("FILL", 1));
        }
        if (!visited[vol1][B]) {
            visited[vol1][B] = 1;
            bfsQ.push(make_pair(actionSeq, State(vol1, B, steps + 1)));
            bfsQ.back().first.push_back(Action("FILL", 2));
        }
        // DROP
        if (!visited[0][vol2]) {
            visited[0][vol2] = 1;
            bfsQ.push(make_pair(actionSeq, State(0, vol2, steps + 1)));
            bfsQ.back().first.push_back(Action("DROP", 1));
        }
        if (!visited[vol1][0]) {
            visited[vol1][0] = 1;
            bfsQ.push(make_pair(actionSeq, State(vol1, 0, steps + 1)));
            bfsQ.back().first.push_back(Action("DROP", 2));
        }
        // POUR
        int AtoB = min(vol1, B - vol2);
        if (!visited[vol1 - AtoB][vol2 + AtoB]) {
            visited[vol1 - AtoB][vol2 + AtoB] = 1;
            bfsQ.push(make_pair(actionSeq, State(vol1 - AtoB, vol2 + AtoB, steps + 1)));
            bfsQ.back().first.push_back(Action("POUR", 1));
        }
        int BtoA = min(vol2, A - vol1);
        if (!visited[vol1 + BtoA][vol2 - BtoA]) {
            visited[vol1 + BtoA][vol2 - BtoA] = 1;
            bfsQ.push(make_pair(actionSeq, State(vol1 + BtoA, vol2 - BtoA, steps + 1)));
            bfsQ.back().first.push_back(Action("POUR", 2));
        }
    }
    return vector<Action>();
}

int main() {
    cin >> A >> B >> C;
    vector<Action> actionSeq = bfs();
    if (actionSeq.size() == 0) {
        cout << "impossible" << endl;
    } else {
        cout << actionSeq.size() << endl;
        for (vector<Action>::iterator itr = actionSeq.begin();
             itr != actionSeq.end(); ++itr) {
            cout << itr->actionType << "(" << itr->subject;
            if (itr->actionType == "POUR") {
                cout << "," << 3 - itr->subject;
            }
            cout << ")" << endl;
        }
    }
    return 0;
}

