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
    // 0: supervised w/o camera, 1: supervised w/ camera, 2: not supervised
    int minCameraCover(TreeNode* root) {
        vector<int> result = walkTree(root);
        return min(result[0], result[1]);
    }
    
    vector<int> walkTree(TreeNode* root) {
        vector<int> result(3, 0);
        if (root != nullptr) {
            vector<int> leftResult = walkTree(root->left);
            vector<int> rightResult = walkTree(root->right);
            
            // root supervised w/o camera
            result[0] = min(min(leftResult[0] + rightResult[1],
                                leftResult[1] + rightResult[0]),
                            leftResult[1] + rightResult[1]);
            
            // root supervised w/ camera
            result[1] = min(min(leftResult[0], leftResult[1]), leftResult[2]) +
                        min(min(rightResult[0], rightResult[1]), rightResult[2]) + 1;
            
            // only root not supervised
            result[2] = leftResult[0] + rightResult[0];
        } else {
            result[1] = 10000;
        }
        return result;
    }
};