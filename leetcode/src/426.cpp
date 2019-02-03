/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) return root;
        
        Node *leftTail = root->left, *rightTail = root->right;
        while (leftTail != nullptr && leftTail->right != nullptr) {
            leftTail = leftTail->right;
        }
        while (rightTail != nullptr && rightTail->right != nullptr) {
            rightTail = rightTail->right;
        }
        
        Node *leftHead = treeToDoublyList(root->left);
        Node *rightHead = treeToDoublyList(root->right);
        
        if (leftTail != nullptr) {
            leftTail->right = root;
            root->left = leftTail;
        } else {
            leftHead = root;
        }
        if (rightHead != nullptr) {
            root->right = rightHead;
            rightHead->left = root;
        } else {
            rightTail = root;
        }
        
        // connect first and final
        // leftHead and rightTail must not be nullptr
        leftHead->left = rightTail;
        rightTail->right = leftHead;
        
        return leftHead;
    }
};