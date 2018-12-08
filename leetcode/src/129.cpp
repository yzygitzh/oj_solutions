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
    int sum = 0;
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) return sum;
        walkTree(root, 0);
        return sum;
    }
    void walkTree(TreeNode *root, int partSum) {
        // invariant: root != nullptr
        partSum = partSum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            sum += partSum;
        } else {
            if (root->left != nullptr) walkTree(root->left, partSum);
            if (root->right != nullptr) walkTree(root->right, partSum);
        }
    }
};