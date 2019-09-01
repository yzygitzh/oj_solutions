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
    // tree dp
    unordered_map<TreeNode*, pair<int, int>> nodeToMinMax;
    int maxAncestorDiff(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftMaxDiff = maxAncestorDiff(root->left);
        int rightMaxDiff = maxAncestorDiff(root->right);
        
        int rootMinVal = root->val;
        if (root->left != nullptr) {
            rootMinVal = min(rootMinVal, nodeToMinMax[root->left].first);
        }
        if (root->right != nullptr) {
            rootMinVal = min(rootMinVal, nodeToMinMax[root->right].first);
        }
        
        int rootMaxVal = root->val;
        if (root->left != nullptr) {
            rootMaxVal = max(rootMaxVal, nodeToMinMax[root->left].second);
        }
        if (root->right != nullptr) {
            rootMaxVal = max(rootMaxVal, nodeToMinMax[root->right].second);
        }
        
        nodeToMinMax[root].first = rootMinVal;
        nodeToMinMax[root].second = rootMaxVal;
        
        return max(max(leftMaxDiff, rightMaxDiff),
                   max(abs(root->val - rootMinVal), abs(root->val - rootMaxVal)));
    }
};