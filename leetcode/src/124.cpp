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
    unordered_map<TreeNode*, int> memo;
    int maxSum = (1 << 31);
    
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int maxPathSum(TreeNode* root) {
        maxSinglePathSum(root);
        return maxSum;
    }
    
    int maxSinglePathSum(TreeNode* root) {
        if (root == nullptr) return 0;
        if (memo.find(root) == memo.end()) {
            int leftSum = maxSinglePathSum(root->left);
            int rightSum = maxSinglePathSum(root->right);
            int singlePathSum = getMax(root->val,
                                 getMax(root->val + leftSum,
                                        root->val + rightSum));
            memo[root] = singlePathSum;
            
            // find max double path sum here
            maxSum = getMax(maxSum, getMax(singlePathSum,
                                           root->val + leftSum + rightSum));
        }
        return memo[root];
    }
};