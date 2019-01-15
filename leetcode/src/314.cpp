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
    map<pair<int, int>, vector<int>> nodes;
    
    vector<vector<int>> verticalOrder(TreeNode* root) {
        walkTree(root, 0, 0);
        map<int, vector<int>> resultMap;
        for (auto itr = nodes.begin(); itr != nodes.end(); ++itr) {
            for (auto itr2 = itr->second.begin();
                 itr2 != itr->second.end(); ++itr2) {
                resultMap[itr->first.first].push_back(*itr2);
            }
        }
        vector<vector<int>> result;
        for (auto itr = resultMap.begin(); itr != resultMap.end(); ++itr) {
            result.push_back(itr->second);
        }
        return result;
    }
    
    void walkTree(TreeNode *root, int row, int col) {
        if (root == nullptr) return;
        walkTree(root->left, row + 1, col - 1);
        nodes[make_pair(col, row)].push_back(root->val);
        walkTree(root->right, row + 1, col + 1);
    }
};