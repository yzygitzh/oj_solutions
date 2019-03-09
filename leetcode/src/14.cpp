class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result = "";
        int idx = 0;
        while (true) {
            bool outOfRange = false;
            unordered_set<char> currentChars;
            for (auto& str: strs) {
                if (idx >= str.length()) {
                    outOfRange = true;
                    break;
                } else {
                    currentChars.insert(str[idx]);
                    if (currentChars.size() > 1) {
                        break;
                    }
                }
            }
            if (!outOfRange && currentChars.size() == 1) {
                result += *currentChars.begin();
                idx++;
            } else {
                break;
            }
        }
        return result;
    }
};