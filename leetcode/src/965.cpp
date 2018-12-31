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
    bool isUnivalTree(TreeNode* root) {
        unordered_map<int, int> valCount;
        testTree(root, valCount);
        return valCount.size() <= 1;
    }
    
    void testTree(TreeNode *root, unordered_map<int, int> &valCount) {
        if (root == nullptr) return;
        testTree(root->left, valCount);
        if (valCount.size() > 1) return;
        testTree(root->right, valCount);
        if (valCount.size() > 1) return;
        valCount[root->val] = 1;
        return;
    }
};