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
    int xParent, yParent, xDepth = -1, yDepth = -1;
    bool isCousins(TreeNode* root, int x, int y) {
        walkTree(root, x, y, 0);
        return xDepth >= 0 && yDepth >= 0 && xDepth == yDepth && xParent != yParent;
    }
    
    void walkTree(TreeNode* root, int x, int y, int depth) {
        if (root == nullptr) return;
        if (root->left != nullptr) {
            if (root->left->val == x) {
                xParent = root->val;
                xDepth = depth + 1;
            }
            if (root->left->val == y) {
                yParent = root->val;
                yDepth = depth + 1;
            }
            walkTree(root->left, x, y, depth + 1);
        }
        if (root->right != nullptr) {
            if (root->right->val == x) {
                xParent = root->val;
                xDepth = depth + 1;
            }
            if (root->right->val == y) {
                yParent = root->val;
                yDepth = depth + 1;
            }
            walkTree(root->right, x, y, depth + 1);
        }
    }
};