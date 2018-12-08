class Solution {
public:
    string decodeString(string s) {
        vector<string> strStack{""};
        vector<int> repeatStack;
        int sLen = s.length(), sIdx = 0;
        
        while (sIdx < sLen) {
            if ('0' <= s[sIdx] && '9' >= s[sIdx]) {
                int digitIdx = sIdx;
                while ('0' <= s[sIdx] && '9' >= s[sIdx]) sIdx++;
                strStack.push_back("");
                repeatStack.push_back(stoi(s.substr(digitIdx, sIdx - digitIdx)));
            } else if (s[sIdx] == ']') {
                string repeatStr = *strStack.rbegin();
                int repeatNum = *repeatStack.rbegin();
                strStack.pop_back();
                repeatStack.pop_back();
                for (int i = 0; i < repeatNum; i++) {
                    *strStack.rbegin() += repeatStr;
                }
            } else {
                *strStack.rbegin() += s[sIdx];
            }
            sIdx++;
        }
        
        return strStack[0];
    }
};