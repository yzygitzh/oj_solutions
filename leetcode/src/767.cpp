class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> charCnt;
        for (auto c : S) {
            charCnt[c]++;
        }
        string result;
        while (charCnt.size() > 0) {
            char lastChar = '#';
            if (result.length() > 0) {
                lastChar = result.back();
            }
            char nextChar;
            int maxCnt = 0;
            for (auto& p : charCnt) {
                if (lastChar != p.first && maxCnt < p.second) {
                    nextChar = p.first;
                    maxCnt = p.second;
                }
            }
            if (maxCnt == 0) {
                return "";
            }
            result += nextChar;
            charCnt[nextChar]--;
            if (charCnt[nextChar] == 0) {
                charCnt.erase(nextChar);
            }
        }
        return result;
    }
};