class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> charCnt, inCnt;
        for (auto c : s) {
            charCnt[c]++;
        }
        string result;
        for (auto c : s) {
            if (inCnt[c] == 1) {
                charCnt[c]--;
                continue;
            }
            while (result.length() > 0 &&
                   c <= result.back() &&
                   charCnt[result.back()] > 1) {
                charCnt[result.back()]--;
                inCnt[result.back()]--;
                result.pop_back();
            }
            if (inCnt[c] == 0) {
                result.push_back(c);
                inCnt[c]++;
            }
        }
        return result;
    }
};