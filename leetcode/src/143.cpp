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
    void reorderList(ListNode* head) {
        // NULL, 1, 1->2
        if (head == NULL || head->next == NULL ||
            head->next->next == NULL) return;

        // at least 1->2->3
        ListNode *first, *secondFirst, *secondLast, *last;
        first = head;
        secondFirst = head->next;
        secondLast = head;
        while (secondLast->next->next != NULL) {
            secondLast = secondLast->next;
        }
        last = secondLast->next;
        
        secondLast->next = NULL;
        reorderList(secondFirst);
        first->next = last;
        last->next = secondFirst;
    }
};