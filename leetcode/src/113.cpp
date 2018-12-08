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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> partResult;
        vector<vector<int> > result;
        if (root == nullptr) return result;
        genPath(root, sum, partResult, result);
        return result;
    }
    
    void genPath(TreeNode *root, int sum,
                 vector<int> &partResult, vector<vector<int> > &result) {
        // invariant: root != nullptr
        partResult.push_back(root->val);
        sum -= root->val;
        if (root->left == nullptr && root->right == nullptr) {
            if (sum == 0) result.push_back(partResult);
        } else {
            if (root->left != nullptr) genPath(root->left, sum,
                                               partResult, result);
            if (root->right != nullptr) genPath(root->right, sum,
                                                partResult, result);
        }
        partResult.pop_back();
    }
};