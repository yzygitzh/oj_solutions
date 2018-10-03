/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: buylow
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

ifstream fin ("buylow.in");
ofstream fout ("buylow.out");

/*
 * F[M]: the length of longest decreasing sequence ended with M-th day
 * F[M] = max(F[1] + numSeq[M] < numSeq[1], ..., 1)
 *
 * uniqNum[M]: number of unique sequences of length F[M]
 * NOTE: given any N, when F[i] = N, uniqNum[i] is non-decreasing
 * for any i < j and F[i] = F[j], to count unique sequences contained
 * in both positions, there are 3 cases:
 * 1) numSeq[i] < numSeq[j]: uniqNum[i] + uniqNum[j]
 * 2) numSeq[i] = numSeq[j]: uniqNum[j] (j contains all sequences of i)
 * 3) numSeq[i] > numSeq[j]: this is impossible.
 *
 */

int N;
int numSeq[5010];
int F[5010];
class BigInt {
public:
    string digits;
    BigInt (int num) {
        if (!num) {
            digits = "0";
        } else {
            while (num) {
                digits += '0' + (num % 10);
                num /= 10;
            }
        }
    }
    BigInt (string num): digits(num) {}
    BigInt (): digits("0") {}
    BigInt operator+(const BigInt& num) {
        string sum;
        int carry = 0, i = 0, j = 0;
        while (i < digits.length() || j < num.digits.length()) {
            int currSum = 0;
            if (i < digits.length()) currSum += digits[i] - '0';
            if (j < num.digits.length()) currSum += num.digits[j] - '0';
            // cout << currSum << endl;
            currSum += carry;
            sum += '0' + (currSum % 10);
            carry = currSum / 10;
            i++;
            j++;
        }
        if (carry) sum += '0' + (carry % 10);
        return sum;
    }
    string getNumStr() {
        string numStr = digits;
        reverse(numStr.begin(), numStr.end());
        return numStr;
    }
};
BigInt uniqNum[5010];

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> numSeq[i];
    }
    numSeq[N] = 0;
    N += 1;

    int maxLen = 0;
    for (int i = 0; i < N; i++) {
        F[i] = 1;
        for (int j = 0; j < i; j++) {
            if (numSeq[i] < numSeq[j] && F[j] + 1 > F[i]) {
                F[i] = F[j] + 1;
            }
        }
        // update uniqNum
        int lastUniqNumIdx = -1;
        BigInt uniqSum = 1, tmpUniqSum = 0;
        for (int j = 0; j < i; j++) {
            if (numSeq[i] < numSeq[j] && F[j] + 1 == F[i]) {
                if (lastUniqNumIdx == -1) {
                    uniqSum = 0;
                    tmpUniqSum = uniqNum[j];
                } else {
                    if (numSeq[lastUniqNumIdx] < numSeq[j]) {
                        uniqSum = uniqSum + tmpUniqSum;
                        tmpUniqSum = uniqNum[j];
                    } else if (numSeq[lastUniqNumIdx] == numSeq[j]) {
                        tmpUniqSum = uniqNum[j];
                    }
                }
                lastUniqNumIdx = j;
            }
        }
        uniqSum = uniqSum + tmpUniqSum;
        // new sequence
        uniqNum[i] = uniqSum;
        // cout << i << " " << F[i] << " " << uniqNum[i] << endl;
        if (F[i] > maxLen) maxLen = F[i];
    }

    fout << maxLen - 1 << " " << uniqNum[N - 1].getNumStr() << endl;

    return 0;
}

