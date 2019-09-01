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
    unordered_map<int, unordered_set<int>> adjList;
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        // convert tree to a graph
        walkTree(root);
        vector<int> result;
        vector<int> visited(510, 0);
        queue<pair<int, int>> bfsQ;
        bfsQ.push(make_pair(target->val, 0));
        visited[target->val] = 1;
        while (!bfsQ.empty()) {
            pair<int, int> state = bfsQ.front();
            bfsQ.pop();
            if (state.second == K + 1) {
                break;
            }
            if (state.second == K) {
                result.push_back(state.first);
            }
            for (auto node : adjList[state.first]) {
                if (!visited[node]) {
                    visited[node] = 1;
                    bfsQ.push(make_pair(node, state.second + 1));
                }
            }
        }
        return result;
    }
    
    void walkTree(TreeNode *p) {
        if (p->left != nullptr) {
            adjList[p->val].insert(p->left->val);
            adjList[p->left->val].insert(p->val);
            walkTree(p->left);
        }
        if (p->right != nullptr) {
            adjList[p->val].insert(p->right->val);
            adjList[p->right->val].insert(p->val);
            walkTree(p->right);
        }
    }
};