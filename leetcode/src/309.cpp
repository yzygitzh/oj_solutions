class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int pricesLen = prices.size();
        if (pricesLen <= 1) return 0;
        
        vector<int> buyProfit(pricesLen, 0); // max profit when buying at i
        vector<int> sellProfit(pricesLen, 0); // max profit when selling at i
        int maxProfit = 0;
        
        for (int i = 1; i < pricesLen; i++) {
            int maxSellProfit = prices[i] - prices[0]; // we can choose don't sell until i
            for (int j = 0; j < i; j++) {
                int currSellProfit = buyProfit[j] + prices[i] - prices[j];
                if (currSellProfit > maxSellProfit) maxSellProfit = currSellProfit;
            }
            sellProfit[i] = maxSellProfit;
            if (sellProfit[i] > maxProfit) maxProfit = sellProfit[i];
                
            int maxBuyProfit = 0; // we can choose don't buy until i
            for (int j = 1; j <= i - 2; j++) {
                int currBuyProfit = sellProfit[j];
                if (currBuyProfit > maxBuyProfit) maxBuyProfit = currBuyProfit;
            }
            buyProfit[i] = maxBuyProfit;
        }
        
        return maxProfit;
    }
};