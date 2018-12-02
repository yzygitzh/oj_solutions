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
    map<pair<int, int>, vector<TreeNode*> > memo;
    vector<TreeNode*> generateTrees(int n) {
        if (n <= 0) return vector<TreeNode*>();
        else return genSubTrees(1, n);
    }
    vector<TreeNode*> genSubTrees(int left, int right) {
        if (left > right) {
            return vector<TreeNode*>{NULL};
        } else if (memo.find(make_pair(left, right)) != memo.end()) {
            return memo[make_pair(left, right)];
        } else if (left == right) {
            vector<TreeNode*> result;
            TreeNode* newNode = new TreeNode(left);
            result.push_back(newNode);
            memo[make_pair(left, right)] = result;
            return memo[make_pair(left, right)];
        } else {
            vector<TreeNode*> result;
            for (int i = left; i <= right; i++) {
                vector<TreeNode*> leftSubTrees = genSubTrees(left, i - 1);
                vector<TreeNode*> rightSubTrees = genSubTrees(i + 1, right);
                for (vector<TreeNode*>::iterator itr1 = leftSubTrees.begin();    
                     itr1 != leftSubTrees.end(); ++itr1) {
                    for (vector<TreeNode*>::iterator itr2 = rightSubTrees.begin();
                         itr2 != rightSubTrees.end(); ++itr2) {
                        TreeNode* newNode = new TreeNode(i);
                        newNode->left = *itr1;
                        newNode->right = *itr2;
                        result.push_back(newNode);
                    }
                }
            }
            memo[make_pair(left, right)] = result;
            return memo[make_pair(left, right)];
        }
    }
};