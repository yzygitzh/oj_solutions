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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<pair<TreeNode*, int> > bfsQ;
        map<int, vector<int> > levelNodes;
        bfsQ.push(make_pair(root, 0));
        
        while (!bfsQ.empty()) {
            pair<TreeNode*, int> top = bfsQ.front();
            bfsQ.pop();
            if (top.first == nullptr) continue;
            levelNodes[top.second].push_back(top.first->val);
            bfsQ.push(make_pair(top.first->left, top.second + 1));
            bfsQ.push(make_pair(top.first->right, top.second + 1));
        }
        
        vector<vector<int> > result;
        for (map<int, vector<int> >::iterator itr = levelNodes.begin();
             itr != levelNodes.end(); ++itr) {
            result.push_back(itr->second);
        }
        return result;
    }
};