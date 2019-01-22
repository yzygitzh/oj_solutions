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
    ListNode* reverseList(ListNode* head) {
        ListNode* before = nullptr, *oldHead;
        while (head != nullptr) {
            oldHead = head;
            head = head->next;
            oldHead->next = before;
            before = oldHead;
        }
        return oldHead;
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        int carry = 0;
        ListNode *p = nullptr, *result;
        while (l1 != nullptr || l2 != nullptr) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            if (p == nullptr) {
                p = new ListNode(sum % 10);
                result = p;
            } else {    
                p->next = new ListNode(sum % 10);
                p = p->next;
            }
            carry = sum / 10;
        }
        if (carry) {
            p->next = new ListNode(carry);
        }
        return reverseList(result);
    }
};