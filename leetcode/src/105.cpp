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
    unordered_map<int, int> valToIdxIn;
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int orderLen = preorder.size();
        for (int i = 0; i < orderLen; i++) {
            valToIdxIn[inorder[i]] = i;
        }
        return construct(preorder, 0, orderLen - 1,
                         inorder, 0, orderLen - 1);
    }
    
    TreeNode* construct(vector<int>& preorder, int pre1, int pre2,
                        vector<int>& inorder, int in1, int in2) {
        if (pre1 > pre2 || in1 > in2) return nullptr;
        int rootVal = preorder[pre1];
        int rootIdxIn = valToIdxIn[rootVal];
        int leftLen = rootIdxIn - in1, rightLen = in2 - rootIdxIn;
        TreeNode *root = new TreeNode(rootVal);
        root->left = construct(preorder, pre1 + 1, pre1 + leftLen,
                               inorder, in1, rootIdxIn - 1);
        root->right = construct(preorder, pre1 + leftLen + 1, pre2,
                                inorder, rootIdxIn + 1, in2);
        return root;
    }
};