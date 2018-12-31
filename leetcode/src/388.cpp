class Solution {
public:
    int lengthLongestPath(string input) {
        int inputLen = input.size();
        vector<string> pathStack;
        int maxLen = 0;
        int currLen = 0;
        for (int i = 0; i < inputLen; i++) {
            // invariant: (\t*)filename(\n)
            int depth = 0;
            while (input[i] == '\t') {
                depth++;
                i++;
            }
            string field;
            while (i < inputLen && input[i] != '\n') {
                field += input[i];
                i++;
            }
            while (pathStack.size() != depth) {
                currLen -= pathStack.rbegin()->length() + 1;
                pathStack.pop_back();
            }
            currLen += field.length() + 1;
            pathStack.push_back(field);
            if (field.find('.') != -1 && currLen > maxLen) maxLen = currLen;
        }
        return maxLen > 0 ? maxLen - 1 : maxLen;
    }
};