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
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> result;
        // val, idx
        vector<pair<int, int>> numStack;
        int idx = 0;
        while (head != nullptr) {
            while (!numStack.empty() && head->val > numStack.back().first) {
                result.resize(max(int(result.size()), numStack.back().second + 1));
                result[numStack.back().second] = head->val;
                numStack.pop_back();
            }
            numStack.push_back(make_pair(head->val, idx));
            head = head->next;
            idx++;
        }
        result.resize(idx);
        for (auto& p : numStack) {
            result[p.second] = 0;
        }
        return result;
    }
};