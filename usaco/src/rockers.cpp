/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: rockers
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
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

ifstream fin ("rockers.in");
ofstream fout ("rockers.out");

int N, T, M;
int songs[30];

int main() {
    fin >> N >> T >> M;
    for (int i = 0; i < N; i++) {
        fin >> songs[i];
    }
    int maxSongs = 0;
    unsigned maxSongBits = (1 << N) - 1;
    for (unsigned songBits = 0; songBits <= maxSongBits; songBits++) {
        int restDisc = M;
        int restT = T;
        int currSongs = 0;
        for (int songIdx = 0; songIdx < N; songIdx++) {
            if (!((1 << songIdx) & songBits)) continue;
            int currSongT = songs[songIdx];
            while (restT < currSongT && restDisc) {
                restDisc--;
                restT = T;
            }
            if (!restDisc) break;
            restT -= currSongT;
            currSongs++;
        }
        if (currSongs > maxSongs) maxSongs = currSongs;
    }
    fout << maxSongs << endl;

    return 0;
}

