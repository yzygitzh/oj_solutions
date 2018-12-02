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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL && root2 == NULL) {
            return true;
        } else if (root1 == NULL || root2 == NULL) {
            return false;
        } else {
            bool equalVal = (root1->val == root2->val);
            bool nonFlip = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
            bool doFlip = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);
            return equalVal && (nonFlip || doFlip);
        }
    }
};