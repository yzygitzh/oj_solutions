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
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        // at least 1->2
        // find mid
        ListNode *p1 = head, *p2 = head;
        while (true) {
            p1 = p1->next;
            p2 = p2->next;
            if (p2 == NULL) break;
            p2 = p2->next;
            if (p2 == NULL) break;
        }
        // p1 is mid
        // sort [head, p1)
        ListNode *firstEnd = head;
        while (firstEnd->next != p1) {
            firstEnd = firstEnd->next;
        }
        firstEnd->next = NULL;
        ListNode *firstSeg = sortList(head);
        // sort [p1, p2)
        ListNode *secondSeg = sortList(p1);
        // merge
        ListNode *finalHead = NULL, *finalTail = NULL;
        while (firstSeg != NULL || secondSeg != NULL) {
            ListNode *nodeInsert;
            if (firstSeg == NULL) {
                nodeInsert = secondSeg;
            } else if (secondSeg == NULL) {
                nodeInsert = firstSeg;
            } else {
                nodeInsert = firstSeg->val < secondSeg->val ? firstSeg : secondSeg;
            }
            if (nodeInsert == firstSeg) firstSeg = firstSeg->next;
            if (nodeInsert == secondSeg) secondSeg = secondSeg->next;
            
            if (finalHead == NULL) {
                finalHead = finalTail = nodeInsert;                
            } else {
                finalTail->next = nodeInsert;
                finalTail = finalTail->next;
            }
            finalTail->next = NULL;
        }
        return finalHead;
    }
};