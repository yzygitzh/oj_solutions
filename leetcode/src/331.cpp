class Solution {
public:
    bool isValidSerialization(string preorder) {
        if (preorder == "#") return true;
        int pLen = preorder.length();
        int pIdx = 0;
        vector<int> seenStack;
        while (pIdx < pLen) {
            if (preorder[pIdx] == '#') {
                if (seenStack.size() > 0) {
                    int stackIdx = seenStack.size() - 1;
                    if (seenStack[stackIdx] == 0) {
                        seenStack[stackIdx] = 1;
                    } else if (seenStack[stackIdx] == 1) {
                        while (seenStack.size() > 0 && *seenStack.rbegin() == 1) {
                            seenStack.pop_back();
                        }
                        if (seenStack.size() > 0) {
                            *seenStack.rbegin() = 1;
                        }
                    }
                } else {
                    return false;
                }
            } else {
                seenStack.push_back(0);
            }
            while (pIdx < pLen && preorder[pIdx] != ',') pIdx++;
            pIdx++;
            if (seenStack.size() == 0) break;
        }
        return seenStack.size() == 0 && pIdx >= pLen;
    }
};