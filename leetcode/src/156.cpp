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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        TreeNode *p = root, *result = root;
        vector<TreeNode *> pStack;
        while (p != nullptr){
            result = p;
            pStack.push_back(p);
            TreeNode *tmpLeft = p->left;
            p->left = nullptr;
            p = tmpLeft;
        }
        while (pStack.size() > 1) {
            TreeNode *currLeft = *pStack.rbegin();
            TreeNode *currRoot = *(++pStack.rbegin());
            pStack.pop_back();
            pStack.pop_back();
            
            currLeft->left = currRoot->right;
            currRoot->right = nullptr;
            currLeft->right = currRoot;
            
            pStack.push_back(currLeft->right);
        }
        return result;
    }
};