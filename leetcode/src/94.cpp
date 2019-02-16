/*
 * LeetCode 94 Binary Tree Inorder Traversal
 * Stack-Based Traversal
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
  vector<int> inorderTraversal(TreeNode* root) {
    vector<TreeNode*> nodeStack;
    vector<int> result;
    TreeNode *p = root;
    while (p != nullptr) {
      nodeStack.push_back(p);
      p = p->left;
    }
    while (nodeStack.size() > 0) {
      // invariant: top's left subtree has been accessed
      TreeNode* top = *nodeStack.rbegin();
      result.push_back(top->val);
      // find next element
      if (top->right != nullptr) {
        // if we have right subtree, find the smallest element
        p = top->right;
        while (p != nullptr) {
          nodeStack.push_back(p);
          p = p->left;
        }
      } else {
        // this is the biggest element in some right subtree
        // pop while is right subtree
        p = top;
        nodeStack.pop_back();
        while (nodeStack.size() > 0 && (*nodeStack.rbegin())->right == p) {
          p = *nodeStack.rbegin();
          nodeStack.pop_back();
        }
      }
    }
    return result;
  }
};
