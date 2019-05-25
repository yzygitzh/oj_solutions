/*
 * POJ 2533 - Longest Ordered Subsequence
 *
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

int seq[1010];
int seqLenToMinEnd[1010] = {0};
int maxSeqLen = 0;

int main() {
    int seqLen;
    cin >> seqLen;
    seqLenToMinEnd[0] = -1;
    for (int i = 0; i < seqLen; i++) {
        cin >> seq[i];
        int left = 0, right = maxSeqLen;
        // find maximum length whose end < seq[i]
        // and update the seqLenToMinEnd[max_len + 1]
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (seqLenToMinEnd[mid] < seq[i]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (seqLenToMinEnd[right] < seq[i]) {
            seqLenToMinEnd[right + 1] = seq[i];
            maxSeqLen = max(maxSeqLen, right + 1);
        } else if (seqLenToMinEnd[left] < seq[i]) {
            seqLenToMinEnd[left + 1] = seq[i];
            maxSeqLen = max(maxSeqLen, left + 1);
        }
    }
    cout << maxSeqLen << endl;

    return 0;
}

