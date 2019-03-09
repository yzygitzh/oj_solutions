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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        } else if (root->val < val) {
            TreeNode *result = new TreeNode(val);
            result->left = root;
            return result;
        } else {
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
    }
};