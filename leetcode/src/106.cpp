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
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int orderLen = postorder.size();
        for (int i = 0; i < orderLen; i++) {
            valToIdxIn[inorder[i]] = i;
        }
        return construct(postorder, 0, orderLen - 1,
                         inorder, 0, orderLen - 1);
    }
    
    TreeNode* construct(vector<int>& postorder, int pre1, int pre2,
                        vector<int>& inorder, int in1, int in2) {
        if (pre1 > pre2 || in1 > in2) return nullptr;
        int rootVal = postorder[pre2];
        int rootIdxIn = valToIdxIn[rootVal];
        int leftLen = rootIdxIn - in1, rightLen = in2 - rootIdxIn;
        TreeNode *root = new TreeNode(rootVal);
        root->left = construct(postorder, pre1, pre1 + leftLen - 1,
                               inorder, in1, rootIdxIn - 1);
        root->right = construct(postorder, pre1 + leftLen, pre2 - 1,
                                inorder, rootIdxIn + 1, in2);
        return root;
    }
};