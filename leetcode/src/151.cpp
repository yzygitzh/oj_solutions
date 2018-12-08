class Solution {
public:
    void reverseWords(string &s) {
        int sLen = s.length();
        vector<string> wordStack;
        
        string currWord;
        for (int i = 0; i < sLen; i++) {
            if (s[i] != ' ') {
                while (i < sLen && s[i] != ' ') {
                    currWord += s[i];
                    i++;
                }
                wordStack.push_back(currWord);
                currWord = "";
            }
        }

        s = "";
        while (wordStack.size() > 0) {
            s += wordStack[wordStack.size() - 1];
            wordStack.pop_back();
            if (wordStack.size() > 0) s += ' ';
        }
    }
};