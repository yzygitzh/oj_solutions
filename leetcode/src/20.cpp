class Solution {
public:
    bool isValid(string s) {
        char lastLeft;
        vector<char> charStack;
        for (auto c : s) {
            if (c == '(' || c == '{' || c == '[') {
                charStack.push_back(c);
            } else if (c == ')') {
                if (charStack.size() == 0 ||
                    *charStack.rbegin() != '(') return false;
                else charStack.pop_back();
            } else if (c == '}') {
                if (charStack.size() == 0 ||
                    *charStack.rbegin() != '{') return false;
                else charStack.pop_back();
            } else if (c == ']') {
                if (charStack.size() == 0 ||
                    *charStack.rbegin() != '[') return false;
                else charStack.pop_back();
            }
        }
        return charStack.size() == 0;
    }
};