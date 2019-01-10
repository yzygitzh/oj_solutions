/*
 * POJ 2965 - The Pilots Brothers' Refrigerator
 *
 * Use bit manipulation for constant optimization
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int dim = 4;
unsigned originBoard = 0;

inline bool tryNum(unsigned num) {
    unsigned testBoard = originBoard;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (num & (1 << (i * dim + j))) {
                testBoard ^= (1U << (i * 4 + j));
                testBoard ^= (0xFU << (i * 4));
                testBoard ^= (0x1111U << j);
            }
        }
    }
    return testBoard == 0xFFFF;
}

int main() {
    char tmpBuf[5];
    for (int i = 0; i < dim; i++) {
        scanf("%s", tmpBuf);
        for (int j = 0; j < dim; j++) {
            if (tmpBuf[j] == '-') originBoard += (1U << (i * 4 + j));
        }
    }
    int minFlip = 17;
    unsigned minStep;
    for (unsigned i = 0; i < (1U << 16); i++) {
        int currFlip = 0;
        for (int j = 0; j < 16; j++) {
            if (i & (1 << j)) currFlip++;
        }
        if (currFlip < minFlip && tryNum(i)) {
            minFlip = currFlip;
            minStep = i;
        }
    }
    printf("%d\n", minFlip);
    for (int i = 0; i < 16; i++) {
        if (minStep & (1 << i)) {
            printf("%d %d\n", (i / 4) + 1, (i % 4) + 1);
        }
    }
    return 0;
}
