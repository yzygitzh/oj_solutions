class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int preorderLen = preorder.size();
        vector<int> numStack;
        int low = (1 << 31);
        for (int i = 0; i < preorderLen; i++) {
            if (low > preorder[i]) return false;
            while (!numStack.empty() &&
                   *numStack.rbegin() < preorder[i]) {
                low = *numStack.rbegin();
                numStack.pop_back();
            }
            numStack.push_back(preorder[i]);
        }
        return true;
    }
};