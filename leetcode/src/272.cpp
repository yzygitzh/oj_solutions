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
    vector<TreeNode*> targetStack;
    
    double getAbs(double x) {
        return x < 0 ? -x : x;
    }
    
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        findTarget(root, target);
        vector<int> leftK = iterK(k + 1, true);
        vector<int> rightK = iterK(k + 1, false);
        int lIdx = 0, rIdx = 0, lLen = leftK.size(), rLen = rightK.size();
        if (leftK[0] > target) lIdx++;
        else rIdx++;
        vector<int> result;
        for (int i = 0; i < k; i++) {
            if (lIdx == lLen ||
                lIdx < lLen && rIdx < rLen > 0 &&
                getAbs((double)leftK[lIdx] - target) >
                getAbs((double)rightK[rIdx] - target)) {
                result.push_back(rightK[rIdx]);
                rIdx++;
            } else {
                result.push_back(leftK[lIdx]);
                lIdx++;
            }
        }
        return result;
    }
    
    vector<int> iterK(int k, bool toLeft) {
        vector<TreeNode*> nodeStack = targetStack;
        vector<int> result;
        for (int i = 0; i < k; i++) {
            // invariant: should visit stack top, and try visit left (if toLeft)
            if (nodeStack.empty()) break;
            TreeNode *p = *nodeStack.rbegin();
            result.push_back(p->val);
            
            if (toLeft) {
                if (p->left != nullptr) {
                    p = p->left;
                    // find biggest value in left subtree
                    while (p != nullptr) {
                        nodeStack.push_back(p);
                        p = p->right;
                    }
                } else {
                    nodeStack.pop_back();
                    // while it's the smallest value in the subtree
                    while (!nodeStack.empty() &&
                           p == (*nodeStack.rbegin())->left) {
                        p = *nodeStack.rbegin();
                        nodeStack.pop_back();
                    }
                }
            } else {
                if (p->right != nullptr) {
                    p = p->right;
                    while (p != nullptr) {
                        nodeStack.push_back(p);
                        p = p->left;
                    }
                } else {
                    nodeStack.pop_back();
                    while (!nodeStack.empty() &&
                           p == (*nodeStack.rbegin())->right) {
                        p = *nodeStack.rbegin();
                        nodeStack.pop_back();
                    }
                }                
            }
        }
        return result;
    }

    void findTarget(TreeNode* root, double target) {
        if (root == nullptr) return;
        targetStack.push_back(root);
        if ((double)root->val < target) {
            findTarget(root->right, target);
        } else if ((double)root->val > target) {
            findTarget(root->left, target);
        }
    }
};