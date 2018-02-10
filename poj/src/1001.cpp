/*
 * POJ 1001 - Exponentiation
 *
 * printReal is the most tricky part, dealing with pre/post zeros
 */

#include <cstdio>
#include <cstring>

struct realNum {
    char sig[1000];
    int exp;
};

struct realNum delTrailingZero(struct realNum R) {
    int sigLen = strlen(R.sig);
    while (R.sig[--sigLen] == '0') {
        R.exp += 1;
        R.sig[sigLen] = '\0';
    }
    return R;
}

struct realNum parseRealNum(char *RStr) {
    int expFlag = 0, sigNum = 0;
    struct realNum retVal;
    retVal.exp = 0;
    for (int i = 0; RStr[i] != '\0'; i++) {
        retVal.exp -= expFlag;
        if (RStr[i] == '.')
            expFlag = 1;
        else
            sigNum = sigNum * 10 + (int)(RStr[i] - '0');
    }
    sprintf(retVal.sig, "%d", sigNum);
    return delTrailingZero(retVal);
}

struct realNum realMul(struct realNum R1, struct realNum R2) {
    char reverseR1Str[1000] = {0}, reverseR2Str[1000] = {0}, reverseRetRStr[1000] = {0};
    int R1StrLen = strlen(R1.sig), R2StrLen = strlen(R2.sig);
    struct realNum retR;

    for (int i = 0; i < 1000; i++)
        reverseRetRStr[i] = '0';

    for (int i = 0; i < R1StrLen; i++)
        reverseR1Str[i] = R1.sig[R1StrLen - i - 1];
    for (int i = 0; i < R2StrLen; i++)
        reverseR2Str[i] = R2.sig[R2StrLen - i - 1];

    for (int i = 0; i < R1StrLen; i++) {
        int carry = 0, j, R1Dig, R2Dig, digResult;
        for (j = 0; j < R2StrLen; j++) {
            R1Dig = (int)(reverseR1Str[i] - '0');
            R2Dig = (int)(reverseR2Str[j] - '0');
            digResult = R1Dig * R2Dig + carry + (int)(reverseRetRStr[i + j] - '0');
            carry = digResult / 10;
            reverseRetRStr[i + j] = (char)((digResult % 10) + '0');
        }
        while (carry > 0) {
            digResult = carry + (int)(reverseRetRStr[i + j] - '0');
            carry = digResult / 10;
            reverseRetRStr[i + j] = (char)((digResult % 10) + '0');
            j++;
        }
    }

    int reverseRetRStrLen;
    for (reverseRetRStrLen = 1000; reverseRetRStrLen > 0; reverseRetRStrLen--)
        if (reverseRetRStr[reverseRetRStrLen - 1] == '0')
            reverseRetRStr[reverseRetRStrLen - 1] = '\0';
        else
            break;

    for (int i = 0; i < reverseRetRStrLen; i++)
        retR.sig[i] = reverseRetRStr[reverseRetRStrLen - i - 1];
    retR.sig[reverseRetRStrLen] = '\0';
    retR.exp = R1.exp + R2.exp;

    return delTrailingZero(retR);
}

void printReal(struct realNum R) {
    int sigLen = strlen(R.sig);
    int dotPos = sigLen + R.exp;
    int startPos = dotPos < 0 ? dotPos : 0;
    int endPos = dotPos > sigLen ? dotPos : sigLen;
    while (startPos < endPos) {
        if (startPos == dotPos)
            printf(".");
        if (startPos < 0 || startPos >= sigLen)
            printf("0");
        else
            printf("%c", R.sig[startPos]);
        startPos++;
    }
    printf("\n");
    return;
}

int main() {
    char RStr[10];
    int n;
    while(scanf("%s%d", RStr, &n)==2) {
        struct realNum R = parseRealNum(RStr);
        struct realNum resultR = R;
        while (--n)
            resultR = realMul(resultR, R);
        printReal(resultR);
    }
    return 0;
}