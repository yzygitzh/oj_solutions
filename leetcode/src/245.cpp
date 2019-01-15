class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int wordsLen = words.size();
        vector<int> indices1, indices2;
        for (int i = 0; i < wordsLen; i++) {
            if (words[i] == word1) indices1.push_back(i);
            if (words[i] == word2) indices2.push_back(i);
        }
        
        int minDis = (~(1 << 31));
        int len1 = indices1.size(), len2 = indices2.size();
        if (word1 == word2) {
            for (int i = 1; i < len1; i++) {
                if (indices1[i] - indices1[i - 1] < minDis) {
                    minDis = indices1[i] - indices1[i - 1];
                }
            }
        } else {
            int idx1 = 0, idx2 = 0;
            while (idx1 < len1 && idx2 < len2) {
                if (indices1[idx1] < indices2[idx2]) {
                    if (indices2[idx2] - indices1[idx1] < minDis) {
                        minDis = indices2[idx2] - indices1[idx1];
                    }
                    idx1++;
                } else {
                    if (indices1[idx1] - indices2[idx2] < minDis) {
                        minDis = indices1[idx1] - indices2[idx2];
                    }
                    idx2++;
                }
            }
        }
        return minDis;
    }
};