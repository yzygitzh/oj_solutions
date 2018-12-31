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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        
        TreeNode *p = root, *tmpP = nullptr;
        // use morris traversal
        while (p != nullptr) {
            if (p->right != nullptr) {
                tmpP = p->right;
                while (tmpP->left != nullptr && tmpP->left != p) tmpP = tmpP->left;
                if (tmpP->left == nullptr) {
                    result.push_back(p->val);
                    tmpP->left = p;
                    p = p->right;
                } else {
                    tmpP->left = nullptr;
                    p = p->left;
                }
            } else {
                result.push_back(p->val);
                p = p->left;
            }
        }
        
        reverse(result.begin(), result.end());
        
        return result;
    }
};