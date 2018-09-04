/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: holstein
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

int V, G;
int vit[30];
int feed[20][30];

int feedSelected[20] = {0};
int feedSum[30] = {0};
int minScoop = 20;
int currentScoop;

int feedId[20] = {0};

void DFS(int rest, int idx) {
    if (rest > G - idx) {
        // too few scoops to choose
        return;
    } else if (rest == 0) {
        // see if meeting requirement
        bool valid = true;
        for (int i = 0; i < V; i++) {
            if (feedSum[i] < vit[i]) {
                valid = false;
                break;
            }
        }
        // cout << valid << endl;
        // if (valid) cout << currentScoop << endl;
        if (valid && currentScoop < minScoop) {
            minScoop = currentScoop;
            int scoopNum = 0;
            for (int i = 0; i < G; i++) {
                if (feedSelected[i]) {
                    feedId[scoopNum++] = i + 1;
                }
            }
        }
    } else {
        // first try w/ current scoop
        for (int i = 0; i < V; i++) feedSum[i] += feed[idx][i];
        feedSelected[idx] = 1;
        DFS(rest - 1, idx + 1);
        // next try w/o current scoop
        for (int i = 0; i < V; i++) feedSum[i] -= feed[idx][i];
        feedSelected[idx] = 0;
        DFS(rest, idx + 1);
    }
}

int main() {
    ofstream fout ("holstein.out");
    ifstream fin ("holstein.in");

    fin >> V;
    for (int i = 0; i < V; i++) fin >> vit[i];
    fin >> G;
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < V; j++) {
            fin >> feed[i][j];
        }
    }

    for (int i = 1; i <= G; i++) {
        currentScoop = i;
        // cout << currentScoop << endl;
        DFS(i, 0);
        if (minScoop == currentScoop) {
            fout << minScoop;
            for (int j = 0; j < minScoop; j++) {
                fout << " " << feedId[j];
            }
            fout << endl;
            break;
        }
    }

    return 0;
}

