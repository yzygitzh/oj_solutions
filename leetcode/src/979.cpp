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
    int result = 0;
    
    int distributeCoins(TreeNode* root) {
        walkAssign(root);
        return result;
    }
    
    int getAbs(int x) {
        return x < 0 ? -x : x;
    }
    
    // return: <0, need coins, >0, redundant coins
    int walkAssign(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftCost = walkAssign(root->left);
        int rightCost = walkAssign(root->right);
        
        result += getAbs(leftCost);
        result += getAbs(rightCost);
        int rootCost = leftCost + rightCost + root->val - 1;
        return rootCost;
    }
};