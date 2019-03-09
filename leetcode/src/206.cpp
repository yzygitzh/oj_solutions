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
        ListNode *beforeHead = nullptr;
        while (head != nullptr) {
            ListNode *oldHead = head;
            head = head->next;
            oldHead->next = beforeHead;
            beforeHead = oldHead;
        }
        return beforeHead;
    }
};