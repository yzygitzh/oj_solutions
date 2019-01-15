class WordDistance {
public:
    unordered_map<string, vector<int> > wordToIdx;
    
    WordDistance(vector<string> words) {
        int wordsLen = words.size();
        for (int i = 0; i < wordsLen; i++) {
            wordToIdx[words[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        vector<int>& indices1 = wordToIdx[word1];
        vector<int>& indices2 = wordToIdx[word2];
        
        int idx1 = 0, idx2 = 0;
        int len1 = indices1.size(), len2 = indices2.size();
        int minDis = (~(1 << 31));
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
        return minDis;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */