class Solution {
public:
    int getMax(int a, int b) {
        return a > b ? a : b;
    }
    
    int maxProfit(vector<int>& prices) {
        int pricesLen = prices.size();
        if (pricesLen < 2) return 0;
        
        // four states
        // 0 - sell -> 1 - buy -> 2 - sell -> 3 (finale)
        // <- rest     <- rest    <- rest     <- rest
        vector<int> states(4, 0);
        vector<int> newStates(4, 0);
        for (int i = 0; i < pricesLen; i++) {
            if (i > 0) {
                newStates[0] = getMax(states[0], -prices[i]);
            } else if (i == 0) {
                newStates[0] = -prices[i];
            }
            
            if (i > 1) {
                newStates[1] = getMax(states[1], prices[i] + states[0]);
            } else if (i == 1) {
                newStates[1] = prices[i] + states[0];
            }
            
            if (i > 2) {
                newStates[2] = getMax(states[2], states[1] - prices[i]);
            } else if (i == 2) {
                newStates[2] = states[1] - prices[i];
            }
            
            if (i > 3) {
                newStates[3] = getMax(states[3], prices[i] + states[2]);
            } else if (i == 3) {
                newStates[3] = prices[i] + states[2];
            }
            
            states = newStates;
        }
        
        return getMax(0, getMax(states[1], states[3]));
    }
};