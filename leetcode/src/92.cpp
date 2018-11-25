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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (m == n || head == NULL) return head;
        ListNode *beforeRev = NULL, *afterRev = NULL;
        int idx = 1;
        ListNode *pCurr = head, *pLast = NULL, *pM, *pN;
        while (pCurr != NULL) {
            ListNode *pNext = pCurr->next;
            if (idx > m && idx <= n) {
                pCurr->next = pLast;
            }
            if (idx == m - 1) beforeRev = pCurr;
            if (idx == m) pM = pCurr;
            if (idx == n + 1) afterRev = pCurr;
            if (idx == n) pN = pCurr;
            pLast = pCurr;
            pCurr = pNext;
            idx++;
        }
        if (beforeRev != NULL){
            beforeRev->next = pN;
        } else {
            head = pN;
        }
        pM->next = afterRev;
        return head;
    }
};