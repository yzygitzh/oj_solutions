/*
 * POJ 1068 - Parencodings
 *
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int seqLen;
        cin >> seqLen;
        vector<int> PSeq(seqLen);
        for (int i = 0; i < seqLen; i++) cin >> PSeq[i];
        // reconstruct sequence
        string originStr;
        int leftCnt;
        leftCnt = 0;
        for (int i = 0; i < seqLen; i++) {
            while (leftCnt < PSeq[i]) {
                originStr += '(';
                leftCnt++;
            }
            originStr += ')';
        }
        // calc W seq
        vector<pair<int, int> > WStack;
        vector<int> WSeq;
        int originStrLen = originStr.length();
        for (int i = 0; i < originStrLen; i++) {
            if (originStr[i] == '(') {
                WStack.push_back(make_pair(1, 0));
            } else {
                leftCnt = 0;
                while (WStack.rbegin()->second != 0) {
                    leftCnt += WStack.rbegin()->first;
                    WStack.pop_back();
                }
                WStack.pop_back();
                WStack.push_back(make_pair(leftCnt + 1, 1));
                WSeq.push_back(leftCnt + 1);
            }
        }
        // output
        for (int i = 0; i < seqLen; i++) {
            if (i > 0) cout << " ";
            cout << WSeq[i];
        }
        cout << endl;
    }
    return 0;
}
