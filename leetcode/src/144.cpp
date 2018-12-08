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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<TreeNode*> nodeStack;
        vector<int> seenStack;
        
        nodeStack.push_back(root);
        seenStack.push_back(0);
        
        vector<int> result;
        
        while (nodeStack.size() > 0) {
            int stackIdx = nodeStack.size() - 1;
            TreeNode *currP = *nodeStack.rbegin();
            if (currP == nullptr || seenStack[stackIdx] == 2) {
                nodeStack.pop_back();
                seenStack.pop_back();
            } else if (seenStack[stackIdx] == 0) {
                result.push_back(currP->val);
                seenStack[stackIdx] = 1;
                nodeStack.push_back(currP->left);
                seenStack.push_back(0);
            } else if (seenStack[stackIdx] == 1) {
                seenStack[stackIdx] = 2;
                nodeStack.push_back(currP->right);
                seenStack.push_back(0);
            }
        }
        
        return result;
    }
};