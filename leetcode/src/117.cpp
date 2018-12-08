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
            // invariant: level of leftMost is connected
            TreeLinkNode *p = leftMost;
            TreeLinkNode *nextLeftMost = nullptr;
            TreeLinkNode *lastNextP = nullptr;
            // move on leftMost's level
            while (p != nullptr) {
                // see if there is non-null node
                if (p->left != nullptr) {
                    if (lastNextP == nullptr) nextLeftMost = lastNextP = p->left;
                    else {
                        lastNextP->next = p->left; 
                        lastNextP = lastNextP->next;
                    }
                }
                if (p->right != nullptr) {
                    if (lastNextP == nullptr) nextLeftMost = lastNextP = p->right;
                    else {
                        lastNextP->next = p->right;
                        lastNextP = lastNextP->next;
                    }
                }
                p = p->next;
            }
            if (lastNextP != nullptr) lastNextP->next = nullptr;
            leftMost = nextLeftMost;
        }
    }
};