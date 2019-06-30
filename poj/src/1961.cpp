/*
 * POJ 1961 - Period
 *
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

int inputLen;
char inputStr[1000010];
int nextArray[1000010];

int main() {
    int caseNum = 0;
    while (true) {
        scanf("%d", &inputLen);
        if (inputLen == 0) {
            break;
        }
        caseNum++;
        scanf("%s", inputStr);
        int i = 0, j = -1;
        nextArray[0] = -1;
        while (i < inputLen) {
            while (j >= 0 && inputStr[i] != inputStr[j]) j = nextArray[j];
            i++, j++;
            if (i == inputLen + 1) break;
            nextArray[i] = j;
        }
        printf("Test case #%d\n", caseNum);
        for (i = 1; i <= inputLen; i++) {
            int segLen = i - nextArray[i];
            if ((i % segLen) == 0 && i != segLen) {
                printf("%d %d\n", i, i / segLen);
            }
        }
        printf("\n");
    }
    return 0;
}

