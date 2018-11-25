class Solution {
public:
    double myPow(double x, int n) {
        int nSign;
        unsigned uN;
        if (n == (1 << 31)) {
            nSign = -1;
            uN = (1 << 31);
        } else if (n > 0) {
            nSign = 1;
            uN = n;
        } else if (n < 0) {
            nSign = -1;
            uN = -n;
        } else {
            // n == 0, x^0 -> 1
            return 1.0;
        }
        // calc pow(x, 2^1), ... pow(x, 2^31)
        double allPows[32];
        allPows[0] = x;
        for (int i = 1; i <= 31; i++) {
            allPows[i] = allPows[i - 1] * allPows[i - 1];
        }
        // multiply them
        double multi = 1.0;
        for (int i = 0; i <= 31; i++) {
            if ((1 << i) & uN) multi *= allPows[i];
        }
        if (nSign > 0) return multi;
        else return 1.0 / multi;
    }
};