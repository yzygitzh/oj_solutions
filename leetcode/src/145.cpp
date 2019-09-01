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
        vector<TreeNode* > nodeStack;
        vector<int> result;
        TreeNode *p = root;
        while (p != nullptr) {
            nodeStack.push_back(p);
            p = p->left;
        }
        while (!nodeStack.empty()) {
            // invariant: top's left sub-tree has been visited
            p = nodeStack.back();
            if (p->right != nullptr) {
                p = p->right;
                while (p != nullptr) {
                    nodeStack.push_back(p);
                    p = p->left;
                }
            } else {
                // both left sub-tree and right sub-tree have been visited
                p = nullptr;
                while (!nodeStack.empty() &&
                       nodeStack.back()->right == p) {
                    p = nodeStack.back();
                    result.push_back(p->val);
                    nodeStack.pop_back();
                }
            }
        }
        return result;
    }
};