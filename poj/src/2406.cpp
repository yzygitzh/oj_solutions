/*
 * POJ 2406 - Power Strings
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

int inputLen, doubleLen;
char inputStr[1000010];
char doubleStr[2000010];
int nextArray[1000010];

int main() {
    while (true) {
        scanf("%s", inputStr);
        inputLen = strlen(inputStr);
        if (inputStr[0] == '.' && inputLen == 1) {
            break;
        }
        if (inputLen == 1) {
            printf("1\n");
            continue;
        }
        // inputLen > 1
        memcpy(doubleStr, inputStr + 1, inputLen - 1);
        memcpy(doubleStr + inputLen - 1, inputStr, inputLen - 1);
        doubleLen = 2 * inputLen - 2;
        doubleStr[doubleLen] = '\0';
        // kmp
        nextArray[0] = -1;
        int i = 0, j = -1;
        while (i < inputLen) {
            while (j >= 0 && inputStr[i] != inputStr[j]) j = nextArray[j];
            i++, j++;
            if (i == inputLen) break;
            if (inputStr[i] == inputStr[j]) nextArray[i] = nextArray[j];
            else nextArray[i] = j;
        }
        i = 0, j = 0;
        while (i < doubleLen && j < inputLen) {
            while (j >= 0 && doubleStr[i] != inputStr[j]) j = nextArray[j];
            i++, j++;
        }
        if (j == inputLen) {
            printf("%d\n", inputLen / (i - j + 1));
        } else {
            printf("1\n");
        }
    }
    return 0;
}

