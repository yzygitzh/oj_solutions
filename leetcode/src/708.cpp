/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (head == nullptr) {
            Node* result = new Node(insertVal, nullptr);
            result->next = result;
            return result;
        } else {
            Node *p = head;
            int minVal = p->val, maxVal = p->val;
            p = head->next;
            while (p != head) {
                minVal = min(minVal, p->val);
                maxVal = max(maxVal, p->val);
                p = p->next;
            }
            p = head;
            while (p->next != head) {
                if (p->val <= insertVal && insertVal <= p->next->val || 
                    p->next->val == minVal && p->val == maxVal &&
                    (insertVal >= p->val || insertVal <= p->next->val)) {
                    break;
                }
                p = p->next;
            }
            // invariant: insert new val after p is correct
            p->next = new Node(insertVal, p->next);
            return head;
        }
    }
};