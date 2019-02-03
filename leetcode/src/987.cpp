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
    map<int, vector<pair<int, int>>> resultMap;
    vector<vector<int>> resultVec;
    
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        walkTree(root, 0, 0);
        
        for (auto itr = resultMap.begin(); itr != resultMap.end(); ++itr) {
            sort(itr->second.begin(), itr->second.end());
            vector<int> currCol;
            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2) {
                currCol.push_back(itr2->second);
            }
            resultVec.push_back(currCol);
        }
        return resultVec;
    }
    
    void walkTree(TreeNode *root, int x, int y) {
        if (root == nullptr) return;
        walkTree(root->left, x - 1, y + 1);
        walkTree(root->right, x + 1, y + 1);
        resultMap[x].push_back(make_pair(y, root->val));
    }
};