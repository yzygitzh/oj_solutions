class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        // k = 2: states: 0 -buy-> 1 -sell-> 2 -buy-> 3 -sell-> 4
        k = min(k, int(prices.size() / 2));
        vector<int> states(2 * k + 1, 0);
        int result = 0;
        for (int i = 0; i < prices.size(); i++) {
            // reverse update states to reuse former states
            for (int j = 2 * k; j >= 1; j--) {
                if (i + 1 >= j) {
                    int delta = (j % 2) ? -prices[i] : prices[i];
                    if (i + 1 == j) {
                        states[j] = states[j - 1] + delta;
                    } else {
                        states[j] = max(states[j], states[j - 1] + delta);
                    }
                    result = max(result, states[j]);
                }
            }
        }
        return result;
    }
};