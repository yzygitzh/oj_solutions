class Solution {
public:
    int maxProduct(vector<string>& words) {
        int wordsLen = words.size();
        if (wordsLen < 2) return 0;
        
        vector<unsigned> wordBits(wordsLen, 0);
        vector<unsigned> wordLens(wordsLen, 0);
        for (int i = 0; i < wordsLen; i++) {
            int wordLen = words[i].length();
            for (int j = 0; j < wordLen; j++) {
                wordBits[i] |= (1 << (words[i][j] - 'a'));
            }
            wordLens[i] = wordLen;
        }
        
        int maxProduct = 0;
        for (int i = 0; i < wordsLen; i++) {
            for (int j = i + 1; j < wordsLen; j++) {
                if (!(wordBits[i] & wordBits[j])) {
                    int currProduct = wordLens[i] * wordLens[j];
                    if (currProduct > maxProduct) maxProduct = currProduct;
                }
            }
        }
        
        return maxProduct;
    }
};