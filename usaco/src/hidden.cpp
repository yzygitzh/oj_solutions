/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: hidden
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
#include <bitset>

#pragma pack(1)
using namespace std;

ifstream fin ("hidden.in");
ofstream fout ("hidden.out");

/*
 * Suffix Array Template
 * 1. sa[i]: sorted suffixes
 * 2. rank[i]: rank of suffix(i)
 * 3. height[i]: length of common prefix of suffix(i) and suffix(i+1)
 */

template <class T>
class SuffixArray {
public:
    T *seq;
    int *sa, *rank, *height;
    pair<T, int> *rankSeq;
    pair<pair<int, int>, int> *rank2;
    int seqLen;
    int sortLen;
    bool nullIsSmaller;
    SuffixArray(const T* _seq, int _seqLen, int _nullIsSmaller) {
        nullIsSmaller = _nullIsSmaller;
        seqLen = _seqLen;
        seq = new T[seqLen];
        memcpy(seq, _seq, sizeof(T) * seqLen);

        sa = new int[seqLen];
        rank = new int[seqLen];
        rankSeq = new pair<T, int>[seqLen];
        rank2 = new pair<pair<int, int>, int>[seqLen];
        height = new int[seqLen];
    }
    ~SuffixArray() {
        delete seq;
        delete sa;
        delete rank;
        delete rankSeq;
        delete rank2;
        delete height;
    }
    void calcSA () {
        for (int i = 0; i < seqLen; i++) {
            rankSeq[i] = make_pair(seq[i], i);
        }
        sort(rankSeq, rankSeq + seqLen);
        for (int i = 0; i < seqLen; i++) {
            sa[i] = rankSeq[i].second;
        }

        int p = 0;
        for (int i = 0; i < seqLen; i++) {
            rank[sa[i]] = p;
            if (i + 1 < seqLen && seq[sa[i]] != seq[sa[i + 1]]) p++;
        }

        sortLen = 1;
        while (sortLen < seqLen) {
            for (int i = 0; i < seqLen; i++) {
                if (i + sortLen < seqLen) {
                    rank2[i] = make_pair(make_pair(rank[i], rank[i + sortLen]), i);
                } else if (nullIsSmaller) {
                    rank2[i] = make_pair(make_pair(rank[i], -1), i);
                } else {
                    rank2[i] = make_pair(make_pair(rank[i], seqLen * 2), i);
                }
            }
            sort(rank2, rank2 + seqLen);
            for (int i = 0; i < seqLen; i++) {
                sa[i] = rank2[i].second;
            }

            p = 0;
            for (int i = 0; i < seqLen; i++) {
                rank[sa[i]] = p;
                if (i + 1 < seqLen && rank2[i].first != rank2[i + 1].first) p++;
            }

            sortLen += sortLen;
        }
    }
    void calcHeight() {
        memset(height, 0, sizeof(int) * seqLen);
        for (int i = 0; i < seqLen; i++) {
            int saIdx = rank[i];
            if (saIdx + 1 == seqLen) continue;
            int seqIdx1 = sa[saIdx];
            int seqIdx2 = sa[saIdx + 1];
            while (seq[seqIdx1 + height[saIdx]] == seq[seqIdx2 + height[saIdx]]) {
                height[saIdx]++;
            }
            height[rank[i + 1]] = height[saIdx] - 1 > 0 ? height[saIdx] : 0;
        }
    }
};

int L;

int main() {
    fin >> L;
    string passwd;
    string inputLine;
    while (fin >> inputLine) {
        passwd += inputLine;
    }

    passwd += passwd;
    SuffixArray<char> sa(passwd.c_str(), passwd.length(), false);
    sa.calcSA();

    int idx = 0;
    while (sa.sa[idx] >= L) idx++;
    fout << sa.sa[idx] << endl; 

    return 0;
}
