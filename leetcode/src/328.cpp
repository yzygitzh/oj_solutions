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
    ListNode* oddEvenList(ListNode* head) {
        // invariant: grouped list + origin list
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *oddHead = head, *evenHead = head->next;
        ListNode *oddTail = oddHead, *evenTail = evenHead;
        while (evenTail != nullptr && evenTail->next != nullptr) {
            oddTail->next = evenTail->next;
            evenTail->next = evenTail->next->next;
            oddTail = oddTail->next;
            oddTail->next = evenHead;
            evenTail = evenTail->next;
        }
        return oddHead;
    }
};