char* convert(char* s, int numRows) {
    if (numRows == 1)
        return s;
        
    int groupSize = numRows * 2 - 2;
    int groupWidth = numRows - 1;
    int sLen = 0;
    while (s[sLen] != '\0')
        sLen++;
    int groupNum = (sLen + groupSize - 1) / groupSize;
    int matrixWidth = groupWidth * groupNum;
    
    char *newS = malloc(sizeof(char) * matrixWidth * numRows);
    memset(newS, 0, sizeof(char) * matrixWidth * numRows);
    
    for (int i = 0; i < groupNum; i++){
        int j = 0;
        for (; j < numRows; j++){
            if (i * groupSize + j < sLen)
                newS[j * matrixWidth + i * groupWidth] = s[i * groupSize + j];
            else
                break;
        }
        if (i * groupSize + j >= sLen)
            break;
        for (; j < groupSize; j++){
            if (i * groupSize + j < sLen)
                newS[(groupSize - j) * matrixWidth + i * groupWidth + (j - numRows + 1)] = s[i * groupSize + j];
            else
                break;
        }
        if (i * groupSize + j >= sLen)
            break;
    }
    
    
    for (int i = 0, j = 0; j < matrixWidth * numRows; j++)
        if (newS[j] != '\0')
            newS[i++] = newS[j];
    newS[sLen] = '\0';
    return newS;
}