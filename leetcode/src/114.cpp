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
    struct ListInfo {
        TreeNode *head, *tail;
    };
    void flatten(TreeNode* root) {
        convert(root);
    }
    ListInfo convert(TreeNode* root) {
        ListInfo result;
        result.head = result.tail = nullptr;
        if (root == nullptr) return result;
        ListInfo leftResult = convert(root->left);
        ListInfo rightResult = convert(root->right);
        
        root->left = root->right = nullptr;
        result.head = result.tail = root;
        // try insert left sequence
        if (leftResult.head != nullptr) {
            result.tail->right = leftResult.head;
            result.tail = leftResult.tail;
        }
        // then try right
        if (rightResult.head != nullptr) {
            result.tail->right = rightResult.head;
            result.tail = rightResult.tail;
        }
        return result;
    }
};