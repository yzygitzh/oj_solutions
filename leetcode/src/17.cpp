class Solution {
public:
    int digit2int(char c) {
        return c - '0';
    }
    
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        int digitsLen = digits.length();
        if (digitsLen == 0) return result;
        
        vector<string> digitMap = {"abc", "def", "ghi", "jkl", "mno",
                                   "pqrs", "tuv", "wxyz"};
        queue<string> bfsQ;
        int currDigit = digit2int(digits[0]);
        for (int i = 0; i < digitMap[currDigit - 2].length(); i++) {
            bfsQ.push(digitMap[currDigit - 2].substr(i, 1));
        }
        
        while (!bfsQ.empty()) {
            string top = bfsQ.front();
            bfsQ.pop();
            if (top.length() == digitsLen) {
                result.push_back(top);
            } else {
                currDigit = digit2int(digits[top.length()]);
                for (int i = 0; i < digitMap[currDigit - 2].length(); i++) {
                    bfsQ.push(top + digitMap[currDigit - 2][i]);
                }
            }
        }
        return result;
    }
};