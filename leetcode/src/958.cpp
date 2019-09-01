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
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        bool noChild = false;
        queue<TreeNode*> bfsQ;
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            TreeNode* node = bfsQ.front();
            bfsQ.pop();
            if (noChild) {
                if (node->left != nullptr || node->right != nullptr) {
                    return false;
                }
            } else {
                if (node->left == nullptr && node->right == nullptr) {
                    noChild = true;
                } else if (node->left == nullptr) {
                    return false;
                } else {
                    bfsQ.push(node->left);
                    if (node->right != nullptr) {
                        bfsQ.push(node->right);
                    } else {
                        noChild = true;
                    }
                }
            }
        }
        return true;
    }
};