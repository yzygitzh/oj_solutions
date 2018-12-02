class Solution {
public:
    int numTrees(int n) {
        if (n <= 0) return 0;
        vector<int> numOfTrees(n + 1, 0);
        numOfTrees[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                numOfTrees[i] += numOfTrees[j - 1] * numOfTrees[i - j];
            }
        }
        return numOfTrees[n];
    }
};