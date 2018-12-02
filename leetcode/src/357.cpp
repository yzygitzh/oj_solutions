class Solution {
public:
    // start without 0
    int countNumbersWithUniqueDigits(int n) {
        // numberOfSeqs[(m, n)]: number of n-length sequence made up by m digits
        // m >= n
        map<pair<int, int>, int> numberOfSeqs;
        for (int i = 1; i <= 10; i++) {
            numberOfSeqs[make_pair(i, 1)] = i;
        }
        for (int i = 2; i <= 10; i++) {
            for (int j = i; j <= 10; j++) {
                numberOfSeqs[make_pair(j, i)] = j * numberOfSeqs[make_pair(j - 1, i - 1)];
            }
        }
        if (n == 0) return 1;
        if (n >= 10) n = 10;
        int sum = 10; // "0" - "9"
        for (int i = 2; i <= n; i++) {
            sum += 9 * numberOfSeqs[make_pair(9, i - 1)];
        }
        return sum;
    }
};