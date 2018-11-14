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
    int rangeSumBST(TreeNode* root, int L, int R) {
        int sum = 0;
        if (root->left != NULL && root->val > L) sum += rangeSumBST(root->left, L, R);
        if (root->right != NULL && root->val < R) sum += rangeSumBST(root->right, L, R);
        if (root->val <= R && root->val >= L) sum += root->val;
        return sum;
    }
};