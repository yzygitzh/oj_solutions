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
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    ListNode *head;
    
    Solution(ListNode* _head): head(_head) {}
    
    /** Returns a random node's value. */
    int getRandom() {
        int selected = head->val, count = 2;
        ListNode *p = head->next;
        while (p != nullptr) {
            if ((int)((double)rand() / (RAND_MAX + 1u) * count) == 0) {
                selected = p->val;
            }
            p = p->next;
            count++;
        }
        return selected;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */