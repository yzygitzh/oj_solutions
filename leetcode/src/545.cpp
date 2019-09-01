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
    vector<int> result;
    
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        walkTree(root, true, true, true);
        return result;
    }
    
    void walkTree(TreeNode *p, bool leftBound, bool rightBound, bool isRoot) {
        if (p == nullptr) {
            return;
        }
        bool pushLater = false;
        bool isLeaf = p->left == nullptr && p->right == nullptr;
        if (isRoot) {
            // root
            result.push_back(p->val);
        } else if (leftBound) {
            // left bound
            result.push_back(p->val);
        } else if (rightBound) {
            // right bound, push later
            pushLater = true;
        } else if (isLeaf) {
            // leaf
            result.push_back(p->val);
        }
        // if right bound is inherited, p is not root. left bound is the same.
        walkTree(p->left, leftBound, rightBound && p->right == nullptr && !isRoot, false);
        walkTree(p->right, leftBound && p->left == nullptr && !isRoot, rightBound, false);
        if (pushLater) {
            result.push_back(p->val);
        }
    }
};