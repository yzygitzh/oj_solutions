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
    // node id, path length
    vector<pair<int, int>> pathToTarget;
    bool targetFound;

    int findClosestLeaf(TreeNode* root, int k) {
        targetFound = false;
        walkTree(root, k);
        pair<int, int> result = make_pair(-1, 0x10000);
        for (int i = 0; i < pathToTarget.size(); i++) {
            if (pathToTarget[i].second + pathToTarget.size() - i - 1 < result.second) {
                result.first = pathToTarget[i].first;
                result.second = pathToTarget[i].second + pathToTarget.size() - i - 1;    
            }
        }
        return result.first;
    }

    pair<int, int> walkTree(TreeNode *p, int target) {
        int pushIdx = -1;
        if (!targetFound) {
            pathToTarget.push_back(make_pair(0, 0));
            pushIdx = pathToTarget.size() - 1;
            if (p->val == target) {
                targetFound = true;
            }
        }
        
        pair<int, int> result = make_pair(-1, 0x10000);
        pair<int, int> leftClosest = p->left == nullptr ? result : walkTree(p->left, target);
        pair<int, int> rightClosest = p->right == nullptr ? result : walkTree(p->right, target);
        if (leftClosest.second < result.second) {
            result = leftClosest;
            result.second += 1;
        }
        if (rightClosest.second < result.second) {
            result = rightClosest;
            result.second += 1;
        }
        // p is leaf
        if (result.second >= 0x10000) {
            result = make_pair(p->val, 1);
        }

        if (!targetFound) {
            pathToTarget.pop_back();
        } else {
            if (pushIdx >= 0) {
                pathToTarget[pushIdx] = result;
            }
        }
        return result;
    }
};