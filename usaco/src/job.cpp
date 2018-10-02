/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: job
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

ifstream fin ("job.in");
ofstream fout ("job.out");

/*
 * TODO: Why the greedy policy is correct?
 */

int N, M1, M2;
int M1Vol[40] = {0};
int M2Vol[40] = {0};
int M1End[40] = {0};
int M2End[40] = {0};
int jobEndM1[1010] = {0};
int jobEndM2[1010] = {0};

int processM1() {
    int maxEnd = 0;
    for (int i = 0; i < N; i++) {
        int minEnd = 1000000000, minIdx;
        for (int j = 0; j < M1; j++) {
            int currEnd = M1Vol[j] + M1End[j];
            if (currEnd < minEnd) {
                minIdx = j;
                minEnd = currEnd;
            }
        }
        jobEndM1[i] = M1End[minIdx] = minEnd;
        if (minEnd > maxEnd) maxEnd = minEnd;
    }
    return maxEnd;
}

int processM2() {
    int maxEnd = 0;
    for (int i = 0; i < N; i++) {
        int minEnd = 1000000000, minIdx;
        for (int j = 0; j < M2; j++) {
            int currEnd = M2Vol[j] + M2End[j];
            if (currEnd < minEnd) {
                minIdx = j;
                minEnd = currEnd;
            }
        }
        jobEndM2[i] = M2End[minIdx] = minEnd;
        if (minEnd > maxEnd) maxEnd = minEnd;
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (ans < jobEndM1[i] + jobEndM2[N - i - 1]) {
            ans = jobEndM1[i] + jobEndM2[N - i - 1];
        }
    }
    return ans;
}

int main() {
    fin >> N >> M1 >> M2;
    for (int i = 0; i < M1; i++) {
        fin >> M1Vol[i];
    }
    for (int i = 0; i < M2; i++) {
        fin >> M2Vol[i];
    }
    fout << processM1() << " ";
    fout << processM2() << endl;

    return 0;
}

