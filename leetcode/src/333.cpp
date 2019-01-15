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
    unordered_map<TreeNode*, pair<int, int>> nodeToMinMax;
    int result;
    
    int largestBSTSubtree(TreeNode* root) {
        result = 0;
        walkTree(root);
        return result;
    }
    
    int walkTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftSize = walkTree(root->left);
        int rightSize = walkTree(root->right);
        int rootSize = 0;
        // calculate min and max
        if ((root->left == nullptr ||
             leftSize > 0 &&
             root->val > nodeToMinMax[root->left].second) &&
            (root->right == nullptr ||
             rightSize > 0 &&
             root->val < nodeToMinMax[root->right].first)) {
            rootSize = leftSize + rightSize + 1;
            nodeToMinMax[root].first = root->left == nullptr ?
                                       root->val :
                                       nodeToMinMax[root->left].first;
            nodeToMinMax[root].second = root->right == nullptr ?
                                        root->val :
                                        nodeToMinMax[root->right].second;
            result = max(result, rootSize);
        }
        return rootSize;
    }
};