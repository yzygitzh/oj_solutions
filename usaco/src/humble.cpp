/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: humble
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

ifstream fin ("humble.in");
ofstream fout ("humble.out");

int K, N;
unsigned long long S[110];
class Elem {
public:
    unsigned long long base, num;
    Elem(unsigned long long _base, unsigned long long _num): base(_base), num(_num) {}
    bool operator< (const Elem& e) const {
        return num > e.num;
    }
};
priority_queue<Elem> searchQ;

unsigned long long search() {
    for (int i = 0; i < K; i++) {
        searchQ.push(Elem(S[i], S[i]));
    }
    bool stopPush = false;
    unsigned currMax = S[0];
    int count = 0;
    for (int i = 0; i < N - 1; i++) {
        Elem topElem = searchQ.top();
        // cout << ":" << topElem.num << endl;
        searchQ.pop();
        count++;
        for (int j = 0; j < K; j++) {
            if (S[j] >= topElem.base) {
                unsigned long long candidate = topElem.num * S[j]; 
                if (candidate < (1ULL<<31)) {
                    if (stopPush && candidate > currMax) break;
                    searchQ.push(Elem(S[j], candidate));
                    // cout << candidate << endl;
                    if (count + searchQ.size() >= N) stopPush = true;
                    currMax = candidate > currMax ? candidate : currMax;
                    // cout << "max:" << currMax << endl;
                }
            }
        }
    }
    return searchQ.top().num;
}

int main() {
    fin >> K >> N;
    for (int i = 0; i < K; i++) {
        fin >> S[i];
    }
    fout << search() << endl;

    return 0;
}

