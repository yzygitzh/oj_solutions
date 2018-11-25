/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL) return head;
        map<RandomListNode *, RandomListNode *> old2new;
        RandomListNode *pCurr = head, *newHead = NULL, *newTail = NULL;
        while (pCurr != NULL) {
            // create shadow node
            if (newHead == NULL) {
                newHead = newTail = new RandomListNode(pCurr->label);
            } else {
                newTail->next = new RandomListNode(pCurr->label);
                newTail = newTail->next;
            }
            old2new[pCurr] = newTail;
            pCurr = pCurr->next;
        }
        pCurr = head;
        newTail = newHead;
        while (pCurr != NULL && newTail != NULL) {
            newTail->random = old2new[pCurr->random];
            pCurr = pCurr->next;
            newTail = newTail->next;
        }
        return newHead;
    }
};