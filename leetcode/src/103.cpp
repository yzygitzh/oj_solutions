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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > result;
        vector<TreeNode*> stacks[2];
        int stackId = 0;
        
        stacks[stackId].push_back(root);
        while (stacks[stackId].size() > 0) {
            int stackIdx = stacks[stackId].size() - 1;
            vector<int> partResult;
            while (stackIdx >= 0) {
                TreeNode *p = stacks[stackId][stackIdx];
                if (p != nullptr) {
                    partResult.push_back(p->val);
                    if (stackId == 0) {
                        stacks[(stackId + 1) % 2].push_back(p->left);
                        stacks[(stackId + 1) % 2].push_back(p->right);
                    } else {
                        stacks[(stackId + 1) % 2].push_back(p->right);
                        stacks[(stackId + 1) % 2].push_back(p->left);
                    }
                }
                stackIdx--;
            }
            if (partResult.size() > 0) result.push_back(partResult);
            stacks[stackId].clear();
            stackId = (stackId + 1) % 2;
        }
        
        return result;
    }
};