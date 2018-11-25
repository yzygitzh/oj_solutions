/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == head) return head;
        // whether there is a circle
        ListNode *p1 = head, *p2 = head;
        while (true) {
            p1 = p1->next;
            p2 = p2->next;
            if (p2 == NULL) return NULL;
            p2 = p2->next;
            if (p2 == NULL) return NULL;
            if (p1 == p2) break;
        }
        // p1/p2 is in circle
        // floyd's algorithm
        
        p2 = head;
        while (p2 != p1) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};