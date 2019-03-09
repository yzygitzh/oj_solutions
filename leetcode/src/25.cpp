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
        if (k <= 1) return head; 
        ListNode *resultHead = nullptr, *resultTail = nullptr;
        if (hasNextGroup(head, k)) {
            while (hasNextGroup(head, k)) {
                ListNode *oldHead = head;
                ListNode *nextGroup = advanceList(head, k);
                ListNode *reversed = reverseList(head, k);
                oldHead->next = nextGroup;
                if (resultHead == nullptr) {
                    resultHead = reversed;
                } else {
                    resultTail->next = reversed;
                }
                resultTail = oldHead;
                head = nextGroup;
            }
        } else {
            resultHead = head;
        }
        return resultHead;
    }

    ListNode* advanceList(ListNode *head, int k) {
        while (k > 0) {
            head = head->next;
            k--;
        }
        return head;
    }

    bool hasNextGroup(ListNode *head, int k) {
        while (k != 0 && head != nullptr) {
            head = head->next;
            k--;
        }
        return k == 0;
    }

    ListNode* reverseList(ListNode* head, int k) {
        ListNode* beforeHead = nullptr;
        while (k != 0 && head != nullptr) {
            ListNode *oldHead = head;
            head = head->next;
            oldHead->next = beforeHead;
            beforeHead = oldHead;
            k--;
        }
        return beforeHead;
    }
};