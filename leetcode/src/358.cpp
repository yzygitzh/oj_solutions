class Solution {
public:
    string rearrangeString(string s, int k) {
        // greedy
        int sLen = s.length();
        unordered_map<char, int> charCnt;
        for (int i = 0; i < sLen; i++) {
            charCnt[s[i]]++;
        }
        string result;
        unordered_map<char, int> lastUse;
        // init last Use
        for (auto itr = charCnt.begin(); itr != charCnt.end(); ++itr) {
            lastUse[itr->first] = -k;
        }
        // each time greedily choose minimum last use
        for (int i = 0; i < sLen; i++) {
            char minChar;
            int maxCnt = 0;
            bool found = false;
            for (auto itr = lastUse.begin(); itr != lastUse.end(); ++itr) {
                if (charCnt.count(itr->first) && i - itr->second >= k) {
                    if (charCnt[itr->first] > maxCnt) {
                        found = true;
                        minChar = itr->first;
                        maxCnt = charCnt[itr->first];
                    }
                }
            }
            if (!found) return "";
            lastUse[minChar] = i;
            result += minChar;
            charCnt[minChar]--;
            if (charCnt[minChar] == 0) charCnt.erase(minChar);
        }
        return result;
    }
};