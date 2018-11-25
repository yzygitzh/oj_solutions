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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // first count list length
        int len = 0;
        ListNode *p = head;
        while (p != NULL) {
            len++;
            p = p->next;    
        }
        
        // convert it to delete n-th from front
        n = len - n + 1;
        
        ListNode *result;
        if (n == 1) {
            result = head->next;
            delete head;
        } else {
            result = head;
            ListNode *before = head, *after;
            while (--n != 1) before = before->next;
            after = before->next->next;
            delete before->next;
            before->next = after;
        }
        return result;
    }
};