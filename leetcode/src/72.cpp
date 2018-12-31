class Solution {
public:
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int minDistance(string word1, string word2) {
        int word1Len = word1.size();
        int word2Len = word2.size();
        
        vector<vector<int> > match12(2, vector<int>(word2Len + 1, 0));
        // dis('', 'abc') == len('abc')
        for (int i = 0; i <= word2Len; i++) {
            match12[0][i] = i;
        }
        for (int i = 1; i <= word1Len; i++) {
            match12[i % 2][0] = i;
            for (int j = 1; j <= word2Len; j++) {
                match12[i % 2][j] = getMin(match12[(i - 1) % 2][j] + 1,
                                           match12[i % 2][j - 1] + 1);
                if (word1[i - 1] == word2[j - 1]) {
                    match12[i % 2][j] = getMin(match12[i % 2][j],
                                               match12[(i - 1) % 2][j - 1]);
                } else {
                    match12[i % 2][j] = getMin(match12[i % 2][j],
                                               match12[(i - 1) % 2][j - 1] + 1);
                }
            }
        }
        return match12[word1Len % 2][word2Len];
    }
};