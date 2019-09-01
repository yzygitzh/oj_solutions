/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        Node* p = head;
        while (p != nullptr) {
            Node *newNode = new Node(p->val, p->next, p->random);
            p->next = newNode;
            p = newNode->next;
        }
        Node *result = head->next;
        p = head;
        while (p != nullptr) {
            if (p->random != nullptr) {
                p->next->random = p->random->next;
            }
            p = p->next->next;
        }
        p = head;
        while (p != nullptr) {
            Node *nextP = p->next->next;
            if (nextP != nullptr) {
                p->next->next = nextP->next;
            }
            p->next = nextP;
            p = nextP;
        }
        return result;
    }
};