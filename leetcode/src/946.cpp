class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int seqLen = pushed.size();
        vector<int> tmpStack;
        int pushIdx = 0, popIdx = 0;
        while (pushIdx < seqLen || tmpStack.size() > 0) {
            if (pushIdx < seqLen && pushed[pushIdx] == popped[popIdx]) {
                popIdx++;
                pushIdx++;
            } else if (tmpStack.size() > 0 &&
                       *tmpStack.rbegin() == popped[popIdx]) {
                tmpStack.pop_back();
                popIdx++;
            } else if (pushIdx < seqLen) {
                tmpStack.push_back(pushed[pushIdx]);
                pushIdx++;
            } else {
                return false;
            }
        }
        return popIdx == seqLen;
    }
};