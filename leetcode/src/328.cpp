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
    ListNode* oddEvenList(ListNode* head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL) {
            return head;
        }
        ListNode *oddHead = NULL, *oddTail = NULL;
        ListNode *evenHead = NULL, *evenTail = NULL;
        
        ListNode *pCurr = head;
        int idx = 1;
        while (pCurr != NULL) {
            ListNode *pNext = pCurr->next;
            if (idx % 2) {
                if (oddHead == NULL) {
                    oddHead = oddTail = pCurr;
                } else {
                    oddTail->next = pCurr;
                    oddTail = pCurr;
                }
                oddTail->next = NULL;
            } else {
                if (evenHead == NULL) {
                    evenHead = evenTail = pCurr;
                } else {
                    evenTail->next = pCurr;
                    evenTail = pCurr;
                }
                evenTail->next = NULL;
            }
            pCurr = pNext;
            idx++;
        }
        
        // merge odd/even lists
        oddTail->next = evenHead;
        return oddHead;
    }
};