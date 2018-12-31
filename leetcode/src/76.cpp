class Solution {
public:
    string minWindow(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        if (sLen == 0 || tLen == 0) return "";
            
        unordered_map<char, int> charSet;
        unordered_map<char, int> charCnt;
        
        for (int i = 0; i < tLen; i++) {
            charSet[t[i]]++;
        }
        
        int minLen = sLen, minIdx = 0;
        int left = 0, right = 0;
        if (charSet.count(s[right])) {
            charCnt[s[right]]++;
        }
        bool onceMatched = false;
        
        while (left <= right && right < sLen) {
            bool matched = true;
            for (unordered_map<char, int>::iterator itr = charSet.begin();
                 itr != charSet.end(); ++itr) {
                if (itr->second > charCnt[itr->first]) {
                    matched = false;
                    break;
                }
            }
            
            if (matched) {
                onceMatched = true;
                int currLen = right - left + 1;
                if (currLen < minLen) {
                    minLen = currLen;
                    minIdx = left;
                }
                if (charSet.count(s[left])) {
                    charCnt[s[left]]--;
                    if (charCnt[s[left]] == 0) charCnt.erase(s[left]);
                }
                left++;
            } else {
                right++;
                if (right < sLen && charSet.count(s[right])) {
                    charCnt[s[right]]++;
                }
            }
        }
        
        return onceMatched ? s.substr(minIdx, minLen) : "";
    }
};