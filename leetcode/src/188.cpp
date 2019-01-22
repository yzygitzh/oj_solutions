class Solution {
public:
    class IntListNode {
    public:
        int val;
        IntListNode *next, *prev;
        IntListNode (int _val): val(_val), next(nullptr), prev(nullptr) {}
    };
    
    IntListNode *head = nullptr, *tail = nullptr;
    
    void listAppend(int val) {
        if (head == nullptr) {
            head = tail = new IntListNode(val);
        } else {
            tail->next = new IntListNode(val);
            tail->next->prev = tail;
            tail = tail->next;
        }
    }
    
    void listDel(IntListNode *p) {
        if (p == head && p == tail) {
            head = tail = nullptr;
        } else if (p == head) {
            p->next->prev = p->prev;
            head = p->next;
        } else if (p == tail) {
            p->prev->next = p->next;
            tail = p->prev;
        } else {
            p->next->prev = p->prev;
            p->prev->next = p->next;
        }
        delete p;
    }
    
    int getAbs(int x) {
        return x > 0 ? x : -x;
    }
    
    int maxProfit(int k, vector<int>& prices) {
        if (k == 0) return 0;

        int pricesLen = prices.size();
        if (pricesLen <= 1) return 0;
      
        int currSum = 0;
        int positiveCnt = 0;
        for (int i = 1; i < pricesLen; i++) {
            int delta = prices[i] - prices[i - 1];
            if (currSum * delta < 0) {
                if (currSum > 0) positiveCnt++;
                listAppend(currSum);
                currSum = delta;
            } else {
                currSum += delta;
            }
        }
        if (currSum > 0) positiveCnt++;
        listAppend(currSum);

        set<pair<int, IntListNode*>> deltaToPtr;
        for (IntListNode* p = head; p != nullptr; p = p->next) {
            deltaToPtr.insert(make_pair(getAbs(p->val), p));
        }
        
        while (positiveCnt > k) {
            // delete negative numbers from two ends
            while (head->val < 0) {
                deltaToPtr.erase(make_pair(getAbs(head->val), head));
                listDel(head);
            }
            while (tail->val < 0) {
                deltaToPtr.erase(make_pair(getAbs(tail->val), tail));
                listDel(tail);
            }
            
            // note that the chosen one cannot change the sign around it
            // otherwise it won't be chosen
            IntListNode *p = deltaToPtr.begin()->second;
            deltaToPtr.erase(deltaToPtr.begin());
            if (p->val > 0) positiveCnt--;

            // do merge with before if there is any
            if (p->prev != nullptr) {
                if (p->prev->val > 0) positiveCnt--;
                p->val += p->prev->val;
                deltaToPtr.erase(make_pair(getAbs(p->prev->val), p->prev));
                listDel(p->prev);
            }

            // do merge with after if there is any
            if (p->next != nullptr) {
                if (p->next->val > 0) positiveCnt--;
                p->val += p->next->val;
                deltaToPtr.erase(make_pair(getAbs(p->next->val), p->next));
                listDel(p->next);
            }
            
            deltaToPtr.insert(make_pair(getAbs(p->val), p));
            if (p->val > 0) {
                positiveCnt++;
            }
        }

        int result = 0;
        for (IntListNode* p = head; p != nullptr; p = p->next) {
            if (p->val > 0) result += p->val;
        }
        return result;
    }
};