/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    Node *head = nullptr, *tail = nullptr;
    
    Node* flatten(Node* listHead) {
        // pre-order traversal
        walkList(listHead);
        return head;
    }
    
    void walkList(Node *root) {
        if (root == nullptr) return;
        Node *next = root->next, *child = root->child;
        if (head == nullptr) {
            head = tail = root;
        } else {
            tail->next = root;
            root->prev = tail;
            tail = root;
        }
        root->next = root->child = nullptr;
        walkList(child);
        walkList(next);
    }
};