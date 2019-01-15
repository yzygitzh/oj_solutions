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
    int globalMax = 0;
    
    int longestConsecutive(TreeNode* root) {
        walkTree(root);
        return globalMax;
    }
    
    int walkTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftLen = walkTree(root->left);
        int rightLen = walkTree(root->right);
        int currMax = 1;
        if (leftLen > 0 && root->left->val - 1 == root->val) {
            currMax = max(currMax, 1 + leftLen);
        }
        if (rightLen > 0 && root->right->val - 1 == root->val) {
            currMax = max(currMax, 1 + rightLen);
        }
        globalMax = max(globalMax, currMax);
        return currMax;
    }
};