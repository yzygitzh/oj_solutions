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
    bool pFound = false, succFound = false;
    TreeNode* result = nullptr;

    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p == nullptr) return nullptr;
        walkTree(root, p);
        return result;
    }
    
    void walkTree(TreeNode *root, TreeNode *p) {
        if (succFound) return;
        if (root == nullptr) return;
        
        walkTree(root->left, p);
        
        if (root == p) {
            pFound = true;
        } else if (pFound && !succFound) {
            succFound = true;
            result = root;
        }
        
        walkTree(root->right, p);
    }
};