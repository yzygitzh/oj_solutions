/*
 * POJ 1753 - Flip Game
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int dim = 4;
char originBoard[5][5], testBoard[5][5];

bool tryNum(unsigned num) {
    memcpy(testBoard, originBoard, sizeof(originBoard));
    // do flip
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (num & (1 << (i * dim + j))) {
                testBoard[i][j] = testBoard[i][j] == 'b' ? 'w' : 'b';
                if (i - 1 >= 0) testBoard[i - 1][j] = testBoard[i - 1][j] == 'b' ? 'w' : 'b';
                if (i + 1 < dim) testBoard[i + 1][j] = testBoard[i + 1][j] == 'b' ? 'w' : 'b';
                if (j - 1 >= 0) testBoard[i][j - 1] = testBoard[i][j - 1] == 'b' ? 'w' : 'b';
                if (j + 1 < dim) testBoard[i][j + 1] = testBoard[i][j + 1] == 'b' ? 'w' : 'b';
            }
        }
    }
    // check if valid
    char firstChar;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == 0 && j == 0) firstChar = testBoard[i][j];
            else if (firstChar != testBoard[i][j]) return false;
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < dim; i++) {
        scanf("%s", originBoard[i]);
    }
    int maxFlip = 17;
    for (unsigned i = 0; i < (1UL << 16); i++) {
        if (tryNum(i)) {
            int currFlip = 0;
            for (int j = 0; j < 16; j++) {
                if (i & (1 << j)) currFlip++;
            }
            if (currFlip < maxFlip) maxFlip = currFlip;
        }
    }
    if (maxFlip != 17) {
        printf("%d\n", maxFlip);
    } else {
        printf("Impossible\n");
    }
    return 0;
}
