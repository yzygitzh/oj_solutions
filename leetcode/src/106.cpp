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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (postorder.size() == 0) return nullptr;
        // root is postorder[-1]
        int rootInorderIdx = 0;
        while (inorder[rootInorderIdx] != postorder[postorder.size() - 1]) {
            rootInorderIdx++;   
        }

        TreeNode *root = new TreeNode(postorder[postorder.size() - 1]);
        vector<int> leftPost, leftIn, rightPost, rightIn;
        int postIdx = 0;
        
        for (int i = 0; i < rootInorderIdx; i++) {
            leftIn.push_back(inorder[i]);
            leftPost.push_back(postorder[postIdx++]);
        }
        for (int i = rootInorderIdx + 1; i < inorder.size(); i++) {
            rightIn.push_back(inorder[i]);
            rightPost.push_back(postorder[postIdx++]);
        }
        
        root->left = buildTree(leftIn, leftPost);
        root->right = buildTree(rightIn, rightPost);
        return root;
    }
};