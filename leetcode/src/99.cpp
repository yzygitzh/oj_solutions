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
    void recoverTree(TreeNode* root) {
        if (root == nullptr) return;
        // use in-order morris traversal
        TreeNode *p = root, *tmpP, *lastP = nullptr;
        int lastVal = p->val;
        TreeNode *badPtrs[2] = {nullptr, nullptr};
        while (p != nullptr) {
            if (p->left != nullptr) {
                tmpP = p->left;
                while (tmpP->right != nullptr && tmpP->right != p) tmpP = tmpP->right;
                if (tmpP->right == nullptr) {
                    tmpP->right = p;
                    p = p->left;
                } else {
                    tmpP->right = nullptr;
                    if (p->val < lastP->val) {
                        if (badPtrs[0] == nullptr) {
                            badPtrs[0] = lastP;
                            badPtrs[1] = p;
                        }
                        else badPtrs[1] = p;
                    }
                    lastP = p;
                    p = p->right;
                }
            } else {
                if (lastP == nullptr) lastP = p;
                if (p->val < lastP->val) {
                    if (badPtrs[0] == nullptr) {
                        badPtrs[0] = lastP;
                        badPtrs[1] = p;
                    }
                    else badPtrs[1] = p;
                }
                lastP = p;
                p = p->right;
            }
        }
        badPtrs[0]->val = badPtrs[0]->val ^ badPtrs[1]->val;
        badPtrs[1]->val = badPtrs[0]->val ^ badPtrs[1]->val;
        badPtrs[0]->val = badPtrs[0]->val ^ badPtrs[1]->val;
        
        return;
    }
};