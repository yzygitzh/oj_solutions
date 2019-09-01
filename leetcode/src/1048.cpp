class Solution {
public:
    bool wordMatch(string& shortWord, string& longWord) {
        int shortIdx = 0, longIdx = 0;
        while (shortIdx < shortWord.length() &&
               longIdx < longWord.length() &&
               shortWord[shortIdx] == longWord[longIdx]) {
            shortIdx++;
            longIdx++;
        }
        longIdx++;
        while (shortIdx < shortWord.length() &&
               longIdx < longWord.length() &&
               shortWord[shortIdx] == longWord[longIdx]) {
            shortIdx++;
            longIdx++;
        }
        return shortIdx == shortWord.length();
    }
    
    int longestStrChain(vector<string>& words) {
        // chain length 16 at most
        vector<vector<pair<string, int>>> lenToWords(17);
        for (auto& word : words) {
            lenToWords[word.length()].push_back(make_pair(word, 1));
        }
        int result = 1;
        for (int len = 2; len <= 16; len++) {
            for (int i = 0; i < lenToWords[len - 1].size(); i++) {
                for (int j = 0; j < lenToWords[len].size(); j++) {
                    if (wordMatch(lenToWords[len - 1][i].first,
                                  lenToWords[len][j].first)) {
                        lenToWords[len][j].second = max(lenToWords[len][j].second,
                                                        lenToWords[len - 1][i].second + 1);
                        result = max(result, lenToWords[len][j].second);
                    }
                }
            }
        }
        return result;
    }
};