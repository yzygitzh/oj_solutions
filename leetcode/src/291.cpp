class Solution {
public:
    bool found = false;
    
    bool wordPatternMatch(string pattern, string str) {
        unordered_map<char, string> pGuess;
        unordered_set<string> pGuessSet;
        dfs(pattern, 0, str, 0, pGuess, pGuessSet);
        return found;
    }
    
    void dfs(string pattern, int pIdx, string str, int sIdx,
             unordered_map<char, string>& pGuess,
             unordered_set<string> pGuessSet) {
        int pLen = pattern.length(), sLen = str.length();
        if (pIdx == pLen || sIdx == sLen) {
            if (pIdx == pLen && sIdx == sLen) {
                found = true;
            }
            return;
        } else {
            char p = pattern[pIdx];
            int restLen = sLen - sIdx;
            if (!pGuess.count(p)) {
                for (int i = 1; i <= restLen; i++) {
                    string pStr = str.substr(sIdx, i);
                    if (pGuessSet.count(pStr)) continue;
                    pGuess[p] = pStr;
                    pGuessSet.insert(pStr);
                    dfs(pattern, pIdx + 1, str, sIdx + i, pGuess, pGuessSet);
                    if (found) return;
                    pGuessSet.erase(pStr);
                    pGuess.erase(p);
                }
            } else {
                // try to match pGuess[p]
                string pStr = pGuess[p];
                int matchIdx = 0;
                while (matchIdx < pStr.length() &&
                       matchIdx < restLen) {
                    if (pStr[matchIdx] != str[sIdx + matchIdx]) {
                        return;
                    }
                    matchIdx++;
                }
                if (matchIdx == pStr.length()) {
                    dfs(pattern, pIdx + 1, str, sIdx + matchIdx, pGuess, pGuessSet);
                    if (found) return;
                }
            }
        }
    }
};