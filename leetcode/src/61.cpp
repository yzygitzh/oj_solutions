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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) return head;

        int listLen = 0;
        ListNode *p = head, *tail;
        while (p != NULL) {
            listLen++;
            tail = p;
            p = p->next;
        }
        k = k % listLen;
        if (k == 0) return head;
        
        int listIdx = listLen - k - 1;
        p = head;
        while (listIdx--) p = p->next;
        tail->next = head;
        head = p->next;
        p->next = NULL;
        return head;
    }
};