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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode *> pPath;
        vector<TreeNode *> qPath;
        vector<TreeNode *> partPath;
        DFS(root, p, q, partPath, pPath, qPath);
        int currIdx = 0;
        while (currIdx < pPath.size() &&
               currIdx < qPath.size() &&
               pPath[currIdx] == qPath[currIdx]) currIdx++;;
        return pPath[currIdx - 1];
    }

    void DFS(TreeNode *root, TreeNode *p, TreeNode *q,
             vector<TreeNode *> &partPath,
             vector<TreeNode *> &pPath, vector<TreeNode *> &qPath) {
        if (root == nullptr) return;
        partPath.push_back(root);
        if (root == p) pPath = partPath;
        if (root == q) qPath = partPath;
        DFS(root->left, p, q, partPath, pPath, qPath);
        DFS(root->right, p, q, partPath, pPath, qPath);
        partPath.pop_back();
    }
};