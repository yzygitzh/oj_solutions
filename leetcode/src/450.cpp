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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val < key) {
            root->right = deleteNode(root->right, key);
            return root;
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
            return root;
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            if (root->right != nullptr) {
                // find smallest number in right
                TreeNode *parentRightMin = root,
                         *rightMin = parentRightMin->right,
                         *restRight = rightMin->right;
                while (rightMin->left != nullptr) {
                    parentRightMin = rightMin;
                    rightMin = parentRightMin->left;
                    restRight = rightMin->right;
                }
                // delete the node
                root->val = rightMin->val;
                delete rightMin;
                // move restRight
                if (parentRightMin == root) {
                    parentRightMin->right = restRight;
                } else {
                    parentRightMin->left = restRight;
                }
                return root;
            }
            // root->left isn't nullptr
            // find biggest number in left
            TreeNode *parentLeftMax = root,
                     *leftMax = parentLeftMax->left,
                     *restLeft = leftMax->left;
            while (leftMax->right != nullptr) {
                parentLeftMax = leftMax;
                leftMax = parentLeftMax->right;
                restLeft = leftMax->left;
            }
            // delete the node
            root->val = leftMax->val;
            delete leftMax;
            // move restLeft
            if (parentLeftMax == root) {
                parentLeftMax->left = restLeft;
            } else {
                parentLeftMax->right = restLeft;
            }
            return root;
        }
    }
};