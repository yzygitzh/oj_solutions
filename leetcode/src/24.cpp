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
    ListNode* swapPairs(ListNode* head) {
        ListNode *result = head, *before = nullptr;
        int count = 0;
        while (head != nullptr && head->next != nullptr) {
            ListNode *newHead = head->next->next;
            ListNode *p1 = head;
            ListNode *p2 = head->next;
            if (before == nullptr) {
                result = p2;
            } else {
                before->next = p2;
            }
            p2->next = p1;
            p1->next = newHead;
            before = p1;
            head = newHead;
        }
        return result;
    }
};