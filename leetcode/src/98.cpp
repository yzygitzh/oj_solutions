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
    struct TreeInfo {
        int minVal, maxVal;
        bool isValid;
    };
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        TreeInfo bstInfo = checkBST(root);
        return bstInfo.isValid;
    }
    TreeInfo checkBST(TreeNode *root) {
        TreeInfo result;
        result.minVal = result.maxVal = root->val;
        result.isValid = false;
        if (root->left != nullptr) {
            TreeInfo leftInfo = checkBST(root->left);
            if (!leftInfo.isValid || leftInfo.maxVal >= root->val) return result;
            result.minVal = leftInfo.minVal;
        }
        if (root->right != nullptr) {
            TreeInfo rightInfo = checkBST(root->right);
            if (!rightInfo.isValid || rightInfo.minVal <= root->val) return result;
            result.maxVal = rightInfo.maxVal;
        }
        result.isValid = true;
        return result;
    }
};