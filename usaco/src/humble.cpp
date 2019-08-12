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

class HumbleElem {
public:
    int val, idx, factor;
    HumbleElem(int _val, int _idx, int _factor)
        : val(_val), idx(_idx), factor(_factor) {}
    bool operator<(const HumbleElem& h) const {
        return val > h.val;
    }
};

int K, N;
int S[110];
int humbles[100010];

int search() { 
    humbles[0] = 1;
    priority_queue<HumbleElem> humbleQ;
    for (int i = 0; i < K; i++) {
        humbleQ.push(HumbleElem(S[i], 0, S[i]));
    }
    int humbleIdx = 0;
    while (humbleIdx < N) {
        HumbleElem elem = humbleQ.top();
        humbleQ.pop();
        if (elem.val > humbles[humbleIdx]) {
            humbles[++humbleIdx] = elem.val;
        }
        humbleQ.push(HumbleElem(humbles[elem.idx + 1] * elem.factor,
                                elem.idx + 1, elem.factor));
    }
    return humbles[humbleIdx];
}

int main() {
    fin >> K >> N;
    for (int i = 0; i < K; i++) {
        fin >> S[i];
    }
    fout << search() << endl;

    return 0;
}

