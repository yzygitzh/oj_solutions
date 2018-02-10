/*
 * POJ 1011 - Sticks
 *
 * Use searching for each factor of the total length.
 *
 * Using greedy strategy to select sticks. Search from
 * longer ones.
 * Note that all substicks MUST fits into some combination.
 * Using 2 pruning:
 * 1. if the first selected stick failed, then all fail,
 *    for we can't find a valid combination for the longest
 *    substick;
 * 2. if a complete combination is built and failed in
 *    the following dividable call, then fail, for we
 *    choose longer sticks first, and a longer stick can
 *    anytime be substituted with shorter ones but not
 *    vice versa.
 */

#include <cstdio>
#include <cstring>

const int maxLen = 50;
int originSticks[maxLen + 10];
int sticks[maxLen + 10];

bool dividable(int currLen, int originLen, int startLen, int restNum) {
    int i = startLen;
    if (restNum == 0)
        return true;
    while (i > 0) {
        if (sticks[i] == 0 || currLen + i > originLen)
            i--;
        else if (currLen + i < originLen) {
            sticks[i]--;
            if (dividable(currLen + i, originLen, i, restNum))
                return true;
            sticks[i]++;
            i--;
            // the first selected stick fails
            if (currLen == 0)
                return false;
        }
        else if (currLen + i == originLen) {
            sticks[i]--;
            if (dividable(0, originLen, maxLen, restNum - 1))
                return true;
            sticks[i]++;
            return false;
        }
    }
    return false;
}

int main() {
    int stickNum, stickLen, stickLenSum;
    while (true) {
        scanf("%d", &stickNum);
        if (stickNum == 0)
            break;

        memset(originSticks, 0, sizeof(int) * (maxLen + 10));
        stickLenSum = 0;

        for (int i = 0; i < stickNum; i++) {
            scanf("%d", &stickLen);
            if (stickLen > 50)
                continue;
            stickLenSum += stickLen;
            originSticks[stickLen]++;
        }

        for (int i = 1; i <= stickLenSum; i++)
            if ((stickLenSum % i == 0)) {
                memcpy(sticks, originSticks, sizeof(int) * (maxLen + 10));
                if (dividable(0, i, maxLen, stickLenSum / i)) {
                    printf("%d\n", i);
                    break;
                }
            }
    }
    return 0;
}
