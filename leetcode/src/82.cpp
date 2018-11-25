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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        int currVal;
        ListNode *before = head, *after, *lastBefore;
        while (before != NULL) {
            currVal = before->val;
            after = before->next;
            while (after != NULL && after->val == currVal) {
                after = after->next;
            }
            
            // delete [before, after) if before->next != after
            if (before->next != after) {
                if (before == head) head = after;
                else lastBefore->next = after;
                while (before != after) {
                    ListNode *p = before->next;
                    delete before;
                    before = p;
                }
            } else {
                lastBefore = before;
                before = after;
            }
        }
        return head;
    }
};