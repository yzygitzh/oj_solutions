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
    int rob(TreeNode* root) {
        // <p, N> at most N money can be robbed when robbing subtree p
        unordered_map<TreeNode*, int> memo;
        return robSum(root, memo);
    }
    
    int robSum(TreeNode *root, unordered_map<TreeNode*, int> &memo) {
        if (root == nullptr) return 0;
        if (memo.find(root) != memo.end()) return memo[root];
        // use root
        int sum1 = root->val;
        if (root->left != nullptr) {
            sum1 += robSum(root->left->left, memo);
            sum1 += robSum(root->left->right, memo);
        }
        if (root->right != nullptr) {
            sum1 += robSum(root->right->left, memo);
            sum1 += robSum(root->right->right, memo);
        }
        // don't use root
        int sum2 = robSum(root->left, memo) + robSum(root->right, memo);
        
        int maxSum = sum1 > sum2 ? sum1 : sum2;
        memo[root] = maxSum;
        return maxSum;
    }
};