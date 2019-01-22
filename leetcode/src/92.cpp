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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int idx = 1;
        ListNode *result = head, *before = nullptr, *oldHead;
        ListNode *beforeP1, *p1, *p2;
        while (head != nullptr) {
            if (m == idx) {
                beforeP1 = before;
                p1 = head;
            }
            if (m <= idx && idx <= n) {
                oldHead = head;
                head = head->next;
                oldHead->next = before;
                before = oldHead;
            } else {
                before = head;
                head = head->next;
            }
            if (n == idx) {
                p2 = oldHead;
                if (beforeP1 != nullptr) {
                    beforeP1->next = p2;
                } else {
                    result = p2;
                }
                p1->next = head;
            }
            idx++;
        }
        return result;
    }
};