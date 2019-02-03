class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int findSubstringInWraproundString(string p) {
        int pLen = p.length();
        if (pLen == 0) return 0;
        int visited[26] = {0};
        int result = 1, currLen = 1;
        visited[p[0] - 'a'] = 1;
        for (int i = 1; i < pLen; i++) {
            if ((((unsigned)p[i - 1] + 1) % 26) == ((unsigned)p[i] % 26)) {
                currLen++;
            } else {
                currLen = 1;
            }
            if (visited[p[i] - 'a'] < currLen) {
                result += currLen - visited[p[i] - 'a'];   
            }
            int needToUpdate = getMin(currLen, 26);
            for (int j = 0; j < needToUpdate; j++) {
                int idx = (p[i] - 'a' - j + 26) % 26;
                visited[idx] = getMax(visited[idx], currLen - j);
            }
        }
        return result;
    }
};