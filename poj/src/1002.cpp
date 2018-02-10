/*
 * POJ 1002
 */

#include <cstdio>

int charNum[256] = {0};
int numCount[10000000] = {0};

int main() {
    int stageCount = 0, dialNum = 2;
    for (unsigned i = (unsigned)'A'; i <= (unsigned)'Z'; i++) {
        stageCount++;
        if (i == (unsigned)'Q' || i == (unsigned)'Z') {
            stageCount--;
            continue;
        }
        charNum[i] = dialNum;
        if (stageCount == 3) {
            stageCount = 0;
            dialNum++;
        }
    }

    int sampleCount = 0;
    scanf("%d", &sampleCount);
    while (sampleCount--) {
        int bufIdx = 0, number = 0;
        char numberBuf[50] = {0};
        scanf("%s", numberBuf);
        while (numberBuf[bufIdx] != '\0') {
            if ((unsigned)'A' <= (unsigned)numberBuf[bufIdx] &&
                (unsigned)'Z' >= (unsigned)numberBuf[bufIdx] &&
                (unsigned)'Q' != (unsigned)numberBuf[bufIdx] &&
                (unsigned)'Z' != (unsigned)numberBuf[bufIdx])
                number = number * 10 + charNum[numberBuf[bufIdx]];
            else if ((unsigned)'0' <= (unsigned)numberBuf[bufIdx] &&
                     (unsigned)'9' >= (unsigned)numberBuf[bufIdx])
                number = number * 10 + (unsigned)numberBuf[bufIdx] - (unsigned)'0';
            bufIdx++;
        }
        numCount[number]++;
    }

    int iFlag = 0;
    for (int i = 0; i < 10000000; i++)
        if (numCount[i] > 1) {
            iFlag = 1;
            printf("%03d-%04d %d\n", i / 10000, i - i / 10000 * 10000, numCount[i]);
        }

    if (!iFlag)
        printf("No duplicates.\n");

    return 0;
}
