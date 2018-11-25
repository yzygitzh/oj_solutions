/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int listLen = 0;
        ListNode *p = head, *tail = NULL;
        while (p != NULL) {
            listLen++;
            tail = p;
            p = p->next;
        }
        
        if (listLen == 0) {
            return NULL;
        } else if (listLen == 1) {
            TreeNode *newNode = new TreeNode(head->val);
            return newNode;
        } else {
            int midIdx = listLen / 2;
            int idx = 0;
            ListNode *leftHead = head;
            ListNode *leftTail = head;
            while (idx + 1 != midIdx) {
                leftTail = leftTail->next;
                idx++;
            }            
            ListNode *midP = leftTail->next;
            leftTail->next = NULL;
            ListNode *rightHead = midP->next;
            
            TreeNode *newNode = new TreeNode(midP->val);
            newNode->left = sortedListToBST(leftHead);
            newNode->right = sortedListToBST(rightHead);
            
            return newNode;
        }
    }
};