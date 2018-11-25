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
    class SortElem {
    public:
        int val;
        ListNode *ptr;
        SortElem(int _val, ListNode *_ptr): val(_val), ptr(_ptr) {}
        bool operator< (const SortElem &a) const {return val > a.val;}
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<SortElem> topHeap;
        for (vector<ListNode*>::iterator itr = lists.begin();
             itr != lists.end(); ++itr) {
            ListNode *pCurr = *itr;
            if (pCurr != NULL) {
                topHeap.push(SortElem(pCurr->val, pCurr));
            }
        }
        
        ListNode *sortedHead = NULL, *sortedTail = NULL;
        while (!topHeap.empty()) {
            SortElem top = topHeap.top();
            topHeap.pop();
            if (sortedHead == NULL) {
                sortedHead = sortedTail = top.ptr;
            } else {
                sortedTail->next = top.ptr;
                sortedTail = sortedTail->next;
            }
            if (top.ptr->next != NULL) {
                topHeap.push(SortElem(top.ptr->next->val, top.ptr->next));
            }
            sortedTail->next = NULL;
        }
        return sortedHead;
    }
};