/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: lamps
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
#include <map>

using namespace std;

int N, C;
set<string> lampStateSet;
int lampState[110] = {0};
vector<int> onLamp, offLamp;

void eval(int step) {
    if (step == 1) {
        for (int i = 1; i <= N; i++) lampState[i] = (lampState[i] + 1) % 2;
    } else if (step == 2) {
        for (int i = 1; i <= N; i++) if (i % 2) lampState[i] = (lampState[i] + 1) % 2;
    } else if (step == 3) {
        for (int i = 1; i <= N; i++) if (i % 2 == 0) lampState[i] = (lampState[i] + 1) % 2;
    } else if (step == 4) {
        for (int i = 1; i <= N; i++) if (i % 3 == 1) lampState[i] = (lampState[i] + 1) % 2;
    }
}

void DFS(int rest) {
    if (rest == 0) {
        string result = "";
        for (int i = 1; i <= N; i++) result += '0' + lampState[i];
        lampStateSet.insert(result);
        // cout << result << endl;
    } else {
        for (int i = 1; i <= 4; i++) {
            // cout << i << endl;
            eval(i);
            DFS(rest - 1);
            eval(i);
            DFS(rest - 1);
        }
    }
}

int main() {
    ofstream fout ("lamps.out");
    ifstream fin ("lamps.in");

    fin >> N >> C;
    if (C > 4) C = 4;

    int on, off;
    while (true) {
        fin >> on;
        if (on == -1) break;
        onLamp.push_back(on);
    }
    while (true) {
        fin >> off;
        if (off == -1) break;
        offLamp.push_back(off);
    }

    // put on all lamps
    for (int i = 1; i <= N; i++) lampState[i] = 1;
    DFS(C);

    bool output = false;
    for (set<string>::iterator itr = lampStateSet.begin();
         itr != lampStateSet.end(); ++itr) {
        bool valid = true;
        for (vector<int>::iterator itr2 = onLamp.begin();
             itr2 != onLamp.end(); ++itr2) {
            if ((*itr)[*itr2 - 1] != '1') {
                valid = false;
                break;
            }
        }
        for (vector<int>::iterator itr2 = offLamp.begin();
             itr2 != offLamp.end(); ++itr2) {
            if ((*itr)[*itr2 - 1] != '0') {
                valid = false;
                break;
            }
        }
        if (valid) {
            fout << *itr << endl;
            output = true;
        }
    }
    
    if (!output) fout << "IMPOSSIBLE" << endl;

    return 0;
}

