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
    ListNode* partition(ListNode* head, int x) {
        ListNode *lessHead = NULL, *lessTail = NULL;
        ListNode *moreHead = NULL, *moreTail = NULL;
        while (head != NULL) {
            ListNode *pNext = head->next;
            if (head->val < x) {
                if (lessHead == NULL) {
                    lessHead = lessTail = head;
                } else {
                    lessTail->next = head;
                    lessTail = head;
                }
                lessTail->next = NULL;
            } else {
                if (moreHead == NULL) {
                    moreHead = moreTail = head;
                } else {
                    moreTail->next = head;
                    moreTail = head;
                }
                moreTail->next = NULL;
            }
            head = pNext;
        }
        if (lessHead == NULL) {
            return moreHead;
        }
        else {
            lessTail->next = moreHead;
            return lessHead;
        }
    }
};