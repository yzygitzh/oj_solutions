/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<TreeNode*> nodeStack{root};
        vector<int> seenStack{0};
        vector<int> result;
        while (nodeStack.size() > 0) {
            int stackSize = nodeStack.size();
            TreeNode *currP = nodeStack[stackSize - 1];
            if (currP == nullptr || seenStack[stackSize - 1] == 2) {
                nodeStack.pop_back();
                seenStack.pop_back();
            } else if (seenStack[stackSize - 1] == 0) {
                seenStack[stackSize - 1] = 1;
                nodeStack.push_back(currP->left);
                seenStack.push_back(0);
            } else if (seenStack[stackSize - 1] == 1) {
                seenStack[stackSize - 1] = 2;
                result.push_back(currP->val);
                nodeStack.push_back(currP->right);
                seenStack.push_back(0);
            }
        }
        return result;
    }
};