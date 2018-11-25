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
    int currK = 0, queryK;
    int result = 0;
    int kthSmallest(TreeNode* root, int k) {
        queryK = k;
        walkBST(root);
        return result;
    }
    void walkBST(TreeNode *root) {
        if (root == NULL) return;
        walkBST(root->left);
        currK++;
        if (currK == queryK) {
            result = root->val;
        }
        walkBST(root->right);
    }
};