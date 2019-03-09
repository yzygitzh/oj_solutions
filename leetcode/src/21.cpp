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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *result = nullptr, *p;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                if (result == nullptr) {
                    result = l1;
                    p = result;
                } else {
                    p->next = l1;
                    p = p->next;
                }
                l1 = l1->next;
            } else {
                if (result == nullptr) {
                    result = l2;
                    p = result;
                } else {
                    p->next = l2;
                    p = p->next;
                }
                l2 = l2->next;
            }
        }
        if (l1 != nullptr) {
            if (result == nullptr) {
                result = l1;
            } else {
                p->next = l1;
            }
        } else if (l2 != nullptr) {
            if (result == nullptr) {
                result = l2;
            } else {
                p->next = l2;
            }
        }
        return result;
    }
};