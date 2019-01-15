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
    vector<int> flipped;
    int currIdx = 0;
    bool invalid = false;
    
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        tryWalk(root, voyage);
        if (invalid) return vector<int>{-1};
        else return flipped;
    }
    
    void tryWalk(TreeNode* root, vector<int>& voyage) {
        if (invalid) return;
        if (root == nullptr) return;
        if (root->val != voyage[currIdx]) {
            invalid = true;
            return;
        }
        currIdx += 1;
        
        bool needFlip = (root->left != nullptr && root->left->val != voyage[currIdx]);
        if (needFlip) {
            flipped.push_back(root->val);
            tryWalk(root->right, voyage);
            tryWalk(root->left, voyage);
        } else {
            tryWalk(root->left, voyage);
            tryWalk(root->right, voyage);
        }
    }
};