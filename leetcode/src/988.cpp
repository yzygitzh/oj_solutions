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
    string smallestFromLeaf(TreeNode* root) {
        if (root == nullptr) return "";
        string leftStr = smallestFromLeaf(root->left);
        string rightStr = smallestFromLeaf(root->right);
        string prefix;
        if (leftStr == "" && rightStr == "") {
            // is leaf, do nothing
        } else if (leftStr == "") {
            prefix = rightStr;
        } else if (rightStr == "") {
            prefix = leftStr;
        } else {
            prefix = leftStr < rightStr ? leftStr : rightStr;
        }
        prefix += (char)('a' + root->val);
        return prefix;
    }
};