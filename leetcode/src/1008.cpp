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
    TreeNode* buildBST(vector<int>& preorder, int left, int right) {
        if (left > right) {
            return nullptr;
        } else if (left == right) {
            return new TreeNode(preorder[left]);
        } else {
            TreeNode *result = new TreeNode(preorder[left]);
            left++;
            int rightSubIdx = left;
            while (rightSubIdx <= right && preorder[rightSubIdx] < result->val) {
                rightSubIdx++;
            }
            result->left = buildBST(preorder, left, rightSubIdx - 1);
            result->right = buildBST(preorder, rightSubIdx, right);
            return result;
        }
    }
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return buildBST(preorder, 0, preorder.size() - 1);
    }
};