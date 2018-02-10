/*
 * POJ 1014 - Dividing
 *
 * A backpack problem with
 * total volume N = sum(ni) / 2
 *
 * Using binary optimization to prevent TLE
 * The same marbles can be represented using "the power of 2"'s
 * e.g.: 31 of 1-marbles, represented by 1 + 2 + 4 + 8 + 16
 *
 * complexity: O(N * log(K))
 *
 * Using 1-dim array to satisfy memory limit (flatN instead of N)
 */

#include <cstdio>

int F[120001], flatN[100];

void calcF(int maxIdx, int maxVol, int sampleCount) {
    int nIdx = 1, currVol = 0;
    for (int k = 1; k < maxIdx; k++)
        for (int vol = maxVol; vol >= 0; vol--) {
            int val1 = F[vol];
            int val2 = 0;
            if (vol - flatN[k] >= 0)
                val2 = flatN[k] + F[vol - flatN[k]];
            F[vol] = (val1 > val2) ? val1 : val2;
            if (F[vol] == maxVol) {
                printf("Collection #%d:\nCan be divided.\n\n", sampleCount);
                return;
            }
        }
    printf("Collection #%d:\nCan't be divided.\n\n", sampleCount);
    return;
}

int main() {
    int sampleCount = 0;
    while (1) {
        int n[7], maxVol = 0;
        for (int i = 1; i <= 6; i++) {
            scanf("%d", &n[i]);
            maxVol += i * n[i];
        }
        if (maxVol == 0)
            break;

        for (int i = 0; i < 120001; i++)
            F[i] = 0;
        for (int i = 0; i < 100; i++)
            flatN[i] = 0;

        int maxIdx = 0;
        for (int i = 1; i <= 6; i++) {
            int binary = 1;
            while (n[i] > 0) {
                n[i] -= binary;
                if (n[i] < 0)
                    flatN[maxIdx++] = i * (n[i] + binary);
                else
                    flatN[maxIdx++] = i * binary;
                binary *= 2;
            }
        }
        if (maxVol % 2)
            printf("Collection #%d:\nCan't be divided.\n\n", ++sampleCount);
        else
            calcF(maxIdx, maxVol / 2, ++sampleCount);
    }
    return 0;
}
