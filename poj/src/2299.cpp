/*
 * POJ 2299 - Ultra-QuickSort
 *
 */

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

int seqLen;
vector<int> seq(500010);

long long mergeSort(int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        long long leftCnt = mergeSort(left, mid);
        long long rightCnt = mergeSort(mid + 1, right);
        long long crossCnt = 0;
        vector<int> newSeq;
        int idx1 = left, idx2 = mid + 1;
        while (idx1 <= mid || idx2 <= right) {
            if (idx1 > mid) {
                newSeq.push_back(seq[idx2]);
                idx2++;
            } else if (idx2 > right) {
                crossCnt += idx2 - mid - 1;
                newSeq.push_back(seq[idx1]);
                idx1++;
            } else {
                if (seq[idx1] < seq[idx2]) {
                    crossCnt += idx2 - mid - 1;
                    newSeq.push_back(seq[idx1]);
                    idx1++;
                } else {
                    newSeq.push_back(seq[idx2]);
                    idx2++;
                }
            }
        }
        for (int i = 0; i < right - left + 1; i++) {
            seq[left + i] = newSeq[i];
        }
        return leftCnt + crossCnt + rightCnt;
    }
}

int main() {
    while (true) {
        cin >> seqLen;
        if (seqLen == 0) break;
        for (int i = 0; i < seqLen; i++) {
            cin >> seq[i];
        }
        cout << mergeSort(0, seqLen - 1) << endl;
    }
    return 0;
}

