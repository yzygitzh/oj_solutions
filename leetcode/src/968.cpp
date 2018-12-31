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
    int globalMin = 0;
    int minCameraCover(TreeNode* root) {
        if (root == nullptr) return 0;
        int rootCover = walkTree(root);
        if (rootCover == 0) globalMin += 1;
        return globalMin;
    }
    
    // 0: not covered
    // 1: covered w/ camera
    // 2: covered w/o camera
    // 3: nullptr
    int walkTree(TreeNode *root) {
        int leftState = 3, rightState = 3;
        if (root->left != nullptr) leftState = walkTree(root->left);
        if (root->right != nullptr) rightState = walkTree(root->right);
        
        if (leftState == 0 || rightState == 0) {
            globalMin += 1;
            return 1;
        }
        if (leftState >= 2 && rightState >= 2) return 0;
        return 2;
    }
};