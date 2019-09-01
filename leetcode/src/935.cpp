class Solution {
public:
    int knightDialer(int N) {
        vector<long long> numToPlans(10, 1);
        for (int i = 0; i < N - 1; i++) {
            vector<long long> newNumToPlans(10, 0);
            newNumToPlans[0] = (numToPlans[4] + numToPlans[6]) % 1000000007;
            newNumToPlans[1] = (numToPlans[6] + numToPlans[8]) % 1000000007;
            newNumToPlans[2] = (numToPlans[7] + numToPlans[9]) % 1000000007;
            newNumToPlans[3] = (numToPlans[4] + numToPlans[8]) % 1000000007;
            newNumToPlans[4] = (numToPlans[3] + numToPlans[9] + numToPlans[0]) % 1000000007;
            newNumToPlans[6] = (numToPlans[1] + numToPlans[7] + numToPlans[0]) % 1000000007;
            newNumToPlans[7] = (numToPlans[2] + numToPlans[6]) % 1000000007;
            newNumToPlans[8] = (numToPlans[1] + numToPlans[3]) % 1000000007;
            newNumToPlans[9] = (numToPlans[2] + numToPlans[4]) % 1000000007;
            numToPlans = newNumToPlans;
        }
        long long result = 0;
        for (int i = 0; i < 10; i++) {
            if (N > 1 && i == 5) {
                continue;
            }
            result += numToPlans[i];
            result %= 1000000007;
        }
        return result;
    }
};