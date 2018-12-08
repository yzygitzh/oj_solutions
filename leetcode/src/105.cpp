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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        // root is preorder[0]
        int rootInorderIdx = 0;
        while (inorder[rootInorderIdx] != preorder[0]) rootInorderIdx++;

        TreeNode *root = new TreeNode(preorder[0]);
        vector<int> leftPre, leftIn, rightPre, rightIn;
        int preIdx = 1;
        
        for (int i = 0; i < rootInorderIdx; i++) {
            leftIn.push_back(inorder[i]);
            leftPre.push_back(preorder[preIdx++]);
        }
        for (int i = rootInorderIdx + 1; i < inorder.size(); i++) {
            rightIn.push_back(inorder[i]);
            rightPre.push_back(preorder[preIdx++]);
        }
        
        root->left = buildTree(leftPre, leftIn);
        root->right = buildTree(rightPre, rightIn);
        return root;
    }
};