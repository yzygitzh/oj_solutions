/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *leftMost = root;
        while (leftMost != nullptr) {
            TreeLinkNode *p = leftMost;
            if (p->left == nullptr) break;
            while (p != nullptr) {
                p->left->next = p->right;
                if (p->next != nullptr) p->right->next = p->next->left;
                else p->right->next = nullptr;
                p = p->next;
            }
            leftMost = leftMost->left;
        }
    }
};