class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        // put the last to the first
        // and add new number to the first
        // for complexity we do it in reverse order
        sort(deck.begin(), deck.end(), greater<int>());
        int deckLen = deck.size();
        queue<int> orderSeq;
        for (int i = 0; i < deckLen; i++) {
            int orderSeqLen = orderSeq.size();
            if (orderSeqLen > 0) {
                int front = orderSeq.front();
                orderSeq.pop();
                orderSeq.push(front);
            }
            orderSeq.push(deck[i]);
        }
        vector<int> result(deckLen, 0);
        for (int i = deckLen - 1; i >= 0; i--) {
            result[i] = orderSeq.front();
            orderSeq.pop();
        }
        return result;
    }
    
};