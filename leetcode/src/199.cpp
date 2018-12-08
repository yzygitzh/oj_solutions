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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        queue<pair<TreeNode*, int> > bfsQ;
        bfsQ.push(make_pair(root, 0));
        
        map<int, int> rightView;
        while (!bfsQ.empty()) {
            pair<TreeNode*, int> top = bfsQ.front();
            bfsQ.pop();
            if (top.first == nullptr) continue;
            rightView[top.second] = top.first->val;
            bfsQ.push(make_pair(top.first->left, top.second + 1));
            bfsQ.push(make_pair(top.first->right, top.second + 1));
        }
        
        for (map<int, int>::iterator itr = rightView.begin();
             itr != rightView.end(); ++itr) {
            result.push_back(itr->second);
        }
        
        return result;
    }
};