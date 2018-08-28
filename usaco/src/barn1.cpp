/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: barn1
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/* Mind that M can be more than C */

int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");

    int M, S, C;
    int cowPos;
    vector<int> cowPosList;
    vector<int> intervals;

    fin >> M >> S >> C;
    for (int i = 0; i < C; i++) {
        fin >> cowPos;
        cowPosList.push_back(cowPos);
    }
    sort(cowPosList.begin(), cowPosList.end());

    for (int i = 0; i < C - 1; i++) {
        intervals.push_back(cowPosList[i + 1] - cowPosList[i] - 1);
    }
    sort(intervals.begin(), intervals.end(), greater<int>());

    int len = cowPosList[C - 1] - cowPosList[0] + 1;
    int boardNum = M < C ? M : C;
    for (int i = 0; i < boardNum - 1; i++) {
        len -= intervals[i];
    }

    fout << len << endl;

    return 0;
}

