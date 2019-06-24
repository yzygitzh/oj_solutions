/*
 * POJ 2886 - Who Gets the Most Candies?
 *
 * Number of factors are computed by sieve method.
 * O(n(1 + 1/2 + ... + 1/n)) = O(nlogn)
 *
 *  a      a
 * d b => d c
 *  c
 *
 * a b c d => a   c d
 * 1 2 3 4 => 1 1 2 3
 *
 * Need to find lower bound
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

int N, K;
int suffix[500010];
char names[500010][15];
int numbers[500010];
int divisors[500010];

int maxScore;
char maxName[15];

void calcDivisors() {
    memset(divisors, 0, sizeof(divisors));
    for (int i = 1; i < 500010; i++) {
        for (int j = i; j < 500010; j += i) {
            divisors[j]++;
        }
    }
}

int lowbit(int x) {
    return x & -x;
}

void updateSuffix(int pos, int val) {
    while (pos < 500010) {
        suffix[pos] += val;
        pos += lowbit(pos);
    }
}

int getSuffix(int pos) {
    int result = 0;
    while (pos) {
        result += suffix[pos];
        pos -= lowbit(pos);
    }
    return result;
}

int main() {
    calcDivisors();
    while (scanf("%d", &N) > 0) {
        scanf("%d", &K);
        for (int i = 1; i <= N; i++) {
            scanf("%s%d", names[i], &numbers[i]);
        }
        memset(suffix, 0, sizeof(suffix));
        for (int i = 1; i <= N; i++) {
            updateSuffix(i, 1);
        }
        maxScore = -1;
        // binary search for each K
        for (int i = 1; i <= N; i++) {
            int leftPos = 1, rightPos = N;
            while (leftPos + 1 < rightPos) {
                int midPos = leftPos + (rightPos - leftPos) / 2;
                if (getSuffix(midPos) < K) {
                    leftPos = midPos;
                } else {
                    rightPos = midPos;
                }
            }
            int validPos = getSuffix(leftPos) == K ? leftPos : rightPos;
            // printf("pos, %d; name, %s\n", validPos, names[validPos]);
            if (divisors[i] > maxScore) {
                maxScore = divisors[i];
                strcpy(maxName, names[validPos]);
            }
            updateSuffix(validPos, -1);
            if (i != N) {
                K = K - 1 + (numbers[validPos] < 0 ? 0 : -1);
                K = ((((K + numbers[validPos]) % (N - i)) + (N - i)) % (N - i)) + 1;
            }
            // printf("K: %d; name, %s\n", K, maxName);
        }
        printf("%s %d\n", maxName, maxScore);
    }
    return 0;
}

