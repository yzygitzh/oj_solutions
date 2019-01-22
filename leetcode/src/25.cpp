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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *result = head, *before = nullptr;
        while (true) {
            ListNode *p1 = head, *p2 = nextK(head, k - 1);
            if (p2 == nullptr) break;
            head = p2->next;
            p2->next = nullptr;
            reverseList(p1);
            if (before == nullptr) {
                result = p2;
            } else {
                before->next = p2;
            }
            p1->next = head;
            before = p1;
        }
        return result;
    }
    
    ListNode* nextK(ListNode *head, int k) {
        while (k && head != nullptr) {
            head = head->next;
            k--;
        }
        return head;
    }
    
    ListNode* reverseList(ListNode *head) {
        ListNode *before = nullptr, *oldHead = nullptr;
        while (head != nullptr) {
            oldHead = head;
            head = head->next;
            oldHead->next = before;
            before = oldHead;
        }
        return oldHead;
    }
};