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
        vector<TreeNode*> nodeStack;
        // find leftmost element
        TreeNode *p = root;
        while (p != nullptr) {
            nodeStack.push_back(p);
            p = p->left;
        }
        
        while (!nodeStack.empty()) {
            p = nodeStack.back();
            // invariant: top's left has been visited
            if (p->right != nullptr) {
                // find top's right's leftmost
                p = p->right;
                while (p != nullptr) {
                    nodeStack.push_back(p);
                    p = p->left;
                }
            } else {
                // top's right has been visited, now access top
                result.push_back(p->val);
                nodeStack.pop_back();
                // until being some node's left subtree
                while (!nodeStack.empty() && nodeStack.back()->right == p) {
                    p = nodeStack.back();
                    result.push_back(p->val);
                    nodeStack.pop_back();
                }
            }
        }
        
        return result;
    }
};