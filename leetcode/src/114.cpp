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
    void flatten(TreeNode* root) {
        TreeNode *tmp = root;
        while (root != nullptr) {
            if (root->left != nullptr) {
                tmp = root->left;
                while (tmp->right != root && tmp->right != nullptr) {
                    tmp = tmp->right;
                }
                if (tmp->right == root) {
                    tmp->right = root->right;
                    root->right = root->left;
                    root->left = nullptr;
                    root = tmp->right;
                } else {
                    tmp->right = root;
                    root = root->left;
                }
            } else {
                root = root->right;
            }
        }
    }
};