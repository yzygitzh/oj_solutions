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
    ListNode* insertionSortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *sortedHead = NULL, *sortedTail = NULL;
        while (head != NULL) {
            ListNode *pCurr = head;
            head = head->next;
            
            // insert it into sorted
            if (sortedHead == NULL) {
                sortedHead = sortedTail = pCurr;
                pCurr->next = NULL;
            } else {
                ListNode *seeker = sortedHead;
                if (seeker->val > pCurr->val) {
                    // insert at head
                    pCurr->next = seeker;
                    sortedHead = pCurr;
                } else {
                    while (seeker->next != NULL && seeker->next->val < pCurr->val) {
                        seeker = seeker->next;
                    }
                    pCurr->next = seeker->next;
                    seeker->next = pCurr;
                }
            }
        }
        return sortedHead;
    }
};