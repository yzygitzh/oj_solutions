/*
 * POJ 1019 - Number Sequence
 * O(10 * 32k)
 */

#include <cstdio>
#include <cstdlib>
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

long long prefixSum[32000] = {0};
long long seqLen[32000] = {0};
long long maxIdx;

void initSeq() {
    long long i = 0;
    while (prefixSum[i] < (1LL << 31)) {
        i++;
        long long digitLen = 0, tmpIdx = i;
        while (tmpIdx) {
            digitLen++;
            tmpIdx /= 10;
        }
        seqLen[i] = seqLen[i - 1] + digitLen;
        prefixSum[i] = prefixSum[i - 1] + seqLen[i];
    }
    maxIdx = i;
}

long long calc(long long pos) {
    // binary search for seqIdx
    long long left = 1, right = maxIdx;
    while (left + 1 < right) {
        long long mid = left + (right - left) / 2;
        if (prefixSum[mid] < pos) {
            left = mid;
        } else {
            right = mid;
        }
    }
    long long seqIdx = left;
    if (prefixSum[left] < pos) seqIdx = right;
    // find the digit
    long long digitIdx = pos - prefixSum[seqIdx - 1], i = 0;
    while (true) {
        i++;
        long long tmpIdx = i;
        vector<long long> digits;
        while (tmpIdx) {
            digits.push_back(tmpIdx % 10);
            tmpIdx /= 10;
        }
        if (digitIdx <= digits.size()) {
            return digits[digits.size() - digitIdx];
        } else {
            digitIdx -= digits.size();
        }
    }
    return -1;
}

int main() {
    initSeq();
    int caseNum, idx;
    cin >> caseNum;
    while (caseNum--) {
        cin >> idx;
        cout << calc(idx) << endl;
    }
    return 0;
}

