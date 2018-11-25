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
        ListNode *first = NULL, *second = NULL, *result = head, *beforeFirst = NULL, *swap;
        while (true) {
            if (first == NULL) {
                first = head;
            } else {
                beforeFirst = second;
                first = second->next;
            }
            if (first == NULL) return result;
            second = first->next;
            if (second == NULL) return result;
            
            if (beforeFirst != NULL) {
                beforeFirst->next = second;
            }
            first->next = second->next;
            second->next = first;
            if (beforeFirst == NULL) {
                result = second;
            }
            swap = second;
            second = first;
            first = swap;
        }
        return result;
    }
};