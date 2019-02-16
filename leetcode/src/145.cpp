/*
 * LeetCode 145 Binary Tree Postorder Traversal
 * Morris Traversal
 */
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
  vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    TreeNode *p = root, *tmp;
    while (p != nullptr) {
      if (p->right != nullptr) {
        tmp = p->right;
        while (tmp->left != nullptr && tmp->left != p) {
          tmp = tmp->left;
        }
        if (tmp->left == nullptr) {
          result.push_back(p->val);
          tmp->left = p;
          p = p->right;
        } else {
          tmp->left = nullptr;
          p = p->left;
        }
      } else {
        result.push_back(p->val);
        p = p->left;
      }
    }
    reverse(result.begin(), result.end());
    return result;
  }
};
