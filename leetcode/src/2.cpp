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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode *result = NULL, *returnResult;
        while (l1 != NULL || l2 != NULL) {
            if (result != NULL) {
                result->next = new ListNode(0);
                result = result->next;
            } else {
                returnResult = result = new ListNode(0);
            }
            
            int sum = (l1 == NULL ? 0 : l1->val) + 
                      (l2 == NULL ? 0 : l2->val) + carry;
            carry = sum / 10;
            result->val = sum - carry * 10;
            if (l1 != NULL) l1 = l1->next;
            if (l2 != NULL) l2 = l2->next;
        }
        if (carry) {
            result->next = new ListNode(carry);
        }
        return returnResult;
    }
};