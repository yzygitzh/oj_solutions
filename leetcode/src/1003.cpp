class Solution {
public:
    bool isValid(string S) {
        vector<string> abcStack;
        for (auto c : S) {
            if (c == 'a') {
                abcStack.push_back(string() + c);
            } else if (!abcStack.empty() && abcStack.back() == "a" && c == 'b') {
                abcStack.back() = "ab";
            } else if (!abcStack.empty() && abcStack.back() == "ab" && c == 'c') {
                abcStack.pop_back();
            } else {
                return false;
            }
        }
        return abcStack.empty();
    }
};