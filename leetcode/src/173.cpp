/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    vector<TreeNode*> nodeStack;
    
    BSTIterator(TreeNode *root) {
        while (root != nullptr) {
            nodeStack.push_back(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return nodeStack.size() > 0;
    }

    /** @return the next smallest number */
    int next() {
        // Each edge is walked twice, in average O(1).
        int stackIdx = nodeStack.size() - 1;
        TreeNode* currP = nodeStack[stackIdx];
        
        // left child has been explored, return self
        nodeStack.pop_back();
        TreeNode *next = currP->right;
        while (next != nullptr) {
            nodeStack.push_back(next);
            next = next->left;
        }
        return currP->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */