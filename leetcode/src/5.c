char* longestPalindrome(char* s) {
    // get length of s
    int sLen = 0, maxLen = 1, maxStart = 0;
    while (s[sLen] != '\0')
        sLen++;
    // iterate odd
    for (int i = 0; i < sLen; i++){
        int tmpLen = -1;
        int maxStress = (sLen - 1 - i) > i ? i : (sLen - 1 - i);
        int j;
        for (j = 0; j <= maxStress; j++){
            if (s[i - j] != s[i + j])
                break;
            tmpLen += 2;
        }
        if (tmpLen > maxLen){
            maxLen = tmpLen;
            maxStart = i - j + 1;
        }
    }
    // iterate even
    for (int i = 0; i < sLen - 1; i++){
        if (s[i] != s[i + 1])
            continue;
        int tmpLen = 0;
        int maxStress = (sLen - 2 - i) > i ? i : (sLen - 2 - i);
        int j;
        for (j = 0; j <= maxStress; j++){
            if (s[i - j] != s[i + 1 + j])
                break;
            tmpLen += 2;
        }
        if (tmpLen > maxLen){
            maxLen = tmpLen;
            maxStart = i - j + 1;
        }
    }
    s[maxStart + maxLen] = '\0';
    return s + maxStart;
}