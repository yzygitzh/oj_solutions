/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: theme
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
#include <utility>

using namespace std;

/*
 * Used suffix array.
 * Standard solution is a really simple O(N^2) DP...
 */

ifstream fin ("theme.in");
ofstream fout ("theme.out");

const int bigLen = 5010 + 4096;
int N;
int seq[bigLen] = {0};
int rankArray[bigLen] = {0};
int newRankArray[bigLen] = {0};
int sa[bigLen] = {0}; // rankArray -> pos
int newSa[bigLen] = {0};
int h[bigLen] = {0};

int currLen;

class CompareBySeq {
public:
    bool operator() (const int &a, const int &b) const {
        if (a >= N) return true;
        if (b >= N) return false;
        return seq[a] < seq[b];
    }
} compareBySeq; 

class CompareByrankArrayPair {
public:
    bool operator() (const int &a, const int &b) const {
        if (a >= N) return true;
        if (b >= N) return false;
        if (rankArray[a] < rankArray[b]) return true;
        if (rankArray[a] > rankArray[b]) return false;
        // rankArray[a] == rankArray[b]
        if (a + currLen >= N) return true;
        if (b + currLen >= N) return false;
        return rankArray[a + currLen] < rankArray[b + currLen];
    }
} compareByrankArrayPair; 

void buildSA() {
    // get sa(1)
    for (int i = 0; i < N; i++) {
        newSa[i] = i;
    }
    sort(newSa, newSa + N, compareBySeq);
    memcpy(sa, newSa, sizeof(sa));
    int p = 0;

    // get init rankArray
    for (int i = 0; i < N; i++) {
        rankArray[sa[i]] = p;
        if (i + 1 < N && seq[sa[i]] != seq[sa[i + 1]]) p++;
    }

    /*
    cout << 1 << endl;
    for (int i = 0; i <= N; i++) {
        cout << rankArray[i] << " ";
    }
    cout << endl;
    */

    currLen = 1;
    while (currLen < N) {
        // get sa(2*n)
        for (int i = 0; i < N; i++) {
            newSa[i] = i;
        }
        sort(newSa, newSa + N, compareByrankArrayPair);
        memcpy(sa, newSa, sizeof(sa));

        // get new rankArray
        p = 0;
        for (int i = 0; i < N; i++) {
            newRankArray[sa[i]] = p;
            if (i + 1 < N &&
                (rankArray[sa[i]] != rankArray[sa[i + 1]] ||
                 rankArray[sa[i] + currLen] != rankArray[sa[i + 1] + currLen])) {
                p++;
            }
        }
        memcpy(rankArray, newRankArray, sizeof(int) * N);

        /*
        cout << 2 * currLen << endl;
        for (int i = 0; i <= N; i++) {
            cout << rankArray[i] << " ";
        }
        cout << endl;
        */

        currLen *= 2;
    }
}

int getMax(int a, int b) {
    return a > b ? a : b;
}

void buildH() {
    for (int i = 0; i < N; i++) {
        if (rankArray[i] + 1 == N) continue;
        int j = sa[rankArray[i] + 1];
        while(seq[i + h[rankArray[i]]] == seq[j + h[rankArray[i]]]) {
            h[rankArray[i]]++;
        }
        // update next (in sa) element's h
        h[rankArray[i + 1]] = getMax(h[rankArray[i]] - 1, 0);
    }
}

bool findAns(int k) {
    // k-length non-intersect themes exist
    int minSuffix = -1, maxSuffix = -1;
    for (int i = 0; i < N - 1; i++) {
        if (h[i] >= k) {
            if (minSuffix < 0) {
                minSuffix = maxSuffix = sa[i];
            }
            if (minSuffix > sa[i]) minSuffix = sa[i];
            if (minSuffix > sa[i + 1]) minSuffix = sa[i + 1];
            if (maxSuffix < sa[i]) maxSuffix = sa[i];
            if (maxSuffix < sa[i + 1]) maxSuffix = sa[i + 1];
            if (minSuffix + k < maxSuffix) return true;
        } else {
            minSuffix = maxSuffix = -1;
        }
    }
    return false;
}

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> seq[i];
        if (i > 0) seq[i - 1] = seq[i] - seq[i - 1];
    }
    for (int i = N - 1; i < bigLen; i++) {
        seq[i] = -100;
        rankArray[i] = -1;
    }
    N -= 1;

    buildSA();

    /*
    for (int i = 0; i < N; i++) {
        cout << rankArray[i] << " ";
    }
    cout << endl;
    */

    buildH();

    int minLen = 4, maxLen = N;
    while (minLen + 1 < maxLen) {
        int mid = (minLen + maxLen) / 2;
        if (findAns(mid)) minLen = mid;
        else maxLen = mid;
    }

    if (findAns(maxLen)) fout << maxLen + 1 << endl;
    else if (findAns(minLen)) fout << minLen + 1 << endl;
    else fout << 0 << endl;

    return 0;
}
