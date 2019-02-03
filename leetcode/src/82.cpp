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
        ListNode *result = head, *before = nullptr;
        while (head != nullptr) {
            if (head->next != nullptr && head->val == head->next->val) {
                int valToDel = head->val;
                while (head != nullptr && head->val == valToDel) {
                    ListNode *next = head->next;
                    if (result == head) result = next;
                    delete head;
                    head = next;
                }
                // connect
                if (before != nullptr) {
                    before->next = head;
                }
            } else {
                before = head;
                head = head->next;
            }
        }
        return result;
    }
};