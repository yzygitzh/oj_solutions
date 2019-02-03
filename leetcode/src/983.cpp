class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // F[M]: min cost covering M-th days, 1D/1D
        int daysLen = days.size();
        vector<int> minCost(daysLen + 1, ~(1 << 31));
        minCost[0] = 0;
        for (int i = 1; i <= daysLen; i++) {
            // try 1-day pass
            minCost[i] = min(minCost[i], minCost[i - 1] + costs[0]);
            // try 7-day pass
            if (days[i - 1] - days[0] <= 6) minCost[i] = min(minCost[i], costs[1]);
            int idx7 = i - 1;
            while (idx7 - 1 >= 1 && days[idx7 - 1] + 6 >= days[i - 1]) idx7--;
            minCost[i] = min(minCost[i], minCost[idx7] + costs[1]);
            // try 30-day pass
            if (days[i - 1] - days[0] <= 29) minCost[i] = min(minCost[i], costs[2]);
            int idx30 = idx7;
            while (idx30 - 1 >= 1 && days[idx30 - 1] + 29 >= days[i - 1]) idx30--;
            minCost[i] = min(minCost[i], minCost[idx30] + costs[2]);
        }
        return minCost[daysLen];
    }
};