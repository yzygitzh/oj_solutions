class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int getMin(int a, int b) {
        return a < b ? a : b;
    }
    
    int maxProfit(int k, vector<int>& prices) {
        // state machine
        
        int pricesLen = prices.size();
        if (k == 0 || pricesLen <= 1) return 0;
        k = getMin(k, pricesLen / 2);
        
        vector<int> state(k * 2), newState(k * 2);
        for (int i = 0; i < pricesLen; i++) {
            for (int j = 0; j < getMin(i + 1, k * 2); j++) {
                if (j % 2) { // sell state
                    if (i == j) newState[j] = state[j - 1] + prices[i];
                    else newState[j] = getMax(state[j], state[j - 1] + prices[i]);
                } else {
                    if (j == 0) { // buy state
                        if (i == j) newState[j] = -prices[i];
                        else newState[j] = getMax(state[j], -prices[i]);
                    } else {
                        if (i == j) newState[j] = state[j - 1] - prices[i];
                        else newState[j] = getMax(state[j], state[j - 1] - prices[i]);
                    }
                }
            }
            state = newState;
        }

        int maxProfit = 0;
        for (int i = 0; i < getMin(pricesLen, k * 2); i++) {
            if (state[i] > maxProfit) maxProfit = state[i];
        }
        return maxProfit;
    }
};