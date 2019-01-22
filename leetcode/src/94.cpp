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
        vector<int> result;
        while (root != nullptr) {
            if (root->left == nullptr) {
                result.push_back(root->val);
                root = root->right;
            } else {
                TreeNode *tmp;
                tmp = root->left;
                while (tmp->right != nullptr && tmp->right != root) {
                    tmp = tmp->right;
                }
                if (tmp->right == nullptr) {
                    tmp->right = root;
                    root = root->left;
                } else {
                    tmp->right = nullptr;
                    result.push_back(root->val);
                    root = root->right;
                }
            }
        }
        return result;
    }
};