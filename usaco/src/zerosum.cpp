/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: zerosum
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

int N;
char op[10];
ofstream fout ("zerosum.out");

void DFS(int depth) {
    if (depth == N) {
        vector<int> numSeq;
        vector<char> opSeq;
        int currNum = 1;
        for (int i = 1; i < N; i++) {
            if (op[i] == '+' || op[i] == '-') {
                opSeq.push_back(op[i]);
                numSeq.push_back(currNum);
                currNum = i + 1;
            } else if (op[i] == ' ') {
                currNum = currNum * 10 + i + 1;
            }
        }
        numSeq.push_back(currNum);
        int sum = numSeq[0];
        for (int i = 0; i < opSeq.size(); i++) {
            if (opSeq[i] == '+') sum += numSeq[i + 1];
            else if (opSeq[i] == '-') sum -= numSeq[i + 1];
        }
        if (sum == 0) {
            // for (int i = 0; i < numSeq.size(); i++) {
            //     fout << numSeq[i] << endl;
            // }
            for (int i = 1; i <= N; i++) {
                fout << i;
                if (i != N) fout << op[i];
            }
            fout << endl;
        }
    } else {
        op[depth] = ' ';
        DFS(depth + 1);
        op[depth] = '+';
        DFS(depth + 1);
        op[depth] = '-';
        DFS(depth + 1);
    }
}

int main() {
    ifstream fin ("zerosum.in");

    fin >> N;
    DFS(1);

    return 0;
}

