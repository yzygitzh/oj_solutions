/*
 * POJ 1014
 *
 * A backpack problem with
 * total volume N = sum(ni) / 2
 *
 */

#include <cstdio>

int F[6][20001], flatN[20001];

void calcF(int maxIdx, int maxVol, int sampleCount) {
    int nIdx = 1, currVol = 0;
    for (int vol = 0; vol <= maxVol; vol++)
        for (int k = 0; k < maxIdx; k++) {
            int val1 = (k - 1 >= 0) ? F[vol % 6][k - 1] : 0;
            int val2 = 0;
            if (vol - flatN[k] >= 0) {
                val2 += flatN[k];
                if (k - 1 >= 0)
                    val2 += F[(vol - flatN[k] + 6) % 6][k - 1];
            }
            F[vol % 6][k] = (val1 > val2) ? val1 : val2;
        }

    for (int k = 0; k < maxIdx; k++)
        if (F[maxVol % 6][k] == maxVol) {
            printf("Collection #%d:\nCan be divided.\n\n", sampleCount);
            return;
        }
    printf("Collection #%d:\nCan't be divided.\n\n", sampleCount);
    return;
}

int main() {
    int n[7], maxIdx, maxVol, sampleCount = 0;
    while (1) {
        sampleCount++;

        scanf("%d %d %d %d %d %d", &n[1], &n[2], &n[3], &n[4], &n[5], &n[6]);
        maxVol = n[1] + 2 * n[2] + 3 * n[3] + 4 * n[4] + 5 * n[5] + 6 * n[6];
        if (maxVol == 0)
            break;
        maxIdx = 0;
        for (int i = 1; i < 7;)
            if (n[i] == 0)
                i++;
            else {
                flatN[maxIdx++] = i;
                n[i]--;
            }

        if (maxVol % 6)
            printf("Collection #%d:\nCan't be divided.\n\n", sampleCount);
        else
            calcF(maxIdx, maxVol / 2, sampleCount);
    }
    return 0;
}
