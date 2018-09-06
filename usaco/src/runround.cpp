/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: runround
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

int visited[10] = {0};
int numBuf[10] = {0};
int totalNum = 0;
set<unsigned long> numSet;

void DFS(int rest, int pos, int len) {
    if (rest == 0 && pos == 0) {
        unsigned long sum = 0;
        for (int i = 0; i < len; i++) {
            sum *= 10;
            sum += (unsigned long) numBuf[i];
        //     cout << numBuf[i];
        }
        // cout << endl;
        numSet.insert(sum);
    } else {
        if (numBuf[pos]) return;
        for (int i = 1; i <= 9; i++) {
            if (visited[i]) continue;
            numBuf[pos] = i;
            visited[i] = 1;
            DFS(rest - 1, (pos + i) % len, len);
            visited[i] = 0;
        }
        numBuf[pos] = 0;
    }
}

int main() {
    ofstream fout ("runround.out");
    ifstream fin ("runround.in");

    unsigned long M;
    fin >> M;
    for (int i = 1; i <= 9; i++) {
        DFS(i, 0, i);
    }
    for (set<unsigned long>::iterator itr = numSet.begin();
         itr != numSet.end(); ++itr) {
        if (*itr > M) {
            fout << *itr << endl;
            break;
        }
    }

    return 0;
}

