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
    ListNode* reverseList(ListNode *head) {
        ListNode *before = nullptr;
        while (head != nullptr) {
            ListNode *oldHead = head;
            head = head->next;
            oldHead->next = before;
            before = oldHead;
        }
        return before;
    }
    
    ListNode* plusOne(ListNode* head) {
        head = reverseList(head);
        int carry = 1;
        ListNode *p = head;
        while (p != nullptr) {
            int sum = p->val + carry;
            p->val = sum % 10;
            carry = sum / 10;
            if (!carry) break;
            if (p->next == nullptr) p->next = new ListNode(0);
            p = p->next;
        }
        return reverseList(head);
    }
};