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
    int result = 0;
    
    int countUnivalSubtrees(TreeNode* root) {
        doCount(root);
        return result;
    }
    
    bool doCount(TreeNode* root) {
        if (root == nullptr) return false;
        int leftCnt = doCount(root->left);
        int rightCnt = doCount(root->right);
        
        if ((leftCnt > 0 && root->val == root->left->val ||
             root->left == nullptr) &&
            (rightCnt > 0 && root->val == root->right->val ||
             root->right == nullptr)) {
            result += 1;
            return true;
        } else {
            return false;
        }
    }
};