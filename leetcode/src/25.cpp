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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || head->next == NULL || k == 1) return head;
        ListNode *beforeSeg, *segStart, *segEnd;
        beforeSeg = segStart = head;
        while (true) {
            segEnd = segStart;
            bool stop = false;
            for (int i = 0; i < k - 1; i++) {
                segEnd = segEnd->next;
                if (segEnd == NULL) {
                    stop = true;
                    break;
                }
            }
            if (stop) break;
            ListNode *nextSeg = segEnd->next;
            ListNode *pOld = segStart;
            ListNode *pCurr = segStart->next;
            for (int i = 0; i < k - 1; i++) {
                ListNode *pNext = pCurr->next;
                pCurr->next = pOld;
                pOld = pCurr;
                pCurr = pNext;
            }
            
            // make beforeSeg points to segEnd
            // and segStart points to afterSeg
            if (beforeSeg == head) {
                head = segEnd;
            } else {
                beforeSeg->next = segEnd;    
            }
            beforeSeg = segStart;
            segStart->next = nextSeg;
            if (segStart->next == NULL) break;
            else segStart = segStart->next;
        }
        return head;
    }
};