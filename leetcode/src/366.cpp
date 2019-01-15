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
    unordered_map<int, vector<int>> levelToNodes;
    int maxLevel = 0;
    
    vector<vector<int>> findLeaves(TreeNode* root) {
        // sort nodes into levels
        walkTree(root);
        
        vector<vector<int>> result;
        for (int i = 1; i <= maxLevel; i++) {
            result.push_back(levelToNodes[i]);
            levelToNodes.erase(i);
        }
        return result;
    }
    
    int walkTree(TreeNode *root) {
        if (root == nullptr) return 0;
        int leftLevel = walkTree(root->left);
        int rightLevel = walkTree(root->right);
        int rootLevel = max(leftLevel, rightLevel) + 1;
        levelToNodes[rootLevel].push_back(root->val);
        maxLevel = max(maxLevel, rootLevel);
        return rootLevel;
    }
};